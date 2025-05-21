#define BRICK_GAME_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

#define WIDTH 1000
#define HEIGHT 800
#define PI 3.14159265
#define PADDLE_WIDTH 80
#define PADDLE_HEIGHT 10
#define BALL_RADIUS 10
#define GRAVITY 0.3f
#define SPEED_INCREASE 1.1f
#define PADDLE_SPEED 0.15f
#define MAX_FALL_SPEED -10.0f

#define BRICK_WIDTH 50
#define BRICK_HEIGHT 20
#define BRICK_MARGIN 6
#define MAX_BRICKS 100

typedef struct {
    float x, y;
} Point;

typedef struct {
    float x, y;
    bool visible;
    float r, g, b;
} Brick;

extern Point pentagon[5];
extern Brick bricks[MAX_BRICKS];
extern float paddleT;
extern float paddleX, paddleY;
extern float ballX, ballY;
extern float ballDX, ballDY;
extern float speedBoostTimer;
extern float normalSpeedMultiplier;
extern float currentSpeedMultiplier;
extern float ballColorR, ballColorG, ballColorB;
extern int brickCount;
extern int paddleHitCount;
extern bool speedBoosted;
extern bool gameClear;
float pointToSegmentDistance(Point A, Point B, Point P);

void initPentagon();
void updatePaddlePosition();
void initBricks();
void drawBricks();
void drawPentagon();
void drawPaddle();
void drawBall();
void checkWallCollisions();
void checkPaddleCollision();
void checkBrickCollisions();
void update(int value);
void keyboard(int key, int x, int y);
void display();
void reshape(int w, int h);

Point pentagon[5];
float paddleT = 0.5f;
float paddleX, paddleY;
float ballX, ballY;
float ballDX = 2.0f, ballDY = 0.0f;
float gameClearFlashTimer = 0.0f;

Brick bricks[MAX_BRICKS];
int brickCount = 20;
int paddleHitCount = 0;
bool speedBoosted = false;
bool gameCleared = false;
bool gameStarted = false;
bool waitingForStart = true;
bool countdownActive = false;

int countdownValue = 4;
int countdownTimerId = 0;
int countdownNumber = 4;

float speedBoostTimer = 0.0f;
float normalSpeedMultiplier = 1.0f;
float currentSpeedMultiplier = 1.0f;
float ballColorR = 0.0f, ballColorG = 0.0f, ballColorB = 1.0f;
float startTime = 0.0f;
float clearTime = 0.0f;
float bestRecord = 0.0f;
bool hasBestRecord = false;