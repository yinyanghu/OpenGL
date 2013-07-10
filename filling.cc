#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define N	30

#define Size	600

using namespace std;

int PointsX[N], PointsY[N];

int XX, YY;

bool Image[Size][Size];

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, Size - 1, 0.0, Size - 1);
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
		Image[(int)x][(int)y] = false;
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


/*
bool GetPixel(int x, int y)
{
	GLint pixel;
	glReadPixels(x, y, 1, 1, GL_RED, GL_INT, &pixel);
	return (pixel == 0) ? true : false;
}
*/

inline void DrawPixel(int x, int y)
{
	Image[x][y] = false;
	glBegin(GL_POINTS);
	glVertex3f(x, y, 0);
	glEnd();
}

void floodfill(int x, int y)
{
	if (x < 0 || x == Size || y < 0 || y == Size || !Image[x][y]) return;
	DrawPixel(x, y);	
	floodfill(x + 1, y);
	floodfill(x - 1, y);
	floodfill(x, y + 1);
	floodfill(x, y - 1);
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
	Image[xc + x][yc + y] = false;
	Image[xc - x][yc + y] = false;
	Image[xc + x][yc - y] = false;
	Image[xc - x][yc - y] = false;
	Image[xc + y][yc + x] = false;
	Image[xc + y][yc - x] = false;
	Image[xc - y][yc + x] = false;
	Image[xc - y][yc - x] = false;
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	memset(Image, true, sizeof(Image));

	/* Draw Random Shape */
	for (int i = 0; i < N - 1; ++ i)
		Bresenham_line(PointsX[i], PointsY[i], PointsX[i + 1], PointsY[i + 1]);	
	Bresenham_line(PointsX[N - 1], PointsY[N - 1], PointsX[0], PointsY[0]);	

	/* Generate Key Point */
	do
	{
		XX = rand() % Size;
		YY = rand() % Size;
	}
	while (!Image[XX][YY]);
	cout << XX << " " << YY << endl;

	/* Filling */
    glColor3f(0.0, 0.0, 1.0);
	floodfill(XX, YY);

	memset(Image, true, sizeof(Image));
	/* Draw Key Point */
    glColor3f(1.0, 0.0, 0.0);
	Bresenham_circle(XX, YY, 2);
	floodfill(XX, YY);

	glFlush();
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	
	for (int i = 0; i < N; ++ i)
	{
		PointsX[i] = rand() % Size;
		PointsY[i] = rand() % Size;
	}

	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Size, Size);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Filling Algorithm: Random Shape");

	glutKeyboardFunc(KeyboardAction);
	glutDisplayFunc(display);

	init();

	glutMainLoop();

	return 0;
}
