/*
 *  cubeprimitive.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/25/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */

#ifndef GL3_PROTOTYPES
	#define GL3_PROTOTYPES 1
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
//#include <OpenGL/glu.h>
#include <unistd.h>  // getcwd() definition
#include <sys/param.h>  // MAXPATHLEN definition
#else
#include <windows.h>
#include "gl/glew.h"
#include "gl/gl.h"
#include "gl/glu.h"
#endif
#include "cubeprimitive.h"
#include "freeimage.h"
#include <iostream>

using namespace std;

#ifdef __APPLE__
void GetCurrentPath(char* buffer)
{
	getcwd(buffer, MAXPATHLEN);
}
#endif

CubePrimitive::CubePrimitive()
{
	size = 1;

	xRot = 0;
	yRot = 0;
	zRot = 0;

	xPos = 0;
	yPos = 0;
	zPos = 0;
}

CubePrimitive::CubePrimitive(double sideLength)
{
	size = sideLength;

	xRot = 0;
	yRot = 0;
	zRot = 0;

	xPos = 0;
	yPos = 0;
	zPos = 0;

	loadDefaultTexture();
}

CubePrimitive::CubePrimitive(double sideLength, double x, double y, double z)
{
	size = sideLength;

	xRot = 0;
	yRot = 0;
	zRot = 0;

	xPos = x;
	yPos = y;
	zPos = z;
}

CubePrimitive::CubePrimitive(double x, double y, double z)
{
	size = 1;

	xRot = 0;
	yRot = 0;
	zRot = 0;

	xPos = x;
	yPos = y;
	zPos = z;
}

CubePrimitive::~CubePrimitive()
{
	cout << "destroyed" << endl;
}

void CubePrimitive::draw()
{
	/*glPushMatrix();


	glRotated(xRot, 1, 0, 0);
	glRotated(yRot, 0, 1, 0);
	glRotated(zRot, 0, 0, 1);

	glTranslated(xPos, yPos, zPos);


	//glBindTexture(GL_TEXTURE_2D, texID);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	//glBegin(GL_LINE_STRIP);

		glNormal3d(0,0,1);
		glColor4f(r, g, b, 1.0f);
		glVertex3f(-size, -size,  size);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glTexCoord2i(0,0);

		glVertex3f( size, -size,  size);
		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);

		glVertex3f( size,  size,  size);
		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);

		glVertex3f(-size,  size,  size);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);


		// Back Face
		glNormal3d(0,0,-1);
		//glColor4f(1.0f,0.0f,0.0f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glVertex3f(-size, -size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
		glVertex3f(-size,  size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
		glVertex3f( size,  size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
		glVertex3f( size, -size, -size);

		// Top Face
		glNormal3d(0,1,0);
		//glColor4f(0.0f,0.0f,1.0f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glVertex3f(-size,  size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
		glVertex3f(-size,  size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
		glVertex3f( size,  size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
		glVertex3f( size,  size, -size);

		glNormal3d(0,-1,0);
		// Bottom Face
		//glColor4f(0.0f,1.0f,1.0f,.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glVertex3f(-size, -size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
		glVertex3f( size, -size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
		glVertex3f( size, -size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
		glVertex3f(-size, -size,  size);

		glNormal3d(1,0,0);
		// Right face
		//glColor4f(1.0f,1.0f,0.0f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glVertex3f( size, -size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
		glVertex3f( size,  size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
		glVertex3f( size,  size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
		glVertex3f( size, -size,  size);

		glNormal3d(-1,0,0);
		// Left Face
		//glColor4f(1.0f,1.0f,1.0f,0.5f);
		glMultiTexCoord2f(GL_TEXTURE0, 0, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
		glVertex3f(-size, -size, -size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 0);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 0);
		glVertex3f(-size, -size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 1, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 1, 1);
		glVertex3f(-size,  size,  size);

		glMultiTexCoord2f(GL_TEXTURE0, 0, 1);
		glMultiTexCoord2f(GL_TEXTURE1, 0, 1);
		glVertex3f(-size,  size, -size);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();*/
}

void CubePrimitive::setPos(double x, double y, double z)
{
	xPos = x;
	yPos = y;
	zPos = z;
}

void CubePrimitive::setRot(double x, double y, double z)
{
	xRot = x;
	yRot = y;
	zRot = z;
}

void CubePrimitive::setSize(double sideLength)
{
	size = sideLength;
}

void CubePrimitive::setColor(double r, double b, double g)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void CubePrimitive::loadDefaultTexture()
{
	GLbyte* bits;
	FIBITMAP* texture;
	FIBITMAP* heightMap;
#ifdef __APPLE__
	char path[MAXPATHLEN];
	GetCurrentPath(path);
	cout << path << endl;
#endif
	texture = FreeImage_Load(FIF_JPEG, "/Textures/Diffuse Map.jpeg", JPEG_ACCURATE);
	heightMap = FreeImage_Load(FIF_JPEG, "/Textures/Normal Map.jpeg", JPEG_ACCURATE);
	
	bits = (GLbyte*)FreeImage_GetBits(texture);
	

	//color map
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//glTexImage2DMultisample()
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(texture), FreeImage_GetHeight(texture), 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
	int err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cout << "We errored out. CubePrimitive::setColor() line 280" << std::endl;
		if(err == GL_INVALID_ENUM)
		{
			std::cout << "GL_INVALID_ENUM" << std::endl;
		}
		else if(err == GL_INVALID_VALUE)
		{
			std::cout << "GL_INVALID_VALUE" << std::endl;
		}
		else if(err == GL_INVALID_OPERATION)
		{
			std::cout << "GL_INVALID_OPERATION" << std::endl;
		}
		/*else if(err == GL_STACK_OVERFLOW)
		{
			std::cout << "GL_STACK_OVERFLOW" << std::endl;
		}
		else if(err == GL_STACK_UNDERFLOW)
		{
			std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		}*/
		else if(err == GL_OUT_OF_MEMORY)
		{
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		}
		//else if(err == GL_TABLE_TOO_LARGE)
		//{
		//	std::cout << "GL_TABLE_TOO_LARGE" << std::endl;
		//}
	}
	//free(bits);

	//height map
	bits = (GLbyte*)FreeImage_GetBits(heightMap);
	
	glGenTextures(1, &heightID);
	glBindTexture(GL_TEXTURE_2D, heightID);

	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FreeImage_GetWidth(heightMap), FreeImage_GetHeight(heightMap), 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
	err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cout << "We errored out. CubePrimitive::setColor() line 326" << std::endl;
		if(err == GL_INVALID_ENUM)
		{
			std::cout << "GL_INVALID_ENUM" << std::endl;
		}
		else if(err == GL_INVALID_VALUE)
		{
			std::cout << "GL_INVALID_VALUE" << std::endl;
		}
		else if(err == GL_INVALID_OPERATION)
		{
			std::cout << "GL_INVALID_OPERATION" << std::endl;
		}
		/*else if(err == GL_STACK_OVERFLOW)
		{
			std::cout << "GL_STACK_OVERFLOW" << std::endl;
		}
		else if(err == GL_STACK_UNDERFLOW)
		{
			std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		}*/
		else if(err == GL_OUT_OF_MEMORY)
		{
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		}
		//else if(err == GL_TABLE_TOO_LARGE)
		//{
		//	std::cout << "GL_TABLE_TOO_LARGE" << std::endl;
		//}
	}
#ifdef _WIN32
	GLenum tmp;
	tmp = glewInit();
#endif

#ifdef _WIN32
	glBindTexture(GL_TEXTURE_2D, texID);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, heightID);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
#else
	
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, heightID);
#endif
}

GLuint CubePrimitive::getTexID()
{
	return texID;
}
