#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926
double camera_distance = 5.0;
double camera_theta = 0.5;
double camera_phi = 0.3;

BOOL viewing_type = true;

GLfloat		vertices[][3] = {
		{ -1.0, -1.0,  1.0 },		// 0 
		{ -1.0,  1.0,  1.0 },		// 1
		{ 1.0,  1.0,  1.0 },		// 2
		{ 1.0, -1.0,  1.0 },		// 3
		{ -1.0, -1.0, -1.0 },		// 4
		{ -1.0,  1.0, -1.0 },		// 5
		{ 1.0,  1.0, -1.0 },		// 6
		{ 1.0, -1.0, -1.0 } };		// 7

GLfloat		colors[][3] = {
		{ 1.0, 0.0, 0.0 },		// red
		{ 0.0, 1.0, 0.0 },		// green 
		{ 1.0, 1.0, 0.0 },		// yellow
		{ 1.0, 1.0, 1.0 },		// white
		{ 0.0, 0.0, 1.0 },		// blue
		{ 1.0, 0.0, 1.0 } };		// magenta


void polygon(int a, int b, int c, int d) { 
	glColor3fv(colors[a]);
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}


void cube(void) {
	polygon(3, 0, 4, 7);
	polygon(5, 4, 0, 1);
	polygon(4, 5, 6, 7);
	polygon(2, 3, 7, 6);	
	polygon(0, 3, 2, 1);
	polygon(1, 2, 6, 5);

	//polygon(3, 0, 4, 7); // Vertex의 번호
	//polygon(1, 2, 6, 5);
	//polygon(5, 4, 0, 1);
	//polygon(0, 3, 2, 1);
	//polygon(2, 3, 7, 6);
	//polygon(4, 5, 6, 7);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x = 빨간색 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y = 초록색
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z = 파란색
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void framebuffer_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	double camera_x, camera_y, camera_z;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (viewing_type)
		gluPerspective(60.0, 1.0, 1.0, 20.0);
	else
		glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 10.0); // 카메라의 위치가 5.0으로 잡혀 있기 때문에 

	camera_x = camera_distance * cos(camera_theta) * cos(camera_phi);
	camera_y = camera_distance * sin(camera_theta) * cos(camera_phi);
	camera_z = camera_distance * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera_x,camera_y, camera_z, 0.0, 0.0, 0.0, 0.0, 0.0, cos(camera_phi)); 
	//gluLookAt(3.0, 4.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	//순서대로 3.0, 4.0, 2.0 카메라 위치 좌표, 0.0, 0.0, 0.0 카메라 응시점, 0.0, 0.0, 1.0 업벡터가 카메라 위에 위치함.
	// 1.0, 0.0, 0.0 이 되면 X축인 빨간선이 카메라 위에 위치하게됨.
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	framebuffer_reset();
	camera();
	axis();
	glColor3f(1.0, 1.0, 0.0);
	cube();
	

	glFlush();
	glutSwapBuffers();
}
void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT: camera_theta -= 0.1; break;
	case GLUT_KEY_RIGHT: camera_theta += 0.1; break;
	case GLUT_KEY_DOWN: camera_phi -= 0.05; break;
	case GLUT_KEY_UP: camera_phi += 0.05; break;
	case GLUT_KEY_F1: viewing_type = !viewing_type; break;
	case GLUT_KEY_F2: camera_distance -= 0.1; break;
	case GLUT_KEY_F3: camera_distance += 0.1; break;
	default: break;
	}
	glutPostRedisplay();  
}


void specialkey() {
	glOrtho(-5, 5, -5, 5, -5, 5);
	gluPerspective(60, 1, 1, 5);
	glutPostRedisplay;
}



void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D_cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutMainLoop();
}
