
#if defined _MSC_VER
#include <windows.h>
#define _USE_MATH_DEFINES
#else
#define _STDCALL_SUPPORTED
#define _M_IX86
#endif

#include <GL/gl.h>
#include <cmath>

void vector_mul( float *res, const float *v1, const float *v2)
{
	res[0] = v1[1] * v2[2] - v2[1] * v1[2];
	res[1] = v2[0] * v1[2] - v1[0] * v2[2];
	res[2] = v1[0] * v2[1] - v2[0] * v1[1];
}

void vector_norm( float *vec )
{
	float r = sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );
	vec[0] /= r;
	vec[1] /= r;
	vec[2] /= r;
}


void draw_disk_my(const float r, const unsigned N)
{
	float x, y, k;
	
	k = float(2.*M_PI)/float(N);
	
	glBegin(GL_TRIANGLE_FAN);
	//glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(r, 0, 0);
	for( unsigned i = 1; i < N + 1; i++)
	{
		x = r*cos( k*float(i) );
		y = r*sin( k*float(i) );
		glVertex3f(x, y, 0);
	}
	glEnd();
}

void draw_cylinder_my(const float r, const float h, unsigned N, const unsigned NroofUp, const unsigned NroofDown)
{
	float x, y;
	float k;
	float vn[3];
	
	k = float(2.*M_PI) / float(N);
	
	glBegin(GL_TRIANGLE_STRIP);
	
	
	glNormal3f(1, 0, 0);
	glVertex3f( r, 0, 0);
	glVertex3f( r, 0, h);
	
	for(unsigned i = 1; i < N + 1; i++)
	{
		x = r*cos(k * float(i));
		y = r*sin(k * float(i));
		
		vn[0] = x;	vn[1] = y;	vn[2] = 0;
		vector_norm(vn);
		glNormal3fv(vn);
		glVertex3f(x, y, 0);
		glVertex3f(x, y, h);
	}
	glEnd();
	
	
	
	//Верхняя крышка
	glPushMatrix();
	glTranslatef(0, 0, h);
	glNormal3f(0, 0, 1);
	draw_disk_my(r, NroofUp);
	glPopMatrix();
	
	//Нижняя крышка
	glNormal3f(0, 0, -1);
	draw_disk_my(r, NroofDown);
}

