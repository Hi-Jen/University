#include <GL/glut.h>
#include <math.h>

#define Window_Width 800
#define Window_Height 800
#define PI 3.1415926
#define N 36   // 분할 개수

float top_radius = 1.0;   // 윗면 반지름
float bottom_radius = 2.0; // 아랫면 반지름
float height = 3.0;       // 높이

// 카메라 변수
double camera_radius, camera_theta, camera_phi;
float up = 1.0;

void axis(void) {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // x축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 0.0); // y축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);

    glColor3f(0.0, 0.0, 1.0); // z축
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
}

void DrawFrustum(void) {
    float angle_step = 2 * PI / N;

    // 옆면
    glColor3f(0, 1, 0);
    for (int i = 0; i < N; i++) {
        float theta1 = i * angle_step;
        float theta2 = (i + 1) * angle_step;

        // 위 원
        float x1_top = top_radius * cos(theta1);
        float y1_top = top_radius * sin(theta1);
        float x2_top = top_radius * cos(theta2);
        float y2_top = top_radius * sin(theta2);

        // 아래 원
        float x1_bot = bottom_radius * cos(theta1);
        float y1_bot = bottom_radius * sin(theta1);
        float x2_bot = bottom_radius * cos(theta2);
        float y2_bot = bottom_radius * sin(theta2);

        glBegin(GL_QUADS);
        glVertex3f(x1_top, y1_top, height / 2.0);   // 위 원
        glVertex3f(x2_top, y2_top, height / 2.0);
        glVertex3f(x2_bot, y2_bot, -height / 2.0); // 아래 원
        glVertex3f(x1_bot, y1_bot, -height / 2.0);
        glEnd();
    }

    glColor3f(1, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, height / 2.0); 
    for (int i = 0; i <= N; i++) {
        float theta = i * angle_step;
        float x = top_radius * cos(theta);
        float y = top_radius * sin(theta);
        glVertex3f(x, y, height / 2.0);
    }
    glEnd();

    glColor3f(0.0, 0.0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, -height / 2.0); 
    for (int i = 0; i <= N; i++) {
        float theta = i * angle_step;
        float x = bottom_radius * cos(theta);
        float y = bottom_radius * sin(theta);
        glVertex3f(x, y, -height / 2.0);
    }
    glEnd();
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    camera_radius = 10.0;
    camera_theta = 0.5;
    camera_phi = 0.3;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 1.0, 1000);
}

void camera_setting(void) {
    double x, y, z;
    x = camera_radius * cos(camera_theta) * cos(camera_phi);
    y = camera_radius * sin(camera_theta) * cos(camera_phi);
    z = camera_radius * sin(camera_phi);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera_setting();
    axis();
    DrawFrustum();

    glFlush();
}

void special_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  camera_theta -= 0.05; break;
    case GLUT_KEY_RIGHT: camera_theta += 0.05; break;
    case GLUT_KEY_UP:    camera_phi += 0.05; break;
    case GLUT_KEY_DOWN:  camera_phi -= 0.05; break;
    default: break;
    }
    glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': camera_radius += 0.5; break;
    case 's': camera_radius -= 0.5; break;
    default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(Window_Width, Window_Height);
    glutCreateWindow("Your 3D Circular truncated cone");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);
    glutSpecialFunc(special_key);
    glutMainLoop();
    return 0;
}
