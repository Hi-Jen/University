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
float zoom = 1.0;
float radius = 30.0;

typedef struct _Point {
    float x;
    float y;
} Point;

Point circles[1000];
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

void DrawRectangle() {
    glColor3f(0.0, 1.0, 0.0);  
    glBegin(GL_POLYGON);
    glVertex2f(150.0f, 250.0f);
    glVertex2f(150.0f, 350.0f);
    glVertex2f(250.0f, 350.0f);
    glVertex2f(250.0f, 250.0f);
    glEnd();
}

void Modeling_Circle(Point CC) {
    float delta = 2 * PI / polygon_num;
    glColor3f(1.0, 0.0, 0.0); 
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
    gluOrtho2D(left, left + width / zoom, bottom, bottom + height / zoom);

    Modeling_Axis();
    DrawRectangle();

    Point center;
    center.x = 200.0f;
    center.y = 150.0f;
    Modeling_Circle(center);  

    glFlush();
}


void mouse1(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        float worldX = left + x * (width / zoom) / width;
        float worldY = bottom + (height - y) * (height / zoom) / height;

        if (button == GLUT_LEFT_BUTTON) {
            zoom *= 1.2;
            left = worldX - (width / zoom) / 2;
            bottom = worldY - (height / zoom) / 2;
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            zoom /= 1.2;
            left = worldX - (width / zoom) / 2;
            bottom = worldY - (height / zoom) / 2;
        }
    }
    glutPostRedisplay();
}

void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: left -= 10 / zoom; break;
    case GLUT_KEY_RIGHT: left += 10 / zoom; break;
    case GLUT_KEY_DOWN: bottom -= 10 / zoom; break;
    case GLUT_KEY_UP: bottom += 10 / zoom; break;
    default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Zoom in Zoom out");
    glutDisplayFunc(RenderScene);
    glutMouseFunc(mouse1);
    glutSpecialFunc(MySpecial);
    glutMainLoop();
    return 0;
}
