#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>


#define PI 3.1415926

int Width = 800;
int Height = 800;

float sun_radius = 0.2f;
float earth_radius = 0.07f;
float moon_radius = 0.03f;

float earth_orbit_radius = 0.6f;
float moon_orbit_radius = 0.15f;

float earthRotation = 0.0f;
float moonRotation = 0.0f;
float earth_rotation_speed = 0.045f; //지구속도
float moon_rotation_speed = 0.03f; //달 속도

void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 기본 단위로 설정

    sun_radius;
    earth_radius;
    moon_radius;

    earth_orbit_radius = 0.6f;
    moon_orbit_radius = 0.15f;
}

void Draw_Circle(float c_radius)
{
    float delta;
    int num = 36;

    delta = 2 * PI / num;
    glBegin(GL_POLYGON);
    for (int i = 0; i < num; i++)
        glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
    glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

    earthRotation += earth_rotation_speed;
    moonRotation += moon_rotation_speed;

    // 태양 : 빨간색의 구
    glColor3f(1.0, 0.0, 0.0);
    Draw_Circle(sun_radius); // 태양은 원점에 고정

    glPushMatrix();
    glRotatef(earthRotation, 0.0, 0.0, 1.0);   // 태양 중심 회전
    glTranslatef(earth_orbit_radius, 0.0, 0.0); // 회전 후 x축으로 이동
    glColor3f(0.0, 1.0, 0.0);
    Draw_Circle(earth_radius); // 지구 그리기

    glPushMatrix();
    glRotatef(moonRotation, 0.0, 0.0, 1.0);      // 지구 중심 회전
    glTranslatef(moon_orbit_radius, 0.0, 0.0); // 회전 후 이동
    glColor3f(1.0, 1.0, 0.0);
    Draw_Circle(moon_radius); // 달 그리기
    glPopMatrix();

    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Solar System");
    init();
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutMainLoop();
}
