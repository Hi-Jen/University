#include <gl/glut.h>  

//#define		_USE_MATH_DEFINES
#include <math.h>

#define		Window_Width	800
#define     Window_Height	800

#define		PI	3.1415926
#define		N	36			// �浵 360���� �������� �ϴ� ���� ��
#define		M	18			// ���� 180���� �������� �ϴ� ���� ��


float	ver[N][M + 1][3];	// ���� ���� ������ ����
float	sphere_radius;		// ������ �ݰ�

// ī�޶� ���� ����
float	camera_radius, camera_theta, camera_phi;

float	up = 1.0;


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



void Sphere(void) {

	// 삼각형 스트립으로 구 그리기
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_POLYGON);
			glVertex3fv(ver[i][j]);
			glVertex3fv(ver[i + 1][j]);
			glVertex3fv(ver[i + 1][j + 1]);
			glVertex3fv(ver[i][j + 1]);
			glEnd();
		}
	}
}




void init(void)
{
	glEnable(GL_DEPTH_TEST);
	sphere_radius = 1.0;
	camera_radius = 5.0;
	camera_theta = 0.3;
	camera_phi = 0.2;
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000);
}


void camera_setting(void)
{
	float	x, y, z;

	x = camera_radius * cos(camera_theta) * cos(camera_phi);
	y = camera_radius * sin(camera_theta) * cos(camera_phi);
	z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);

}


void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_setting();
	axis();

	// Your Sphere Code 
	Sphere();


	glFlush();

}

void Adjust_camera_up_vector(void) {

	if (camera_phi > 3.0 * PI / 2.0)
		camera_phi -= 2.0 * PI;
	else if (camera_phi < -3.0 * PI / 2.0)
		camera_phi += 2.0 * PI;

	if (camera_phi > PI / 2.0)
		up = -1.0;
	else if (camera_phi < -1.0 * PI / 2.0)
		up = -1.0;
	else
		up = 1.0;
}

void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:		camera_theta -= 0.01; 	break;
	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
	default: break;
	}
	Adjust_camera_up_vector();

	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':	camera_radius += 0.1; break;
	case 's':	camera_radius -= 0.1; break;
	default: break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("2D Sphere");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	glutSpecialFunc(special_key);
	glutMainLoop();
	return 0;
}