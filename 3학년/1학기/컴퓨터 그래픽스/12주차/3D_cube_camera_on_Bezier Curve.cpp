#include <gl/glut.h>
#include <gl/gl.h>
#include <stdio.h>
#include <math.h>

#define	PI	3.1415926

double	c_distance, c_theta, c_phi;

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
		{ 1.0, 0.0, 0.0 },			// red
		{ 0.0, 1.0, 0.0 },			// green 
		{ 1.0, 1.0, 0.0 },			// yellow
		{ 1.0, 1.0, 1.0 },			// white
		{ 0.0, 0.0, 1.0 },			// blue
		{ 1.0, 0.0, 1.0 } };		// magenta


int			point[100][3];
int			p_num = 0;
int			camera_moving_on = 0;
double		simulation_time, simulation_step;

typedef struct _point3D {
	float	x;
	float	y;
	float	z;
} point3D;



void Make_Camera_Control_Point(void) {
	float	x, y, z;

	point[p_num][0] = c_distance * cos(c_theta) * cos(c_phi);
	point[p_num][1] = c_distance * sin(c_theta) * cos(c_phi);
	point[p_num][2] = c_distance * sin(c_phi);
	p_num++;

	point[p_num][0] = 0.0;
	point[p_num][1] = 0.0;
	point[p_num][2] = 0.0;
	p_num++;

	point[p_num][0] = c_distance * cos(c_theta + 1.0) * cos(c_phi + 0.2);
	point[p_num][1] = c_distance * sin(c_theta + 1.0) * cos(c_phi + 0.2);
	point[p_num][2] = c_distance * sin(c_phi + 0.2);
	p_num++;
}

void init(void)
{
	c_distance = 5.0;
	c_theta = 0.6;
	c_phi = 0.5;

	simulation_time = 0.0;
	simulation_step = 0.0001;

	Make_Camera_Control_Point();

	glEnable(GL_DEPTH_TEST);
}


int	Factorial(int k) {

	if (k <= 1)
		return 1;
	else {
		return k * Factorial(k - 1);
	}
}

double Combination(int n, int k) {
	double	value;
	if (n >= 1 && k <= n)
		value = Factorial(n) / (Factorial(n - k) * Factorial(k));
	else
		value = 1;
	return value;
}

double Bernstein(int n, int k, double time) {
	double value;
	if (0.0 <= time && time <= 1.0)
		value = Combination(n, k) * pow(1.0 - time, n - k) * pow(time, k);
	else
		value = 1.0;
	return value;
}

point3D Curve_Position(float time) {
	float	sumx, sumy, sumz;
	float	function_value;
	int		curve_degree;
	point3D position;

	curve_degree = p_num - 1;
	sumx = sumy = sumz = 0.0;
	for (int k = 0; k <= curve_degree; k++) {
		function_value = Bernstein(curve_degree, k, time);
		sumx += function_value * point[k][0];
		sumy += function_value * point[k][1];
		sumz += function_value * point[k][2];
	}
	position.x = sumx;
	position.y = sumy;
	position.z = sumz;

	return position;
}

void Draw_Bezier_Curve(void) {
	double	px, py, pz;
	double	sumx, sumy, sumz;
	double	time;
	double	function_value;
	double  partial_time;
	int		curvepoint_num = 100;
	int		curve_degree;
	point3D position;

	glColor3f(1.0, 1.0, 0.0);

	curve_degree = p_num - 1;
	partial_time = 1.0 / curvepoint_num;

	glBegin(GL_LINE_STRIP);
	glVertex3d(point[0][0], point[0][1], point[0][2]);

	for (time = partial_time; time <= 1.0; time += partial_time) {
		position = Curve_Position(time);
		glVertex3d(position.x, position.y, position.z);
	}
	glVertex3d( point[curve_degree][0], point[curve_degree][1], point[curve_degree][2] );
	glEnd();
}


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
	polygon(2, 3, 7, 6);
	polygon(4, 5, 6, 7);
	polygon(3, 0, 4, 7);
	polygon(1, 2, 6, 5);
	polygon(5, 4, 0, 1);
	polygon(0, 3, 2, 1);

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
	glColor3f(1.0, 0.0, 0.0); // x 빨간색
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y 초록색
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z 파란색
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}

void frame_reset(void) {
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void camera(float	time) {
	float	x, y, z;
	point3D position, camera_position;

	camera_position.x = c_distance * cos(c_theta) * cos(c_phi);
	camera_position.y = c_distance * sin(c_theta) * cos(c_phi);
	camera_position.z = c_distance * sin(c_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (camera_moving_on % 2 == 1) {
		position = Curve_Position(time);
		gluLookAt(position.x, position.y, position.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	}
	else {
		gluLookAt(camera_position.x, camera_position.y, camera_position.z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	}
}


void display(void)
{

	frame_reset();

	if (camera_moving_on % 2) {
		if (simulation_time >= 1.0)
			simulation_time = 0.0;
		simulation_time += simulation_step;
	}
	if (simulation_time >= 1.0)
		simulation_time = 1.0;

	camera(simulation_time);
	axis();
	cube();
	glLineWidth(2.0);
	glColor3f(1.0, 1.0, 1.0);
	Draw_Bezier_Curve();
	glLineWidth(1.0);

	glFlush();
	glutSwapBuffers();
}

void myKey(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':		c_distance += 0.01;	break;
	case 's':		c_distance -= 0.01;	break;
	default:							break;
	}
	glutPostRedisplay();

}

void Special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:		c_theta -= 0.01;	break;
	case GLUT_KEY_RIGHT:	c_theta += 0.01;	break;
	case GLUT_KEY_DOWN:		c_phi -= 0.01;		break;
	case GLUT_KEY_UP:		c_phi += 0.01;		break;
	case GLUT_KEY_F1:		camera_moving_on++; break;
	default:									break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3D_cube_camera_on_Bezier Curve");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKey);
	glutSpecialFunc(Special);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
