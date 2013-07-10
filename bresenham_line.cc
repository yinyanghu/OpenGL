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
    glColor3f(1.0, 0.0, 0.0);
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


void Bresenham_line(int x0, int y0, int x1, int y1)
{
	GLfloat x, y;
	x = x0; y = y0;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int signX = sign(x1, x0);
	int signY = sign(y1, y0);

	int flag = 0;
	if (dy > dx)
	{
		swap(dx, dy);
		flag = 1;
	}

	int e = dy * 2 - dx;
	for (int i = 0; i < dx; ++ i)
	{
        glBegin(GL_POINTS);
        glVertex3f(x, y, 0);
        glEnd();
		while (e > 0)
		{
			if (flag)
				x += signX;
			else
				y += signY;
			e = e - 2 * dx;
		}

		if (flag)
			y += signY;
		else
			x += signX;

		e = e + 2 * dy;
	}
}

int X0, Y0, X1, Y1;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	Bresenham_line(X0, Y0, X1, Y1);	

	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Please input start and end point (x0, y0, x1, y1):" << endl;
	cin >> X0 >> Y0 >> X1 >> Y1;

	char S[100];
	sprintf(S, "Bresenham Algorithm: Line (%d, %d) --> (%d, %d)", X0, Y0, X1, Y1);

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
