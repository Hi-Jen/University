#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#define PI 3.14159265358979323846
#include <cmath>

int radius = 230;
int num = 17;
void Draw_Axis(void) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(200, 0);
    glVertex2f(-200, 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0, -200);
    glVertex2f(0, 200);
    glEnd();
}

void drawCircle(void) {

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num; i++) {
        float angle = 2.0f * PI * i / num;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void Camera_Lense(void) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);

}

void RenderScene(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Modeling Objects -------- 

    Camera_Lense();
    Draw_Axis();
    drawCircle();

    glFlush();
}

void myKey(unsigned char key, int x, int y) {
    switch (key) {
    case 'n': num++;  break;
    case 'm': if (num > 3)num--;  break;
    case 'w': radius++; break;
    case 's': radius--; break;
    default: break;
    }
    glutPostRedisplay();
}

void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 150);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Welcome to Computer Graphics");
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(myKey);
    glutMainLoop();
    return;
}