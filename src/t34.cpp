
#if defined _MSC_VER
#include <windows.h>
#define _USE_MATH_DEFINES
#else
#define _STDCALL_SUPPORTED
#define _M_IX86
#endif

#include <GL/GL.h>


#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "GL/glut.h"
#include "elements.h"


std::string media_path = "../media/";

extern unsigned detal;
extern int toogleTexture, toogleAnimate, toogleConsist;

unsigned t34textures[6];
unsigned char* TgaRead(const std::string FileName, unsigned& width, unsigned& height);

void draw_1ring(const double inerR, const double outR, const unsigned N)
{
	float x, y, k;
	
	k = 2.*M_PI/float(N);
	
	glNormal3f(0, 0, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(outR, 0, 0);
	glVertex3f(inerR, 0, 0);
	
	for(unsigned i = 1; i < N + 1; i++)
	{
		x = cos( k*float(i) );
		y = sin( k*float(i) );
		glVertex3f( outR*x, outR*y, 0);
		glVertex3f( inerR*x, inerR*y, 0);
	}
	glEnd();
}


//#define detal 10
void draw_base_wheel(double r)
{
	//glNormal3f(0, 0, 1);
	//draw_disk_my(r, detal);
	
	//сама болванка
	glPushMatrix();
	glTranslatef(0, 0, -0.8*r);
	draw_cylinder_my( r, r*0.8, detal, detal, detal);
	glPopMatrix();
	
	//мостовое основание
	//glColor3f(0, 1, 0);
	draw_cylinder_my( r * 0.3, r*0.05, detal, detal, 0);
	glPushMatrix();
	glTranslatef(0, 0, r*0.05);
	glScalef(4, 4, 1);
	glutSolidSphere( r * 0.06, detal, detal);
	glPopMatrix();
	//мостовой болт
	glPushMatrix();
	glTranslatef(0, 0, r*(0.05 + 0.06) );
	draw_cylinder_my( r * 0.03, r*0.05, detal >> 1, detal >> 1, 0);
	glPopMatrix();
	//внешнее колесо
	glPushMatrix();
	//glColor4f(0.1, 0.1, 0.1, 1);
	glTranslatef(0, 0, r*(0.05 + 0.06 + 0.05) );
	draw_1ring(r, r*0.8, detal);
	glPopMatrix();
	draw_cylinder_my( r, r*(0.05 + 0.06 + 0.05), detal, 0, 0);
	draw_cylinder_my( r*0.8, r*(0.05 + 0.06 + 0.05), detal, 0, 0);
	
	//внутренние болты
	for(unsigned i = 0; i < 3; i++)
	{
		glPushMatrix();
		glRotatef(60. - 60.f*float(i), 0, 0, 1); 
		glTranslatef(0, r * 0.4, 0);
		draw_cylinder_my( r * 0.03, r*0.05, detal >> 1, detal >> 1, 0);
		glPopMatrix();
	}
	//внешние болты
	for(unsigned i = 0; i < 10; i++)
	{
		glPushMatrix();
		glRotatef(36.*float(i), 0, 0, 1); 
		glTranslatef(0, r * 0.6, 0);
		draw_cylinder_my( r * 0.03, r*0.05, detal >> 1, detal >> 1, 0);
		glPopMatrix();
	}
	
}




float basev[][3] =
	{
		//Нижнее основание
		{0, 0, -1},
		{-0.9, -0.5, 0}, {-0.9, 0.5, 0}, {0.8, 0.5, 0}, 		{0.8, 0.5, 0}, {0.8, -0.5, 0}, {-0.9, -0.5, 0},
		
		//Левая нижняя боковушка
		{0, -1, 0},
		{-0.9, -0.5, 0}, {-0.9, -0.5, 0.4}, {0.8, -0.5, 0},		{0.8, -0.5, 0}, {0.8, -0.5, 0.4}, {-0.9, -0.5, 0.4},
		//передний левый уголок
		{-0.9, -0.5, 0}, {-1.1, -0.5, 0.15}, {-0.9, -0.5, 0.4},
		//Задний левый уголок
		{0.8, -0.5, 0}, {0.95, -0.5, 0.2}, {0.8, -0.5, 0.4},
		
		//Верхняя левая боковушка
		{0, cos( 5./6.*M_PI), sin(5./6.*M_PI) },
		{-0.9, -0.5, 0.4}, {-0.8, -0.4, 0.6}, {0.8, -0.5, 0.4},		{-0.8, -0.4, 0.6}, {0.7, -0.4, 0.6}, {0.8, -0.5, 0.4},
		
		
		//правая нижняя боковушка
		{0, 1, 0},
		{-0.9, 0.5, 0}, {-0.9, 0.5, 0.4}, {0.8, 0.5, 0},		{0.8, 0.5, 0}, {0.8, 0.5, 0.4}, {-0.9, 0.5, 0.4},
		//передний правый уголок
		{-0.9, 0.5, 0}, {-1.1, 0.5, 0.15}, {-0.9, 0.5, 0.4},
		//Задний правый уголок
		{0.8, 0.5, 0}, {0.95, 0.5, 0.2}, {0.8, 0.5, 0.4},
		
		//Верхняя правая боковушка
		{0, cos(1./6.*M_PI), sin(1./6.*M_PI) },
		{-0.9, 0.5, 0.4}, {-0.8, 0.4, 0.6}, {0.8, 0.5, 0.4},		{-0.8, 0.4, 0.6}, {0.7, 0.4, 0.6}, {0.8, 0.5, 0.4},
		
		
		//Нижняя защита1 водителя
		{cos(5./3.*M_PI), 0, sin(5./3.*M_PI)},
		{-0.9, -0.5, 0}, {-1.1, -0.5, 0.15}, {-0.9, 0.5, 0},		{-0.9, 0.5, 0}, {-1.1, 0.5, 0.15}, {-1.1, -0.5, 0.15},
		//верхняя защита1 водителя
		{cos(3./4.*M_PI), 0, sin(3./4.*M_PI)},
		{-1.1, -0.5, 0.15}, {-0.9, -0.5, 0.4}, {-1.1, 0.5, 0.15},	{-1.1, 0.5, 0.15}, {-0.9, 0.5, 0.4}, {-0.9, -0.5, 0.4},
		//верхняя защита2 водителя
		{cos(5./6.*M_PI), 0, sin(5./6.*M_PI)},
		{-0.9, -0.5, 0.4}, {-0.9, 0.5, 0.4}, {-0.8, -0.4, 0.6},		{-0.9, 0.5, 0.4}, {-0.8, 0.4, 0.6}, {-0.8, -0.4, 0.6},
		
		//Задняя нижняя защита
		{cos(7./4.*M_PI), 0, sin(7./4.*M_PI)},
		{0.8, -0.5, 0}, {0.8, 0.5, 0}, {0.95, -0.5, 0.2},			{0.8, 0.5, 0}, {0.95, -0.5, 0.2}, {0.95, 0.5, 0.2},
		//Задняя верхняя защита1
		{cos(1./4.*M_PI), 0, sin(1./4.*M_PI)},
		{0.95, -0.5, 0.2}, {0.95, 0.5, 0.2}, {0.8, -0.5, 0.4},		{0.95, 0.5, 0.2}, {0.8, 0.5, 0.4}, {0.8, -0.5, 0.4},
		//Задняя верхняя защита2
		{cos(1./6.*M_PI), 0, sin(1./6.*M_PI)},
		{0.8, -0.5, 0.4}, {0.7, -0.4, 0.6}, {0.8, 0.5, 0.4},		{0.8, 0.5, 0.4}, {0.7, -0.4, 0.6}, {0.7, 0.4, 0.6},
		
		//Верхняя крышка
		{0, 0, 1},
		{-0.8, -0.4, 0.6}, {-0.8, 0.4, 0.6}, {0.7, -0.4, 0.6},		{-0.8, 0.4, 0.6}, {0.7, 0.4, 0.6}, {0.7, -0.4, 0.6},
		
		//Левая Юбка
		{0, 0, 1},
		{-0.9, -0.5, 0.4}, {-0.9, -0.65, 0.4}, {0.8, -0.5, 0.4},	{0.8, -0.5, 0.4}, {0.8, -0.65, 0.4}, {-0.9, -0.65, 0.4},
		//спереди
		{cos(3./4.*M_PI), 0, sin(3./4.*M_PI)},
		{-0.9, -0.5, 0.4}, {-0.9, -0.65, 0.4}, {-1.2, -0.5, 0.3},	{-0.9, -0.65, 0.4}, {-1.2, -0.5, 0.3}, {-1.2, -0.65, 0.3},
		//там же
		{0, 1, 0},
		{-0.9, -0.5, 0.4,}, {-1.2, -0.5, 0.3}, {-0.9, -0.5, 0.15},
		//сзади
		{cos(1./4.*M_PI), 0, sin(1./4.*M_PI)},
		{0.8, -0.5, 0.4}, {0.8, -0.65, 0.4}, {1.0, -0.5, 0.3},		{0.8, -0.65, 0.4}, {1.0, -0.5, 0.3}, {1.0, -0.65, 0.3},
		//там же
		{0, 1, 0},
		{0.8, -0.5, 0.4}, {0.8, -0.5, 0.3}, {1.0, -0.5, 0.3},
		
		
		//Правая Юбка
		{0, 0, 1},
		{-0.9, 0.5, 0.4}, {-0.9, 0.65, 0.4}, {0.8, 0.5, 0.4},	{0.8, 0.5, 0.4}, {0.8, 0.65, 0.4}, {-0.9, 0.65, 0.4},
		//спереди
		{cos(3./4.*M_PI), 0, sin(3./4.*M_PI)},
		{-0.9, 0.5, 0.4}, {-0.9, 0.65, 0.4}, {-1.2, 0.5, 0.3},	{-0.9, 0.65, 0.4}, {-1.2, 0.5, 0.3}, {-1.2, 0.65, 0.3},
		//там же
		{0, -1, 0},
		{-0.9, 0.5, 0.4,}, {-1.2, 0.5, 0.3}, {-0.9, 0.5, 0.15},
		//сзади
		{cos(1./4.*M_PI), 0, sin(1./4.*M_PI)},
		{0.8, 0.5, 0.4}, {0.8, 0.65, 0.4}, {1.0, 0.5, 0.3},		{0.8, 0.65, 0.4}, {1.0, 0.5, 0.3}, {1.0, 0.65, 0.3},
		//там же
		{0, 1, 0},
		{0.8, 0.5, 0.4}, {0.8, 0.5, 0.3}, {1.0, 0.5, 0.3},
	};
	

void draw_base()
{
	glBegin(GL_TRIANGLES);
	//Нижнее основание
	glNormal3fv(basev[0] );
	for (int i = 1; i < 7; i++)
		glVertex3fv(basev[i]);
	/*
	glVertex3fv(basev[1] );
	glVertex3fv(basev[2] );
	glVertex3fv(basev[3] );
	glVertex3fv(basev[4] );
	glVertex3fv(basev[5] );
	glVertex3fv(basev[6] );*/
	
	//Левая нижняя боковушка
	glNormal3fv(basev[7] );
	for (int i = 8; i < 14; i++)
		glVertex3fv(basev[i]);
	/*
	glVertex3fv(basev[8] );
	glVertex3fv(basev[9] );
	glVertex3fv(basev[10] );
	glVertex3fv(basev[11] );
	glVertex3fv(basev[12] );
	glVertex3fv(basev[13] );*/
	//Передний левый уголок
	glVertex3fv(basev[14] );
	glVertex3fv(basev[15] );
	glVertex3fv(basev[16] );
	//Задний левый уголок
	glVertex3fv(basev[17] );
	glVertex3fv(basev[18] );
	glVertex3fv(basev[19] );
	
	//Верхняя левая боковушка
	glNormal3fv(basev[20] );
	glVertex3fv(basev[21] );
	glVertex3fv(basev[22] );
	glVertex3fv(basev[23] );
	glVertex3fv(basev[24] );
	glVertex3fv(basev[25] );
	glVertex3fv(basev[26] );	
	
	
	//правая нижняя боковушка
	glNormal3fv(basev[27] );
	glVertex3fv(basev[28] );
	glVertex3fv(basev[29] );
	glVertex3fv(basev[30] );
	glVertex3fv(basev[31] );
	glVertex3fv(basev[32] );
	glVertex3fv(basev[33] );
	//передний правый уголок
	glVertex3fv(basev[34] );
	glVertex3fv(basev[35] );
	glVertex3fv(basev[36] );
	//Задний правый уголок
	glVertex3fv(basev[37] );
	glVertex3fv(basev[38] );
	glVertex3fv(basev[39] );
	
	//Верхняя правая боковушка
	glNormal3fv(basev[40] );
	glVertex3fv(basev[41] );
	glVertex3fv(basev[42] );
	glVertex3fv(basev[43] );
	glVertex3fv(basev[44] );
	glVertex3fv(basev[45] );
	glVertex3fv(basev[46] );
	
	
	//Нижняя защита1 водителя
	glNormal3fv(basev[47] );
	glVertex3fv(basev[48] );
	glVertex3fv(basev[49] );
	glVertex3fv(basev[50] );
	glVertex3fv(basev[51] );
	glVertex3fv(basev[52] );
	glVertex3fv(basev[53] );
	glEnd();
	
	if(toogleTexture)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t34textures[0]);
	}
	glBegin(GL_TRIANGLES);
	//верхняя защита1 водителя
	glNormal3fv(basev[54] );
	glTexCoord2f(1.0, 0.0);		glVertex3fv(basev[55] );
	glTexCoord2f(1.0, 0.5);		glVertex3fv(basev[56] );
	glTexCoord2f(0.0, 0.0);		glVertex3fv(basev[57] );
	glTexCoord2f(0.0, 0.0);		glVertex3fv(basev[58] );
	glTexCoord2f(0.0, 0.5);		glVertex3fv(basev[59] );
	glTexCoord2f(1.0, 0.5);		glVertex3fv(basev[60] );
	glEnd();
	
	
	glBegin(GL_TRIANGLES);
	//верхняя защита2 водителя
	glNormal3fv(basev[61] );
	glTexCoord2f(1.0, 0.5);		glVertex3fv(basev[62] );
	glTexCoord2f(0.0, 0.5);		glVertex3fv(basev[63] );
	glTexCoord2f(1.0, 1.0);		glVertex3fv(basev[64] );
	glTexCoord2f(0.0, 0.5);		glVertex3fv(basev[65] );
	glTexCoord2f(0.0, 1.0);		glVertex3fv(basev[66] );
	glTexCoord2f(1.0, 1.0);		glVertex3fv(basev[67] );
	glEnd();
	if(toogleTexture)
		glDisable(GL_TEXTURE_2D);
	
	glBegin(GL_TRIANGLES);
	//Задняя нижняя защита
	glNormal3fv(basev[68] );
	glVertex3fv(basev[69] );
	glVertex3fv(basev[70] );
	glVertex3fv(basev[71] );
	glVertex3fv(basev[72] );
	glVertex3fv(basev[73] );
	glVertex3fv(basev[74] );	
	
	//Задняя верхняя защита1
	glNormal3fv(basev[75] );
	glVertex3fv(basev[76] );
	glVertex3fv(basev[77] );
	glVertex3fv(basev[78] );
	glVertex3fv(basev[79] );
	glVertex3fv(basev[80] );
	glVertex3fv(basev[81] );	
	//Задняя верхняя защита2
	glNormal3fv(basev[82] );
	glVertex3fv(basev[83] );
	glVertex3fv(basev[84] );
	glVertex3fv(basev[85] );
	glVertex3fv(basev[86] );
	glVertex3fv(basev[87] );
	glVertex3fv(basev[88] );	
	
	//Верхняя крышка
	glNormal3fv(basev[89] );
	glVertex3fv(basev[90] );
	glVertex3fv(basev[91] );
	glVertex3fv(basev[92] );
	glVertex3fv(basev[93] );
	glVertex3fv(basev[94] );
	glVertex3fv(basev[95] );
	
	
	//Левая Юбка
	glNormal3fv(basev[96] );
	glVertex3fv(basev[97] );
	glVertex3fv(basev[98] );
	glVertex3fv(basev[99] );
	glVertex3fv(basev[100] );
	glVertex3fv(basev[101] );
	glVertex3fv(basev[102] );
	//перед левой юбки
	glNormal3fv(basev[103] );
	glVertex3fv(basev[104] );
	glVertex3fv(basev[105] );
	glVertex3fv(basev[106] );
	glVertex3fv(basev[107] );
	glVertex3fv(basev[108] );
	glVertex3fv(basev[109] );
	//тоже
	glNormal3fv(basev[110] );
	glVertex3fv(basev[111] );
	glVertex3fv(basev[112] );
	glVertex3fv(basev[113] );
	//back левой юбки
	glNormal3fv(basev[114] );
	glVertex3fv(basev[115] );
	glVertex3fv(basev[116] );
	glVertex3fv(basev[117] );
	glVertex3fv(basev[118] );
	glVertex3fv(basev[119] );
	glVertex3fv(basev[120] );
	//тоже
	glNormal3fv(basev[121] );
	glVertex3fv(basev[122] );
	glVertex3fv(basev[123] );
	glVertex3fv(basev[124] );
	
	
	//Правая Юбка
	glNormal3fv(basev[125] );
	glVertex3fv(basev[126] );
	glVertex3fv(basev[127] );
	glVertex3fv(basev[128] );
	glVertex3fv(basev[129] );
	glVertex3fv(basev[130] );
	glVertex3fv(basev[131] );
	//спереди
	glNormal3fv(basev[132] );
	glVertex3fv(basev[133] );
	glVertex3fv(basev[134] );
	glVertex3fv(basev[135] );
	glVertex3fv(basev[136] );
	glVertex3fv(basev[137] );
	glVertex3fv(basev[138] );
	//тоже
	glNormal3fv(basev[139] );
	glVertex3fv(basev[140] );
	glVertex3fv(basev[141] );
	glVertex3fv(basev[142] );
	
	//back Правая юбки
	glNormal3fv(basev[143] );
	glVertex3fv(basev[144] );
	glVertex3fv(basev[145] );
	glVertex3fv(basev[146] );
	glVertex3fv(basev[147] );
	glVertex3fv(basev[148] );
	glVertex3fv(basev[149] );
	//тоже
	glNormal3fv(basev[150] );
	glVertex3fv(basev[151] );
	glVertex3fv(basev[152] );
	glVertex3fv(basev[153] );
	
	glEnd();
}


void draw_track(float size, float y_top)
{
	float left = -1, right = 0.9, bottom = -1;
	float xpos;
	float z_top = 0.3;
	float r = 0.1;
	int num;
	glPushMatrix();
	
	num = (right - left) / (3*size + 3*0.5*size);
	for(int i = 0; i < num; i++)
	{
		xpos = right - 3*1.5*size*float(i);
		glPushMatrix();
		glTranslatef(-0.1, y_top, z_top);
		glTranslatef(xpos, 0, 0);
		glScalef(3*size, 3*size, size);
		glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.1, y_top, -0.5*size);
		glTranslatef(xpos, 0, 0);
		glScalef(3*size, 3*size, size);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(left, y_top, z_top);
	glPushMatrix();
	glRotatef(30, 0, -1, 0);
	glScalef(3*size, 3*size, size);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.2*size, 0, -3*size);
	glRotatef(100, 0, -1, 0);
	glScalef(3*size, 3*size, size);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.2*size, 0, -6*size);
	glRotatef(130, 0, -1, 0);
	glScalef(3*size, 3*size, size);
	glutSolidCube(1);
	glPopMatrix();
	
	glPopMatrix();


	glPushMatrix();
	glTranslatef(right + size, y_top, z_top - 2*size);
	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glScalef(3*size, 3*size, size);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0*size, 0, -3.2*size);
	glRotatef(130, 0, 1, 0);
	glScalef(3*size, 3*size, size);
	glutSolidCube(1);
	glPopMatrix();
	
	glPopMatrix();
	
}

void draw_tracks()
{
	float size = 0.04;


	GLboolean glnormal;
	
	
	glGetBooleanv(GL_NORMALIZE, &glnormal);
	if(glnormal == false)
		glEnable(GL_NORMALIZE);
	
	draw_track(size, -0.6);
	draw_track(size,  0.6);
	
	if(glnormal == false)
		glDisable(GL_NORMALIZE);
}

void draw_all_wheels(float angle)
{
	float wheel_size = 0.135, wheel_size2 = 0.1;
	float xposw[] = {-0.95, -0.7, -0.4, 0, 0.3, 0.6, 0.84};
	float zposw[] = {0.12, 0.21, 0.18};
	
	for(int i = 0; i < 7; i++)
	{
		glPushMatrix();	
		glTranslatef(xposw[i], -0.6, zposw[i == 0 | (i == 6) << 1]);
		glRotatef(90, 1, 0, 0);
		glRotatef(angle, 0, 0, 1);
		if( i == 0 || i == 6)
			draw_base_wheel(wheel_size2);
		else
			draw_base_wheel(wheel_size);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(xposw[i], 0.6, zposw[i == 0 | (i == 6) << 1]);
		glRotatef(90, -1, 0, 0);
		glRotatef(angle, 0, 0, -1);
		if( i == 0 || i == 6)
			draw_base_wheel(wheel_size2);
		else
			draw_base_wheel(wheel_size);
		glPopMatrix();
	}
}

//Масштаб, позиция x,y,z, угол поворота башни, горизонт дула
void draw_canon(float scale, float x, float y, float z, float angle, float phi)
{
	GLboolean glnormal;
	
	glGetBooleanv(GL_NORMALIZE, &glnormal);
	if(glnormal == false)
		glEnable(GL_NORMALIZE);
		
	glPushMatrix();
	glTranslatef(x, y, z + 0.2*scale);
	glRotatef(angle, 0, 0, 1);
	glScalef(scale, scale, scale);
	
	if(toogleTexture)
		glEnable(GL_TEXTURE_2D);
	//Левая боковина
	glBindTexture(GL_TEXTURE_2D, t34textures[1]);
	glNormal3f(-0.2, cos(5./6. * M_PI), sin(5./6. * M_PI) );
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-1, -0.9, 0);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-0.8, -0.6, 0.8);
	glTexCoord2f(0.5, 1.0);		glVertex3f(0, -0.8, 0.8);
	glTexCoord2f(0.5, 0.0);		glVertex3f(0, -1, 0);
	glEnd();
	glNormal3f(0.2, cos(5./6. * M_PI), sin(5./6. * M_PI) );
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5, 0.0);		glVertex3f(0, -1, 0);
	glTexCoord2f(0.5, 1.0);		glVertex3f(0, -0.8, 0.8);
	glTexCoord2f(1.0, 1.0);		glVertex3f(0.8, -0.4, 0.8);
	glTexCoord2f(1.0, 0.0);		glVertex3f(1, -0.6, 0);
	glEnd();
	
	
	//Правая боковина
	glBindTexture(GL_TEXTURE_2D, t34textures[2]);
	glNormal3f(-0.2, cos(1./6.*M_PI), sin(1./6.*M_PI) );
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0.0);		glVertex3f(-1, 0.9, 0);
	glTexCoord2f(1.0, 1.0);		glVertex3f(-0.8, 0.6, 0.8);
	glTexCoord2f(0.5, 1.0);		glVertex3f(0, 0.8, 0.8);
	glTexCoord2f(0.5, 0.0);		glVertex3f(0, 1, 0);
	glEnd();
	glNormal3f(0.2, cos(1./6.*M_PI), sin(1./6.*M_PI) );
	glBegin(GL_POLYGON);
	glTexCoord2f(0.5, 0.0);		glVertex3f(0, 1, 0);
	glTexCoord2f(0.5, 1.0);		glVertex3f(0, 0.8, 0.8);
	glTexCoord2f(0, 1.0);		glVertex3f(0.8, 0.4, 0.8);
	glTexCoord2f(0, 0.0);		glVertex3f(1, 0.6, 0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, t34textures[5]);
	//Передняя боковина
	glNormal3f(cos(5./6.*M_PI), 0, sin(5./6.*M_PI));
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);		glVertex3f(-1, -0.9, 0);
	glTexCoord2f(1, 1);		glVertex3f(-0.8, -0.6, 0.8);
	glTexCoord2f(0, 1);		glVertex3f(-0.8, 0.6, 0.8);
	glTexCoord2f(0, 0);		glVertex3f(-1, 0.9, 0);
	glEnd();
	
	
	glBindTexture(GL_TEXTURE_2D, t34textures[4]);
	//Задняя боковина
	glNormal3f(cos(1./6.*M_PI), 0, sin(1./6.*M_PI));
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0);		glVertex3f(1, -0.6, 0);
	glTexCoord2f(1, 1);		glVertex3f(0.8, -0.4, 0.8);
	glTexCoord2f(0.0, 1);		glVertex3f(0.8, 0.4, 0.8);
	glTexCoord2f(0., 0.);		glVertex3f(1, 0.6, 0);
	glEnd();
	
	
	//Верхняя крышка
	glBindTexture(GL_TEXTURE_2D, t34textures[3]);
	glNormal3f(0, 0, 1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.1, 0.95);	glVertex3f(-0.8, -0.6, 0.8);
	glTexCoord2f(0.9, 1.0);		glVertex3f(-0.8, 0.6, 0.8);
	glTexCoord2f(1, 0.5);		glVertex3f(0, 0.8, 0.8);
	glTexCoord2f(0.95, 0.1);	glVertex3f(0.8, 0.4, 0.8);
	glTexCoord2f(0.0, 0.1);		glVertex3f(0.8, -0.4, 0.8);
	glTexCoord2f(0.0, 0.5);		glVertex3f(0, -0.8, 0.8);
	glEnd();
	if(toogleTexture)
		glDisable(GL_TEXTURE_2D);
	
	//Нижняя
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glVertex3f(-1, -0.9, 0);
	glVertex3f(-1, 0.9, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 0.6, 0);
	glVertex3f(1, -0.6, 0);
	glVertex3f(0, -1, 0);
	glEnd();
	glPopMatrix();
	
		


	if(glnormal == false)
		glDisable(GL_NORMALIZE);
	

	//рисуем основание и ствол
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0, 0, 1);
	draw_cylinder_my(0.9*scale, 0.2*scale, 10, 0, 0);
	
	glTranslatef(-0.8*scale, 0, (0.2 + 0.4)*scale);
	
	glRotatef(-90 + phi, 0, 1, 0);
	draw_cylinder_my(0.05, 1, 10, 0, 0);
	glPopMatrix();
}



void draw_engine()
{
	GLboolean glnormal;
	glGetBooleanv(GL_NORMALIZE, &glnormal);
	if(glnormal == false)
		glEnable(GL_NORMALIZE);
	
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(0.4, 0, 0.2);
	glScalef(1, 0.6, 0.7);
	glutSolidCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0.7, -0.2, 0.1);
	glScalef(0.4, 1.2, 0.5);
	glutSolidCube(0.4);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 0.5, 0.4);
	glTranslatef(0.8, -0.2, 0.18);
	//glScalef(0.4, 1.2, 0.5);
	glutSolidCube(0.2);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 0.3, 0.8);
	glTranslatef(0.84, 0.6, 0.18);
	//glScalef(0.4, 1.2, 0.5);
	glRotatef(90, 1, 0, 0);
	draw_cylinder_my(0.02, 1.2, 10, 0, 0);
	glPopMatrix();
	
	if(glnormal == false)
		glDisable(GL_NORMALIZE);
}


void draw_t34()
{
	float canonAngle = 0, canonAngleRand = 0, canonPhi = 0, canonPhiRand = 0, wheelAngle = 0;
	int anglef = 0, phif = 0;
	
	glColor3f(0.5f, 0.5f, 0.5f);

	if(toogleConsist)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		draw_base();
		draw_all_wheels(wheelAngle);
		draw_tracks();
		draw_canon(0.35, -0.4, 0, 0.6, canonAngle, canonPhi);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		draw_engine();
	}else
	{
		draw_base();
		draw_all_wheels(wheelAngle);
		draw_tracks();
		draw_canon(0.35, -0.4, 0, 0.6, canonAngle, canonPhi);
	}
	
	if(toogleAnimate)
	{
		if(anglef)
		{
			if(canonAngle + canonAngleRand >= 360)
			{
				anglef = 0;
				canonAngleRand = 260.*rand() / float(RAND_MAX);
			}
			canonAngle += 0.6;
		}else
		{
			if(canonAngle - canonAngleRand <= 0)
			{
				anglef = 1;
				canonAngleRand = 260.*rand() / float(RAND_MAX);
			}
			canonAngle -= 0.7;
		}
		
		if(phif)
		{
			if(canonPhi + canonPhiRand >=  70)
			{
				phif = 0;
				canonPhiRand = 70.*rand() / float(RAND_MAX);
			}
			canonPhi += 0.2;
		}else
		{
			if(canonPhi - canonPhiRand <= 0)
			{
				phif = 1;
				canonPhiRand = 70.*rand() / float(RAND_MAX);
			}
			canonPhi -= 0.2;
		}
		if( (wheelAngle += 1.5) >= 360)
			wheelAngle = 0;
	}
}


void t34_init()
{
	unsigned width, height;
	unsigned char *ImageData;
	
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glGenTextures(4, t34textures);
	
	if( (ImageData = TgaRead(media_path + "front.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;
	
	if( (ImageData = TgaRead(media_path + "head_left.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;
	
	if( (ImageData = TgaRead(media_path + "head_right.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;
	
	if( (ImageData = TgaRead(media_path + "head.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;
	
	if( (ImageData = TgaRead(media_path + "head_back.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;
	
	if( (ImageData = TgaRead(media_path + "head_front.tga", width, height)) == 0)
	{
		printf("Tga Read fail\n");
		exit(0);
	}
	glBindTexture(GL_TEXTURE_2D, t34textures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
								0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData);
	delete[] ImageData;	
}
