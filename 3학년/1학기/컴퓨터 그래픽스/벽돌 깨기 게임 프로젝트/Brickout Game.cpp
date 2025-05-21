#include "brick_game.h"
#include <stdio.h>
#include <time.h>

void initPentagon() {
    float cx = WIDTH / 2.0f;
    float cy = HEIGHT / 2.0f;
    float r = 250.0f;
    for (int i = 0; i < 5; i++) {
        pentagon[i].x = cx + r * cos(PI / 2 + i * 2 * PI / 5);
        pentagon[i].y = cy + r * sin(PI / 2 + i * 2 * PI / 5);
    }
}

void updatePaddlePosition() {
    Point A = pentagon[3];
    Point B = pentagon[2];
    float dx = B.x - A.x;
    float dy = B.y - A.y;
    float length = hypot(dx, dy);
    float halfPaddle = PADDLE_WIDTH / 2.0f;
    float tMin = halfPaddle / length;
    float tMax = 1.0f - halfPaddle / length;
    if (paddleT < tMin) paddleT = tMin;
    if (paddleT > tMax) paddleT = tMax;
    float px = A.x + paddleT * dx;
    float py = A.y + paddleT * dy;
    paddleX = px - PADDLE_WIDTH / 2;
    paddleY = py;
}

void initBricks() {
    srand(time(NULL));
    int rows = 4;
    int cols = 5;
    float totalWidth = cols * BRICK_WIDTH + (cols - 1) * BRICK_MARGIN;
    float totalHeight = rows * BRICK_HEIGHT + (rows - 1) * BRICK_MARGIN;
    float startX = WIDTH / 2 - totalWidth / 2;
    float startY = HEIGHT / 2 + 100;
    int index = 0;
    for (int i = 0; i < rows && index < MAX_BRICKS; i++) {
        for (int j = 0; j < cols && index < MAX_BRICKS; j++) {
            bricks[index].x = startX + j * (BRICK_WIDTH + BRICK_MARGIN);
            bricks[index].y = startY - i * (BRICK_HEIGHT + BRICK_MARGIN);
            bricks[index].visible = true;
            bricks[index].r = (rand() % 100) / 100.0f;
            bricks[index].g = (rand() % 100) / 100.0f;
            bricks[index].b = (rand() % 100) / 100.0f;
            index++;
        }
    }
    brickCount = index;
}

void drawBricks() {
    for (int i = 0; i < brickCount; i++) {
        if (!bricks[i].visible) continue;
        float x = bricks[i].x;
        float y = bricks[i].y;
        glColor3f(bricks[i].r, bricks[i].g, bricks[i].b);
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + BRICK_WIDTH, y);
        glVertex2f(x + BRICK_WIDTH, y + BRICK_HEIGHT);
        glVertex2f(x, y + BRICK_HEIGHT);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + BRICK_WIDTH, y);
        glVertex2f(x + BRICK_WIDTH, y + BRICK_HEIGHT);
        glVertex2f(x, y + BRICK_HEIGHT);
        glEnd();
    }
}

void drawPentagon() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 5; i++)
        glVertex2f(pentagon[i].x, pentagon[i].y);
    glEnd();
}

void drawPaddle() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(paddleX, paddleY);
    glVertex2f(paddleX + PADDLE_WIDTH, paddleY);
    glVertex2f(paddleX + PADDLE_WIDTH, paddleY + PADDLE_HEIGHT);
    glVertex2f(paddleX, paddleY + PADDLE_HEIGHT);
    glEnd();
}

void drawBall() {
    glColor3f(ballColorR, ballColorG, ballColorB);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 50; i++) {
        float angle = i * 2 * PI / 50;
        glVertex2f(ballX + BALL_RADIUS * cos(angle), ballY + BALL_RADIUS * sin(angle));
    }
    glEnd();
}

void drawText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void drawStrokeText(const char* text, float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);
    for (const char* c = text; *c; c++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawStrokeTextCentered(const char* text, float centerX, float centerY, float scale) {
    float totalWidth = 0.0f;
    for (const char* c = text; *c; ++c) {
        totalWidth += glutStrokeWidth(GLUT_STROKE_ROMAN, *c);
    }
    float adjustedX = centerX - (totalWidth * scale / 2.0f);
    glPushMatrix();
    glTranslatef(adjustedX, centerY, 0.0f);
    glScalef(scale, scale, 1.0f);
    for (const char* c = text; *c; ++c) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }
    glPopMatrix();
}

void drawCountdown() {
    if (countdownActive && countdownNumber > 0) {
        char buffer[10];
        sprintf_s(buffer, "%d", countdownNumber);
        glColor3f(1.0f, 1.0f, 0.0f);
        drawStrokeTextCentered(buffer, WIDTH / 2.0f, HEIGHT / 2.0f, 0.4f);
    }
}

void drawBestRecord() {
    if (hasBestRecord) {
        char buffer[64];
        sprintf_s(buffer, "Best Record: %.2f sec", bestRecord);
        glColor3f(0.0f, 1.0f, 0.0f);
        drawText(WIDTH / 2 - 80, HEIGHT - 30, buffer, GLUT_BITMAP_HELVETICA_18);
    }
}


float pointToSegmentDistance(Point A, Point B, Point P) {
    float dx = B.x - A.x;
    float dy = B.y - A.y;
    float l2 = dx * dx + dy * dy;
    if (l2 == 0.0f) return hypot(P.x - A.x, P.y - A.y);
    float t = ((P.x - A.x) * dx + (P.y - A.y) * dy) / l2;
    t = fmax(0, fmin(1, t));
    float projX = A.x + t * dx;
    float projY = A.y + t * dy;
    return hypot(P.x - projX, P.y - projY);
}

void checkWallCollisions() {
    Point ball = { ballX, ballY };
    for (int i = 0; i < 5; i++) {
        Point A = pentagon[i];
        Point B = pentagon[(i + 1) % 5];
        float dist = pointToSegmentDistance(A, B, ball);
        if (dist <= BALL_RADIUS) {
            float dx = B.x - A.x;
            float dy = B.y - A.y;
            float length = hypot(dx, dy);
            float nx = -dy / length;
            float ny = dx / length;
            float dot = ballDX * nx + ballDY * ny;
            ballDX = ballDX - 2 * dot * nx;
            ballDY = ballDY - 2 * dot * ny;
            ballX += nx * (BALL_RADIUS - dist);
            ballY += ny * (BALL_RADIUS - dist);
        }
    }
}

void checkPaddleCollision() {
    if (ballY - BALL_RADIUS <= paddleY + PADDLE_HEIGHT &&
        ballX >= paddleX && ballX <= paddleX + PADDLE_WIDTH &&
        ballDY < 0) {

        paddleHitCount++;
        ballDY = -ballDY * SPEED_INCREASE;
        ballDX *= SPEED_INCREASE;
        ballY = paddleY + PADDLE_HEIGHT + BALL_RADIUS;

        if (paddleHitCount >= 5 && !speedBoosted) {
            ballDX *= 1.5f;
            ballDY *= 1.5f;
            ballColorR = 1.0f;
            ballColorG = 0.0f;
            ballColorB = 0.0f;
            speedBoosted = true;
            speedBoostTimer = 0.0f;
        }
    }
}

void checkBrickCollisions() {
    for (int i = 0; i < brickCount; i++) {
        if (!bricks[i].visible) continue;
        float x = bricks[i].x;
        float y = bricks[i].y;
        if (ballX + BALL_RADIUS >= x && ballX - BALL_RADIUS <= x + BRICK_WIDTH &&
            ballY + BALL_RADIUS >= y && ballY - BALL_RADIUS <= y + BRICK_HEIGHT) {
            bricks[i].visible = false;
            ballDY = -ballDY;

            bool allCleared = true;
            for (int j = 0; j < brickCount; j++) {
                if (bricks[j].visible) {
                    allCleared = false;
                    break;
                }
            }

            if (allCleared && !gameCleared) {
                gameCleared = true;
                clearTime = ((float)clock() / CLOCKS_PER_SEC) - startTime;

                if (!hasBestRecord || clearTime < bestRecord) {
                    bestRecord = clearTime;
                    hasBestRecord = true;
                }
                gameCleared = true;
            }

            break;
        }
    }
}

void update(int value) {
    if (!gameStarted) return;

    ballDY -= GRAVITY;
    if (ballDY < MAX_FALL_SPEED)
        ballDY = MAX_FALL_SPEED;
    ballX += ballDX;
    ballY += ballDY;
    checkWallCollisions();
    checkPaddleCollision();
    checkBrickCollisions();

    if (speedBoosted) {
        speedBoostTimer += 0.016f;
        if (speedBoostTimer >= 1.0f) {
            ballDX /= 1.5f;
            ballDY /= 1.5f;
            ballColorR = 0.0f;
            ballColorG = 0.0f;
            ballColorB = 1.0f;
            speedBoosted = false;
            paddleHitCount = 0;
        }
    }

    if (gameCleared) {
        gameClearFlashTimer += 0.016f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


void keyboard(int key, int x, int y) {
    if (gameCleared) return;

    if (key == GLUT_KEY_LEFT) {
        paddleT += PADDLE_SPEED;
    }
    else if (key == GLUT_KEY_RIGHT) {
        paddleT -= PADDLE_SPEED;
    }
    updatePaddlePosition();
}

void countdownTimer(int value) {
    countdownNumber--;
    if (countdownNumber > 0) {
        glutTimerFunc(1000, countdownTimer, 0);
    }
    else {
        countdownActive = false;
        gameStarted = true;
        gameCleared = false;
        startTime = (float)clock() / CLOCKS_PER_SEC;
        glutTimerFunc(16, update, 0);
    }
    glutPostRedisplay();
}

void restartGame() {
    initBricks();
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    ballDX = 2.0f;
    ballDY = 0.0f;
    paddleT = 0.5f;
    updatePaddlePosition();
    paddleHitCount = 0;
    speedBoosted = false;
    speedBoostTimer = 0.0f;
    ballColorR = 0.0f;
    ballColorG = 0.0f;
    ballColorB = 1.0f;
    clearTime = 0.0f;
    gameCleared = false;
    countdownNumber = 4;

    countdownActive = true;
    gameStarted = false;
    glutTimerFunc(1000, countdownTimer, 0);
}

void keyboardNormal(unsigned char key, int x, int y) {
    if (gameCleared) {
        if (key == 'r' || key == 'R') {
            restartGame();
        }
        return;
    }

    if (!gameStarted && !countdownActive && (key == 's' || key == 'S')) {
        countdownActive = true;
        glutTimerFunc(0, countdownTimer, 0);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPentagon();
    drawBricks();
    drawPaddle();
    drawBall();

    drawBestRecord();

    if (!gameStarted && !countdownActive) {
        glColor3f(1.0f, 1.0f, 0.0f);
        drawStrokeTextCentered("Press S to Game Start", WIDTH / 2.0f, HEIGHT / 2.0f - 80.0f, 0.18f);
    }

    if (countdownActive) {
        drawCountdown();
    }

    if (speedBoosted) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(WIDTH / 2 - 50, HEIGHT / 2 - 20, "Speed UP!", GLUT_BITMAP_HELVETICA_18);
    }

    if (gameCleared) {
        if (((int)(gameClearFlashTimer * 2)) % 2 == 0)
            glColor3f(0.0f, 1.0f, 1.0f);
        else
            glColor3f(1.0f, 1.0f, 0.0f);

        drawStrokeTextCentered(" CONGRATULATION !! ", WIDTH / 2.0f, HEIGHT / 2.0f + 60.0f, 0.3f);
        drawStrokeTextCentered(" GAME CLEAR ", WIDTH / 2.0f, HEIGHT / 2.0f, 0.25f);
        drawStrokeTextCentered("Press R to Restart", WIDTH / 2.0f, HEIGHT / 2.0f - 80.0f, 0.18f);
    }

    glutSwapBuffers();
}



void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Pentagon Brick Game");
    initPentagon();
    updatePaddlePosition();
    initBricks();
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboardNormal);
    glutMainLoop();
    return 0;
}
