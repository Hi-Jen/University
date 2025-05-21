#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		Window_Width	800
#define		Window_Height	800

int			point[100][2];
int			num = 0;


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

void Draw_Bezier_Curve(void) {
	double	px, py;
	double	sumx, sumy;
	double	time;
	double	function_value;
	double  partial_time;
	int		curvepoint_num = 100;
	int		curve_degree;

	glColor3f(1.0, 1.0, 0.0);

	curve_degree = num - 1;
	partial_time = 1.0 / curvepoint_num;

	px = point[0][0];
	py = point[0][1];

	glBegin(GL_LINE_STRIP);
	for (time = partial_time; time <= 1.0; time += partial_time) {
		sumx = sumy = 0.0;
		for (int k = 0; k <= curve_degree; k++) {
			function_value = Bernstein(curve_degree, k, time);
			sumx += function_value * point[k][0];
			sumy += function_value * point[k][1];
		}
		glVertex2d(sumx, sumy);
		px = sumx;
		py = sumy;
	}
	sumx = point[curve_degree][0];
	sumy = point[curve_degree][1];
	glVertex2d(px, py);
	glVertex2d(sumx, sumy);
	glEnd();
}
void Draw_Control_Points(void) {

	glPointSize(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (int k = 0; k < num; k++) {
		glVertex2f(point[k][0], point[k][1]);
	}
	glEnd();

}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 0.0, 0.0);

	if (num >= 1)
		Draw_Control_Points();
	if (num >= 2)
		Draw_Bezier_Curve();

	glFlush();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION); // Set projection parameters.
	glLoadIdentity();
	gluOrtho2D(0, Window_Width, 0, Window_Height);
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		point[num][0] = x;
		point[num][1] = Window_Height - y;
		num++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		num = 0;
	}
	glutPostRedisplay();
	RenderScene();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Bezier Curve");
	init();
	glutDisplayFunc(RenderScene);
	glutMouseFunc(mouse);
	glutMainLoop();
}