#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>
using namespace std;

GLfloat ctrlpoints[4][4][3]={
	{{-1.5,-1.5,4.0},{-0.5,-1.5,2.0},{0.5,-1.5,-1.0},{1.5,-1.5,2.0}},
	{{-1.5,-0.5,1.0},{-0.5,-0.5,3.0},{0.5,-0.5,0.0},{1.5,-0.5,-1.0}},
	{{-1.5,0.5,4.0},{-0.5,0.5,0.0},{0.5,0.5,3.0},{1.5,0.5,4.0}},
	{{-1.5,1.5,-2.0},{-0.5,1.5,-2.0},{0.5,1.5,0.0},{1.5,1.5,-1.0}}
};

int numOfGrid=20;
bool isDrawMesh=true;
bool isWhiteLight=true;

void initNumOfGrid()
{
	numOfGrid=20;
}

void makeGridintensive()
{
	if(numOfGrid>=100)
	{
		return;
	}
	numOfGrid+=20;
}

void setToDrawSurface()
{
	isDrawMesh=false;
}

void setToDrawMesh()
{
	isDrawMesh=true;
}

void setToUseWhiteLight()
{
	isWhiteLight=true;
}

void setToUseBlueLight()
{
	isWhiteLight=false;
}

void initlightA()
{
	GLfloat ambient[]={0.2,0.2,0.2,1.0};
	GLfloat position[]={0.0,0.0,2.0,1.0};
	GLfloat mat_diffuse[]={0.6,0.6,0.6,1.0};
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

void initlightB()
{
	GLfloat ambient[]={0.0,0.0,1.0,1.0};
	GLfloat position[]={2.0,2.0,1.0,1.0};
	GLfloat mat_diffuse[]={0.5,0.5,0.5,1.0};
	GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={50.0};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}

void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glEnable(GL_DEPTH_TEST);
	glMap2f(GL_MAP2_VERTEX_3,0,1,3,4,0,1,12,4,&ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(numOfGrid,0.0,1.0,numOfGrid,0.0,1.0);
	if(isWhiteLight)
	{
		initlightA();
	}
	else
	{
		initlightB();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(85.0,1.0,1.0,1.0);
	init();
	if(isDrawMesh)
	{
		glEvalMesh2(GL_LINE,0,numOfGrid,0,numOfGrid);
	}
	else
	{
		glEvalMesh2(GL_FILL,0,20,0,20);
	}
	glPopMatrix();
	glFlush();
}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
	{
		glOrtho(-5.0,5.0,-5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w,-5.0,5.0);
	}
	else
	{
		glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h,-5.0,5.0,-5.0,5.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboardAction(unsigned char key, int x,int y)
{
	switch(key)
	{
	case 'v':
		initNumOfGrid();
		setToDrawMesh();
		glutPostRedisplay();
		break;
	case 'b':
		makeGridintensive();
		setToDrawMesh();
		glutPostRedisplay();
		break;
	case 'n':
		setToDrawSurface();
		initNumOfGrid();
		setToUseWhiteLight();
		initlightA();
		glutPostRedisplay();
		break;
	case 'm':
		setToDrawSurface();
		initNumOfGrid();
		setToUseBlueLight();
		initlightB();
		glutPostRedisplay();
		break;
	default:
		exit(0);
	}
}

int main(int argc,char **argv)
{
	printf("[v]:初始化模型,显示最稀疏的网格.\n");
	printf("[b]:网格细化,对初始模型可细化4次.\n");
	printf("[n]:使用白光的光照,显示白光光照下的模型.\n");
	printf("[m]:使用蓝光的光照,显示蓝光光照下的模型.\n");

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize(800,800);
	glutInitWindowPosition(200,100);
	glutCreateWindow("Bezier Surface");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardAction);

	glutMainLoop();
	return 0;
}
