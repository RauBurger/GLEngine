//
//  Vector3.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "math.h"
#include "Vector3.h"

Vector3::Vector3()
{
	mData[0] = 0.0f;
	mData[1] = 0.0f;
	mData[2] = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	mData[0] = x;
	mData[1] = y;
	mData[2] = z;
}

float& Vector3::operator[](int i)
{
	return mData[i];
}

Vector3 Vector3::operator+ (const Vector3 &vec3) const
{
	Vector3 tmpVec3;
	tmpVec3[0] = mData[0] + vec3.mData[0];
	tmpVec3[1] = mData[1] + vec3.mData[1];
	tmpVec3[2] = mData[2] + vec3.mData[2];
	return tmpVec3;
}

Vector3 Vector3::operator- (const Vector3& vec3) const
{
	Vector3 tmpVec3;
	tmpVec3[0] = mData[0] - vec3.mData[0];
	tmpVec3[1] = mData[1] - vec3.mData[1];
	tmpVec3[2] = mData[2] - vec3.mData[2];
	return tmpVec3;
}

Vector3 Vector3::operator* (const float& scalar) const
{
	Vector3 tmpVec3;
	tmpVec3[0] = mData[0] * scalar;
	tmpVec3[1] = mData[1] * scalar;
	tmpVec3[2] = mData[2] * scalar;
	return tmpVec3;
}

Vector3 Vector3::operator/ (const float& scalar) const
{
	Vector3 tmpVec3;
	tmpVec3[0] = mData[0] / scalar;
	tmpVec3[1] = mData[1] / scalar;
	tmpVec3[2] = mData[2] / scalar;
	return tmpVec3;
}

float Vector3::length()
{
	return sqrt((mData[0]*mData[0])+(mData[1]*mData[1])+(mData[2]*mData[2]));
}

void Vector3::normalize()
{
	float len = sqrt((mData[0]*mData[0])+(mData[1]*mData[1])+(mData[2]*mData[2]));
	mData[0] = mData[0] / len;
	mData[1] = mData[1] / len;
	mData[2] = mData[2] / len;
}

float Vector3::dot(Vector3& vec3)
{
	return (mData[0]*vec3.mData[0]) + (mData[1]*vec3.mData[1]) + (mData[2]*vec3.mData[2]);
}

Vector3 Vector3::cross(Vector3& vec3)
{
	Vector3 tmpVec;
	tmpVec[0] = mData[1]*vec3.mData[2] - mData[2]*vec3.mData[1];
	tmpVec[1] = -(mData[0]*vec3.mData[2] - mData[2]*vec3.mData[0]);
	tmpVec[2] = mData[0]*vec3.mData[1] - mData[1]*vec3.mData[0];
	return tmpVec;
}
