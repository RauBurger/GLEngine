/*
 *  Camera.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/26/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */

#ifndef GL3_PROTOTYPES
	#define GL3_PROTOTYPES 1
#endif

#include "Camera.h"
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#else
# ifdef __WIN32__
#  include <windows.h>
#  include "gl/gl.h"
# endif
#endif

#include <math.h>
#include "Frustrum.h"
#include "Node.h"
#include "Vector3.h"

Camera::Camera()
{

	xPos = 0;
	yPos = 0;
	zPos = 0;
	
	pos[0] = 0.0;
	pos[1] = 0.0;
	pos[2] = 0.0;

	angle = 0;
	xVec = 0;
	yVec = 0;
	zVec = 0;

	xRot = 0;
	yRot = 0;
	zRot = 0;
	
	mParentNode = 0;
}

Camera::~Camera()
{

}

void Camera::setFrustrum(Frustrum *frustrum)
{
	mFrustrum = frustrum;
}

Frustrum* Camera::getFrustrum()
{
	return mFrustrum;
}

void Camera::setPosition(double _x, double _y, double _z)
{
	pos[0] = _x;
	pos[1] = _y;
	pos[2] = _z;
}

void Camera::setRotation(double _angle, double _x, double _y, double _z)
{
	EulerRot = false;
	vecRot = true;
	angle = _angle;
	xVec = _x;
	yVec = _y;
	zVec = _z;
}

void Camera::setRotation(double _x, double _y, double _z)
{
	EulerRot = true;
	vecRot = false;
	xRot = _x;
	yRot = _y;
	zRot = _z;
}

void Camera::translate(double _x, double _y, double _z)
{
	mLocalViewMat[12] = _x;
	mLocalViewMat[13] = _y;
	mLocalViewMat[14] = _z;
	//pos[0] += _x;
	//pos[1] += _y;
	//pos[2] += _z;
}

void Camera::rotate(double _x, double _y, double _z)
{
	Matrix3 tmpMat;
	float cs = cos(angle);
	float sn = sin(angle);
	
	float mag = sqrt((_x*_x)+(_y*_y)+(_z*_z));
	_x = _x/mag;
	_y = _y/mag;
	_z = _z/mag;
	
	float xx = _x*_x;
	float xy = _x*_y;
	float xz = _x*_z;
	float yy = _y*_y;
	float yz = _y*_z;
	float zz = _z*_z;
	float one_cs = 1 - cs;
		
#define M(x) tmpMat[x]
	M(0) = cs + xx*one_cs; M(3) = xy*one_cs-_z*sn;  M(6)  = xz*one_cs+_y*sn; // M(12) = 0.0f;
	M(1) = xy*one_cs+_z*sn; M(4) = cs+yy*one_cs;	M(7)  = yz-_x*sn;		 // M(13) = 0.0f;
	M(2) = xz*one_cs-_y*sn; M(5) = yz*one_cs+_x*sn; M(8) = cs+zz*one_cs;	 // M(14) = 0.0f;
#undef M
		
	tmpMat = mLocalViewMat.extractRotationMatrix() * tmpMat;
	
	mLocalViewMat.setRotationMatrix(tmpMat);
}

float* Camera::getPosition()
{
	return pos;
}

void Camera::setParent(Node* parent)
{
	mParentNode = parent;
}

void Camera::draw(Matrix4* viewMat)
{
	if(mParentNode)
		//(*viewMat) = mLocalViewMat * mParentNode->_getModelMatrix();
		//(*viewMat) = mLocalViewMat.getInverse() * mParentNode->_getModelMatrix();
		//(*viewMat) = mParentNode->_getModelMatrix() * mLocalViewMat.getInverse();
		//(*viewMat) =  mParentNode->_getModelMatrix() * mLocalViewMat;
		(*viewMat) =  mParentNode->getWorldTransform() * mLocalViewMat;
		//(*viewMat) = mLocalViewMat * mParentNode->getWorldTransform();
	else
		(*viewMat) = mLocalViewMat;
	
	
	//(mLocalViewMat*mLocalViewMat.getInverse()).printMatrix();
	/*if(EulerRot)
	{
		glRotated(-xRot, 1, 0, 0);
		glRotated(-yRot, 0, 1, 0);
		glRotated(-zRot, 0, 0, 1);
	}
	else
		glRotated(-angle, xVec, yVec, zVec);

	glTranslated(-pos[0],-pos[1],-pos[2]);*/
}

void Camera::setViewAxis(Vector3 dVec, Vector3 uVec)
{
	Vector3 rVec = dVec.cross(uVec);
}
