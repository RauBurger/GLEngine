/*
 *  cubeprimitive.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/26/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef CUBEPRIMITIVE_H
#define CUBEPRIMITIVE_H

#ifndef GL3_PROTOTYPES
	#define GL3_PROTOTYPES 1
#endif
#ifndef kCGLOGLPVersion_3_2_Core
	#define kCGLOGLPVersion_3_2_Core 1
#endif

#include "Object.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
#include "gl/gl.h"
#endif


class CubePrimitive : public Object
{
public:
	CubePrimitive();
	CubePrimitive(double sideLength);
	CubePrimitive(double sideLength, double x, double y, double z);
	CubePrimitive(double x, double y, double z);
	~CubePrimitive();

	void draw();
	void setPos(double x, double y, double z);
	void setRot(double x, double y, double z);
	void setSize(double sideLength);
	void setColor(double r, double g, double b);

	GLuint getTexID();

private:
	void loadDefaultTexture();

	double size;
	double xRot, yRot, zRot;
	double xPos, yPos, zPos;
	double r, g, b;

	GLuint texID;
	GLuint heightID;
};

#endif // CUBEPRIMITIVE_H
