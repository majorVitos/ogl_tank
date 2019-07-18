

#if defined _MSC_VER
#include <windows.h>
#define _USE_MATH_DEFINES

#else
#define _STDCALL_SUPPORTED
#define _M_IX86
#endif
#include <gl/GL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cmath>

#include "elements.h"

#include "GL/glut.h"

unsigned detal = 10;

int mainWindow, padWindow;

int MouseDownStartX, MouseDownStartY;
int Mousedx, Mousedy;
int toogleFog = 0;
float fogDendity = 1, fogcolor[] = {0.4f, 0.3f, 0.35f, 0.8f};
int toogleLight = 1, uselist = 1;
int xpos = 0, zpos = 0;

int toogleTexture = 1, toogleAnimate = 0, toogleConsist = 0, toogleRotate = 0, toogleFrustum = 1;

void draw_t34();
void t34_init();

void RotateFromMouse()
{
		glMatrixMode(GL_PROJECTION);

		if(Mousedx)
			glRotatef(float(Mousedx), 0.f, 1.f, 0.f);
		if(Mousedy)
			glRotatef(float(Mousedy), 1.f, 0.f, 0.f);
			
		glTranslated(0.2*xpos, 0, 0.2*zpos);
		glMatrixMode(GL_MODELVIEW);

		xpos = zpos = 0;
		Mousedx = Mousedy = 0;
}

void DrawFig1(int solid)
{
	glPushMatrix();
	glTranslatef(-0.5f, 0.2f, -1.f);
	glScalef(0.1f, 0.1f, 0.1f);
	
	glColor4f(0.f, 1.f, 0.f, 1.f);
	if(solid)
		//glutSolidDodecahedron();
		glutSolidTorus(0.3, 0.5, 10, 10);
	else
		glutWireDodecahedron();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glScalef(0.2, 0.2, 0.2);
	glColor4f(0.5, 0.6, 0.2, 1);
	if(solid)
		glutSolidDodecahedron();
		//glutSolidTorus(0.3, 0.5, 10, 10);
	else
		glutWireDodecahedron();
	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, -0.2, -0.3);
	glRotatef(30, 1, 0, 1);
	glScalef(0.3, 0.3, 0.3);
	glColor4f(1, 0.9, 0, 1);
	if(solid)
		//glutSolidDodecahedron();
		glutSolidTorus(0.3, 0.5, 10, 10);
	else
		glutWireDodecahedron();
	glPopMatrix();
}

void DrawFig2(int N, double r)
{
	double x, y;
	double ci = 0.8;
	for( int i = 0; i < N; i++)
	{
		glColor4f( ci*float(rand())/float(RAND_MAX), ci*float(rand())/float(RAND_MAX), ci*float(rand())/float(RAND_MAX), 1); 
		glPushMatrix();
		x = cos( 2*M_PI/double(N) * double(i) );
		y = sin(  2*M_PI/double(N) * double(i) );
		glTranslated( x, y, 0);
		//glutWireSphere(r, 10, 10);
		glutSolidSphere(r, 30, 30);
		glPopMatrix();
	}
	
	glColor4ub(128, 0, 130, 255);
	//glColor4f(0.5, 0, 0.6, 1);
	glutSolidCube(0.6);
}

void DrawFig2_2(int N, double r)
{
	double x, y, dr = 0.2;
	
	for(int i = 0; i < N; i++)
	{
		glPushMatrix();
		x = (r + dr*double(i) )*cos( 2.*M_PI/8. * double(i) );
		y = (r + dr*double(i) )*sin( 2.*M_PI/8. * double(i) );
		glScaled(0.3, 0.3, 0.3);
		glTranslated(x, y, -0.5*double(i));
		DrawFig2(10, 0.4);
		glPopMatrix();
	}
}

void draw_square()
{
	//Площадка
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 0, 1);
	glVertex3f(-1, -1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(1, 1, 0);
	
	glNormal3f(1, 0, 0);
	glVertex3f(1, -1, -0.1);
	glVertex3f(1, 1, -0.1);
	
	glNormal3f(0, 0, -1);
	glVertex3f(-1, -1, -0.1);
	glVertex3f(-1, 1, -0.1);
	
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(-1, 1, 0);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, -1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(-1, -1, -0.1);
	glVertex3f(1, -1, -0.1);
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, 1, -0.1);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, -0.1);
	glEnd();
	
	//Опоры
	glPushMatrix();
	glTranslatef(0.9, 0.9, 0);
	glColor3f(0.35, 0.1, 0.15);
	draw_cylinder_my(0.1, 0.05, 20, 20, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.9, 0.9, 0);
	glColor3f(0.35, 0.1, 0.15);
	draw_cylinder_my(0.1, 0.05, 20, 20, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.9, -0.9, 0);
	glColor3f(0.35, 0.1, 0.15);
	draw_cylinder_my(0.1, 0.05, 20, 20, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-0.9, -0.9, 0);
	glColor3f(0.35, 0.1, 0.15);
	draw_cylinder_my(0.1, 0.05, 20, 20, 0);
	glPopMatrix();
	//****
}

void DisplayWork()
{
	unsigned dispList = 0;
	unsigned angle = 0;
	
	glClearColor(0.4, 0.2, 0.1, 1);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	if( Mousedx || Mousedy )
		RotateFromMouse();

	
	if(toogleLight)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
	}
	if(toogleFog)
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, (toogleFog == 1)*GL_LINEAR + (toogleFog == 2)*GL_EXP + (toogleFog == 3)*GL_EXP2 );
		glFogf(GL_FOG_DENSITY, fogDendity);
		glFogfv(GL_FOG_COLOR, fogcolor);
	}
		
	//glEnable(GL_NORMALIZE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glPushMatrix();
	if(toogleRotate)
	{
		if(toogleRotate == 2)
			glRotatef(30, -1, 0, 0);
		if(toogleRotate == 3)
			glRotatef(60, 0, 1, 0);
		glRotatef(angle++, 0, 0, 1);
	}
	draw_t34();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 0, -1);
	//Площадка
	glColor3f(0.5, 0, 0);
	draw_square();
	glPopMatrix();
	
	if(toogleFog)
	{
		glDisable(GL_FOG);
	}
	if(toogleLight)
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
	}
	glFlush();
	glutSwapBuffers();
}

void updateProjection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(toogleFrustum)
		glFrustum(-1, 1, -1, 1, 0.8, 40);
	else
	{
		glOrtho(-1, 1, -1, 1, 0.6, 40);
		glTranslated(0, 0, -2.5);
	}

	glTranslated(0, 0, -2.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Reshape( int Width, int Height)
{
	glViewport(0, 0, Width, Height);

	updateProjection();
	glEnable(GL_DEPTH_TEST);
}

void Mouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		MouseDownStartX = x;
		MouseDownStartY = y;
	}
	if( state == GLUT_UP)
	{
		Mousedx = 0;
		Mousedy = 0;
	}
}

void MouseMotion(int x, int y)
{
	Mousedx = x - MouseDownStartX;
	Mousedy = y - MouseDownStartY;

	MouseDownStartX = x;
	MouseDownStartY = y;

	printf("mouse move dx = %i\t\tdy = %i\n", Mousedx, Mousedy);
}

void KeyBoardFunc(unsigned char key, int x, int y)
{
	switch(key)
	{
		case '0':
		case ')':
			//glutDisplayFunc( DisplayDefault );
		break;

		case '1':
		case '!':
			//glutDisplayFunc( DisplayWork1 );
		break;


		case '2':
			//glutDisplayFunc( DisplayWork2 );
		break;
		
		
		case '3':
			//glutDisplayFunc( DisplayWork3 );
		break;
		
		
		case 'a':
		case 'A':
			if(toogleAnimate++)
				toogleAnimate = 0;
		break;

		
		case 'r':
		case 'R':
			if(toogleRotate++ == 3)
				toogleRotate = 0;
		break;
		
		case 'f':
		case 'F':
			if(++toogleFog == 4)
				toogleFog = 0;
		break;
		
		case 'g':
		case 'G':
			fogDendity += 0.2f;
			if(fogDendity > 20)
				fogDendity = 0.1f;
		break;
		
		case 'c':
		case 'C':
			if(toogleConsist++)
				toogleConsist = 0;
				
		case 't':
		case 'T':
			if(toogleTexture++)
				toogleTexture = 0;
		break;
		
		case 'l':
		case 'L':
			toogleLight++;
			if(toogleLight == 2)
				toogleLight = 0;
		break;
		
		
		case 'u':
		case 'U':
			if(uselist)
				uselist = 0;
			else
				uselist = 1;
		break;
		
		case 'p':
		case 'P':
			if(toogleFrustum++)
				toogleFrustum = 0;
			updateProjection();
		break;
		
		case 27:
			glutIdleFunc( 0 );
			glutDestroyWindow(1);
			exit(0);
			
		break;
	}
}

void SpecialKeyFunc(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			xpos--;
		break;
		
		case GLUT_KEY_RIGHT:
			xpos++;
		break;
		
		case GLUT_KEY_UP:
			zpos++;
		break;
		
		case GLUT_KEY_DOWN:
			zpos--;
		break;
		
		default:
		break;
	}
	RotateFromMouse();
}

void Idle()
{
	
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	mainWindow = glutCreateWindow("tank");
	glutDisplayFunc( DisplayWork );
	glutReshapeFunc( Reshape );
	glutMouseFunc( Mouse );
	glutMotionFunc( MouseMotion );
	glutKeyboardFunc(KeyBoardFunc );
	glutSpecialFunc( SpecialKeyFunc );
	glutIdleFunc( Idle );
	glutShowWindow();
	t34_init();
	glutMainLoop();
	return 0;
}
