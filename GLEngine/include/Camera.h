/*
 *  Camera.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/07/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "SceneTree.h"
#include "Object.h"

class Frustrum;
class Node;
class Vector3;

class Camera : public Object
{
public:
	Camera();
	~Camera();
	
	void setFrustrum(Frustrum* frustrum);
	Frustrum* getFrustrum();

	void setPosition(double _x, double _y, double _z);
	void setRotation(double _angle, double _x, double _y, double _z); //angle around the vector.
	void setRotation(double _x, double _y, double _z); //Euler angles applied xyz.
	void translate(double _x, double _y, double _z);
	void rotate(double _x, double _y, double _z);

	void setViewAxis(Vector3 dVec, Vector3 uVec);
	
	void setParent(Node* parent);
	
	float* getPosition();

	void draw(Matrix4* viewMat);

private:
	float pos[3];
	float xPos;
	float yPos;
	float zPos;

	float angle;
	float xVec;
	float yVec;
	float zVec;

	float xRot;
	float yRot;
	float zRot;

	bool vecRot;
	bool EulerRot;
	
	Node* mParentNode;
	Matrix4 mLocalViewMat;
	Frustrum* mFrustrum;
};

#endif // CAMERA_H
