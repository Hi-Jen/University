// ���ڸ� ������� ��ġ��

#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

GLfloat		vertices[][3] = {
{ -1.0, -1.0,  1.0 },		// 0 
{ -1.0,  1.0,  1.0 },		// 1
{ 1.0,  1.0,  1.0 },		// 2
{ 1.0, -1.0,  1.0 },		// 3
{ -1.0, -1.0, -1.0 },		// 4
{ -1.0,  1.0, -1.0 },		// 5
{ 1.0,  1.0, -1.0 },		// 6
{ 1.0, -1.0, -1.0 } 		// 7
};

GLfloat		colors[][3] = {
{ 1.0, 0.0, 0.0 },			// red
{ 0.0, 1.0, 0.0 },			// green 
{ 1.0, 1.0, 0.0 },			// yellow
{ 1.0, 1.0, 1.0 },			// white
{ 0.0, 0.0, 1.0 },			// blue
{ 1.0, 0.0, 1.0 }			// magenta
};


int		view_type = 0;
float	c_distance, c_theta, c_phi;
float	up = 1.0;
int		animate_sign;
float	animate_time;
float	delta_time;


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

	polygon(4, 5, 6, 7); // �ٴڸ�

	// �����ʸ�
	glPushMatrix();
	glTranslatef(0.0, 1.0, -1.0);
	glRotatef(-1.0 * animate_time, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -1.0, 1.0);
	polygon(1, 2, 6, 5);
	glPopMatrix();


	// �޸�
	glPushMatrix();
	polygon(5, 4, 0, 1);
	glPopMatrix();

	// �ո�
	glPushMatrix();
	polygon(2, 3, 7, 6);
	glPopMatrix();


	// ���ʸ�
	glPushMatrix();
	polygon(3, 0, 4, 7);
	glPopMatrix();

	// ����
	glPushMatrix();
	polygon(0, 3, 2, 1);
	glPopMatrix();


}

void init(void)
{

	c_distance = 7.0;
	c_theta = 0.3;
	c_phi = 0.4;

	animate_sign = 0;
	animate_time = 0.0;
	delta_time = 0.1;

	glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_CULL_FACE);

}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
	gluPerspective(60.0, 1.0, 1.0, 20.0);
}

void axis(void) {

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z�� 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(void) {
	float	x, y, z;
	x = c_distance * cos(c_theta) * cos(c_phi);
	y = c_distance * sin(c_theta) * cos(c_phi);
	z = c_distance * sin(c_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);

}


void display(void)
{
	if (animate_sign % 2 == 1)
		animate_time += delta_time;



	frame_reset();

	camera();
	axis();

	cube();


	glFlush();
	glutSwapBuffers();
}

void MyKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':			glFrontFace(GL_CCW);	break;
	case 's':			glFrontFace(GL_CW);		break;
	case 't':			animate_sign++;			break;
	case 'n':			animate_time = 0.00;		break;
	default:	break;
	}
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:			c_theta -= 0.01;	break;
	case GLUT_KEY_RIGHT:		c_theta += 0.01;	break;
	case GLUT_KEY_DOWN:         c_phi -= 0.01;		break;
	case GLUT_KEY_UP:			c_phi += 0.01;		break;

	default:	break;
	}
	if (c_phi > 3.0 * PI / 2.0)
		c_phi -= 2.0 * PI;
	else if (c_phi < -3.0 * PI / 2.0)
		c_phi += 2.0 * PI;

	if (c_phi > PI / 2.0)
		up = -1.0;
	else if (c_phi < -1.0 * PI / 2.0)
		up = -1.0;
	else
		up = 1.0;

	glutPostRedisplay();


}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Flattening_Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(MyKey);
	glutIdleFunc(display);
	glutSpecialFunc(Special);
	glutMainLoop();
	return 0;
}
