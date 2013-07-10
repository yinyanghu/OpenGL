#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

using namespace std;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 599.0, 0.0, 599.0);
}

void KeyboardAction(unsigned char key, int x,int y)
{
	exit(0);
}

inline int sign(int a, int b)
{
	return (a > b) ? 1 : -1;
}


void DrawCirclePoints(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex3f(xc + x, yc + y, 0);
	glVertex3f(xc - x, yc + y, 0);
	glVertex3f(xc + x, yc - y, 0);
	glVertex3f(xc - x, yc - y, 0);
	glVertex3f(xc + y, yc + x, 0);
	glVertex3f(xc + y, yc - x, 0);
	glVertex3f(xc - y, yc + x, 0);
	glVertex3f(xc - y, yc - x, 0);
	glEnd();
}

void Bresenham_circle(int xc, int yc, int R)
{
	GLfloat x, y;
	int K;

	K = 3 - 2 * R;
	y = R;
	for (x = 0; x < y; ++ x)
	{
		DrawCirclePoints(xc, yc, x, y);
		if (K < 0)
			K += 4 * x + 6;
		else
		{
			K += 4 * (x - y) + 10;
			-- y;
		}
	}
	if (x == y)
		DrawCirclePoints(xc, yc, x, y);
}

int XC, YC, R;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	Bresenham_circle(XC, YC, R);

	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Please input the center and radius of circle (xc, yc, R):" << endl;
	cin >> XC >> YC >> R;

	char S[100];
	sprintf(S, "Bresenham Algorithm: Circle (%d, %d, %d)", XC, YC, R);

	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(S);

	glutKeyboardFunc(KeyboardAction);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}
