#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h> 
#include <math.h>

#define width 400
#define height 600
#define PI 3.1415
#define polygon_num 50

int collision_count = 0;
float radius1, moving_ball_radius;
float speed = 0.1f;

typedef struct {
    float x;
    float y;
} Point;

Point fixed_ball, moving_ball, velocity;
Point diamond[4]; 

void init(void) {
    radius1 = 20.0f;
    moving_ball_radius = 10.0f;

    fixed_ball.x = width / 2.0f;
    fixed_ball.y = height / 2.0f;

    moving_ball.x = width / 2.0f;
    moving_ball.y = height / 4.0f;

    velocity.x = 0.05f;
    velocity.y = 0.05f;

    // 다이아몬드 그리기 # 교수님께서 / 2 하라고 하심.
    diamond[0].x = width / 2.0f;   
    diamond[0].y = height;

    diamond[1].x = width;           
    diamond[1].y = height / 2.0f;

    diamond[2].x = width / 2.0f;    
    diamond[2].y = 0;

    diamond[3].x = 0;               
    diamond[3].y = height / 2.0f;

    collision_count = 0;
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

void Modeling_Circle(float radius, Point center) {
    float delta = 2 * PI / polygon_num;
    glBegin(GL_POLYGON);
    for (int i = 0; i < polygon_num; i++)
        glVertex2f(center.x + radius * cos(delta * i), center.y + radius * sin(delta * i));
    glEnd();
}

void Draw_Diamond() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(diamond[i].x, diamond[i].y);
    glEnd();
}

void Collision_Detection_to_Walls() {// 공과 벽의 충돌 함수 
    for (int i = 0; i < 4; i++) {
        Point p1 = diamond[i];
        Point p2 = diamond[(i + 1) % 4];

        // 벡터 공식 사용: 선분 법선 벡터 
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;

        // 선분의 법선 벡터
        float nx = -dy;
        float ny = dx;

        // 점과 선까지의 거리 
        float A = dy;
        float B = -dx;
        float C = dx * p1.y - dy * p1.x;
        float dist = fabs(A * moving_ball.x + B * moving_ball.y + C) / sqrt(A * A + B * B);

        if (dist <= moving_ball_radius) {
            // 속도 벡터에 대해 벽의 법선 벡터로 반사
            float dot = velocity.x * nx + velocity.y * ny;
            velocity.x -= 2 * dot * nx / (nx * nx + ny * ny);
            velocity.y -= 2 * dot * ny / (nx * nx + ny * ny);
            break;
        }
    }
}

// 공과 고정된 공의 충돌 처리
void Collision_Detection_Between_Balls() {
    float dx = moving_ball.x - fixed_ball.x;
    float dy = moving_ball.y - fixed_ball.y;
    float dist = sqrt(dx * dx + dy * dy);

    if (dist <= radius1 + moving_ball_radius) {
        // 단순 반사
        float nx = dx / dist;
        float ny = dy / dist;

        float dot = velocity.x * nx + velocity.y * ny;
        velocity.x -= 2 * dot * nx;
        velocity.y -= 2 * dot * ny;

        collision_count++;
    }
}

void RenderScene(void) {
    glClearColor(1.0, 1.0, 0.0, 0.0); 
    glClear(GL_COLOR_BUFFER_BIT);

    Draw_Diamond();

    // 윈도우 중심의 위치에 고정된 공 그리기 
    glColor3f(1.0, 0.0, 0.0);
    Modeling_Circle(radius1, fixed_ball);

    // 충돌 검사
    Collision_Detection_Between_Balls();
    Collision_Detection_to_Walls();

    // 위치 업데이트
    moving_ball.x += velocity.x;
    moving_ball.y += velocity.y;

    // 움직이는 공 그리기 
    glColor3f(0.0, 0.0, 1.0);
    Modeling_Circle(moving_ball_radius, moving_ball);

    glutSwapBuffers();
    glutPostRedisplay(); // 계속 반복
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("Bounce Ball in Diamond");
    init();
    glutReshapeFunc(MyReshape);
    glutDisplayFunc(RenderScene);
    glutMainLoop();
    return 0;
}
