#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>

#define width 400
#define height 600
#define PI 3.1415
#define polygon_num 30

int left = 0;
int bottom = 0;

float radius = 10.0;
float point[1000][2];
int point_num = 0;

typedef struct _Point {
    float x;
    float y;
} Point;

Point circles[1000]; // 여러 개의 원 저장
int circle_count = 0;

void Modeling_Axis(void) {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(0, 0);
    glVertex2i(1.0 * width, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 1.0 * height);
    glEnd();
}

void Modeling_Circle(Point CC) {
    float delta = 2 * PI / polygon_num;
    glBegin(GL_POLYGON);
    for (int i = 0; i < polygon_num; i++) {
        glVertex2f(CC.x + radius * cos(delta * i), CC.y + radius * sin(delta * i));
    }
    glEnd();
}

void RenderScene(void) {
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, left + width, bottom, bottom + height);

    Modeling_Axis();

    // 저장된 원들을 모두 그림
    for (int i = 0; i < circle_count; i++) {
        Modeling_Circle(circles[i]);
    }

    glFlush();
}

void mouse1(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (circle_count < 1000) {
            circles[circle_count].x = x;
            circles[circle_count].y = height - y;
            circle_count++;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        circle_count = 0; // 화면 초기화
    }
    glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: left += 1.0; break;
    case GLUT_KEY_RIGHT: left -= 1.0; break;
    case GLUT_KEY_DOWN: bottom += 1.0; break;
    case GLUT_KEY_UP: bottom -= 1.0; break;
    default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Draw Circles by Mouse Input");
    glutDisplayFunc(RenderScene);
    glutMouseFunc(mouse1);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}
