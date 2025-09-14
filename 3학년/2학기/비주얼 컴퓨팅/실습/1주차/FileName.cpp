#include <GL/glut.h>
#include <math.h>

#define Window_Width 800
#define Window_Height 800

#define PI 3.1415926
#define N 36   // �浵 ����
#define M 18   // ���� ����

float ver[N + 1][M + 1][3];   // �� ��ǥ ����
float sphere_radius = 1.0;

float camera_radius = 5.0, camera_theta = 0.3, camera_phi = 0.2;
float up = 1.0;

void axis(void) {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0); // X
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0); // Y
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10); // Z
    glEnd();
}

// ������ �簢�� �������� ������
void Sphere(void) {
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < N; i++) {
            glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glVertex3fv(ver[i][j]);
            glVertex3fv(ver[i + 1][j]);
            glVertex3fv(ver[i + 1][j + 1]);
            glVertex3fv(ver[i][j + 1]);
            glEnd();
        }
    }
}

void init(void) {
    glEnable(GL_DEPTH_TEST);

    // �� �� ��ǥ ���
    for (int i = 0; i <= N; i++) {
        float theta = (float)i / N * 2.0f * PI;
        for (int j = 0; j <= M; j++) {
            float phi = (float)j / M * PI - PI / 2.0f;
            ver[i][j][0] = sphere_radius * cos(theta) * cos(phi);
            ver[i][j][1] = sphere_radius * sin(theta) * cos(phi);
            ver[i][j][2] = sphere_radius * sin(phi);
        }
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
}

void camera_setting(void) {
    float x = camera_radius * cos(camera_theta) * cos(camera_phi);
    float y = camera_radius * sin(camera_theta) * cos(camera_phi);
    float z = camera_radius * sin(camera_phi);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0, 0, 0, 0, 0, up);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera_setting();
    axis();

    Sphere();

    glutSwapBuffers();
}

void Adjust_camera_up_vector(void) {
    if (camera_phi > 3.0 * PI / 2.0) camera_phi -= 2.0 * PI;
    else if (camera_phi < -3.0 * PI / 2.0) camera_phi += 2.0 * PI;

    if (camera_phi > PI / 2.0) up = -1.0;
    else if (camera_phi < -PI / 2.0) up = -1.0;
    else up = 1.0;
}

void special_key(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:  camera_theta -= 0.01; break;
    case GLUT_KEY_RIGHT: camera_theta += 0.01; break;
    case GLUT_KEY_UP:    camera_phi += 0.01;   break;
    case GLUT_KEY_DOWN:  camera_phi -= 0.01;   break;
    }
    Adjust_camera_up_vector();
    glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': camera_radius += 0.1; break;
    case 's': camera_radius -= 0.1; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Window_Width, Window_Height);
    glutCreateWindow("Your 3D Sphere");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mykey);
    glutSpecialFunc(special_key);
    glutMainLoop();
    return 0;
}
