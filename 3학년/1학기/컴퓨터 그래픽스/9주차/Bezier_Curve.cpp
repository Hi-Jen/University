#include <GL/glut.h>
#include <cmath>
#include <iostream>

GLfloat ctrlPoints[4][2] = {
    {100.0, 100.0},  
    {150.0, 300.0},  
    {300.0, 300.0},  
    {400.0, 100.0}   
};

void bezierCurve(GLfloat t, GLfloat* x, GLfloat* y) {
    GLfloat u = 1 - t;
    *x = u*u*u * ctrlPoints[0][0] +
         3 * u*u * t * ctrlPoints[1][0] +
         3 * u * t*t * ctrlPoints[2][0] +
         t*t*t * ctrlPoints[3][0];

    *y = u*u*u * ctrlPoints[0][1] +
         3 * u*u * t * ctrlPoints[1][1] +
         3 * u * t*t * ctrlPoints[2][1] +
         t*t*t * ctrlPoints[3][1];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(ctrlPoints[i]);
    }
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        GLfloat x, y;
        bezierCurve(t, &x, &y);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("º£Áö¾î °î¼± (Bezier Curve)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
