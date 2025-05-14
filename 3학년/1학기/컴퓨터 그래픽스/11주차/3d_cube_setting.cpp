#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

GLfloat		vertices[][3] = {
		{ -1.0, -1.0,  1.0 },		// 0 
		{ -1.0,  1.0,  1.0 },			// 1
		{ 1.0,  1.0,  1.0 },			// 2
		{ 1.0, -1.0,  1.0 },			// 3
		{ -1.0, -1.0, -1.0 },		// 4
		{ -1.0,  1.0, -1.0 },		// 5
		{ 1.0,  1.0, -1.0 },			// 6
		{ 1.0, -1.0, -1.0 } };		// 7

GLfloat		colors[][3] = {
		{ 1.0, 0.0, 0.0 },				// red
		{ 0.0, 1.0, 0.0 },				// green 
		{ 1.0, 1.0, 0.0 },				// yellow
		{ 1.0, 1.0, 1.0 },				// white
		{ 0.0, 0.0, 1.0 },				// blue
		{ 1.0, 0.0, 1.0 } };			// magenta


void polygon(int a, int b, int c, int d) {
	glBegin(GL_POLYGON);
		glVertex3fv(vertices[a]);
		glVertex3fv(vertices[b]);
		glVertex3fv(vertices[c]);
		glVertex3fv(vertices[d]);
	glEnd();
}


void cube(void) {
	polygon(3, 0, 4, 7);
	polygon(1, 2, 6, 5);
	polygon(5, 4, 0, 1);
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(4, 5, 6, 7);
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
	glColor3f(1.0, 0.0, 0.0); // x√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z√‡ 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void framebuffer_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}


void display(void)
{
	framebuffer_reset();

	camera();

	glColor3f(1.0, 1.0, 0.0);
	cube();

	axis();

	glFlush();
	glutSwapBuffers();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D_cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}
