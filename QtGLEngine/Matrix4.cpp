//
//  Matrix4.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 11/8/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#include <iostream>
#include "Matrix4.h"
#include "Matrix3.h"

Matrix4::Matrix4()
{
	mData[0] = 1; mData[4] = 0; mData[8]  = 0; mData[12] = 0;
	mData[1] = 0; mData[5] = 1; mData[9]  = 0; mData[13] = 0;
	mData[2] = 0; mData[6] = 0; mData[10] = 1; mData[14] = 0;
	mData[3] = 0; mData[7] = 0; mData[11] = 0; mData[15] = 1;
}

float& Matrix4::operator[](int index)
{
	return mData[index];
}

Matrix4 Matrix4::operator=(Matrix4 mat4)
{
	float* tmp = mat4.getData();
	for(int i = 0; i < 16; i++)
		mData[i] = tmp[i];
	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat4) const
{
	Matrix4 tmp;
	const float* matData = mat4.getData();
	float tmpData[16];
	tmpData[0]  = (mData[0] * matData[0])  + (mData[4] * matData[1])  + (mData[8]  * matData[2])  + (mData[12] * matData[3]);
	tmpData[1]  = (mData[1] * matData[0])  + (mData[5] * matData[1])  + (mData[9]  * matData[2])  + (mData[13] * matData[3]);
	tmpData[2]  = (mData[2] * matData[0])  + (mData[6] * matData[1])  + (mData[10] * matData[2])  + (mData[14] * matData[3]);
	tmpData[3]  = (mData[3] * matData[0])  + (mData[7] * matData[1])  + (mData[11] * matData[2])  + (mData[15] * matData[3]);
	tmpData[4]  = (mData[0] * matData[4])  + (mData[4] * matData[5])  + (mData[8]  * matData[6])  + (mData[12] * matData[7]);
	tmpData[5]  = (mData[1] * matData[4])  + (mData[5] * matData[5])  + (mData[9]  * matData[6])  + (mData[13] * matData[7]);
	tmpData[6]  = (mData[2] * matData[4])  + (mData[6] * matData[5])  + (mData[10] * matData[6])  + (mData[14] * matData[7]);
	tmpData[7]  = (mData[3] * matData[4])  + (mData[7] * matData[5])  + (mData[11] * matData[6])  + (mData[15] * matData[7]);
	tmpData[8]  = (mData[0] * matData[8])  + (mData[4] * matData[9])  + (mData[8]  * matData[10]) + (mData[12] * matData[11]);
	tmpData[9]  = (mData[1] * matData[8])  + (mData[5] * matData[9])  + (mData[9]  * matData[10]) + (mData[13] * matData[11]);
	tmpData[10] = (mData[2] * matData[8])  + (mData[6] * matData[9])  + (mData[10] * matData[10]) + (mData[14] * matData[11]);
	tmpData[11] = (mData[3] * matData[8])  + (mData[7] * matData[9])  + (mData[11] * matData[10]) + (mData[15] * matData[11]);
	tmpData[12] = (mData[0] * matData[12]) + (mData[4] * matData[13]) + (mData[8]  * matData[14]) + (mData[12] * matData[15]);
	tmpData[13] = (mData[1] * matData[12]) + (mData[5] * matData[13]) + (mData[9]  * matData[14]) + (mData[13] * matData[15]);
	tmpData[14] = (mData[2] * matData[12]) + (mData[6] * matData[13]) + (mData[10] * matData[14]) + (mData[14] * matData[15]);
	tmpData[15] = (mData[3] * matData[12]) + (mData[7] * matData[13]) + (mData[11] * matData[14]) + (mData[15] * matData[15]);
	tmp.setData(tmpData);
	return tmp;
}

float* Matrix4::getData()
{
	return mData;
}

const float* Matrix4::getData() const
{
	return mData;
}

void Matrix4::setData(float *data)
{
	for(int i = 0; i < 16; i++)
		mData[i] = data[i];
}

Matrix3 Matrix4::extractRotationMatrix()
{
	float tmpData[9];
	Matrix3 tmpMat;
	
	tmpData[0] = mData[0]; tmpData[3] = mData[4]; tmpData[6] = mData[8];
	tmpData[1] = mData[1]; tmpData[4] = mData[5]; tmpData[7] = mData[9];
	tmpData[2] = mData[2]; tmpData[5] = mData[6]; tmpData[8] = mData[10];

	tmpMat.setData(tmpData);
	
	return tmpMat;
}

void Matrix4::setRotationMatrix(Matrix3 &rotMat)
{
	mData[0] = rotMat[0]; mData[4] = rotMat[3]; mData[8]  = rotMat[6];
	mData[1] = rotMat[1]; mData[5] = rotMat[4]; mData[9]  = rotMat[7];
	mData[2] = rotMat[2]; mData[6] = rotMat[5]; mData[10] = rotMat[8];
}

void Matrix4::printMatrix()
{
	std::cout << "[" << mData[0] << " " << mData[4] << " " << mData[8]  << " " << mData[12] << "]" << std::endl <<
				 "[" << mData[1] << " " << mData[5] << " " << mData[9]  << " " << mData[13] << "]" << std::endl <<
				 "[" << mData[2] << " " << mData[6] << " " << mData[10] << " " << mData[14] << "]" << std::endl <<
				 "[" << mData[3] << " " << mData[7] << " " << mData[11] << " " << mData[15] << "]" << std::endl;
}

Matrix4 Matrix4::getInverse()
{
	Matrix4 tmpMat;
	tmpMat = *this;
	float a11 = mData[0];
	float a12 = mData[4];
	float a13 = mData[8];
	float a14 = mData[12];
	float a21 = mData[1];
	float a22 = mData[5];
	float a23 = mData[9];
	float a24 = mData[13];
	float a31 = mData[2];
	float a32 = mData[6];
	float a33 = mData[10];
	float a34 = mData[14];
	float a41 = mData[3];
	float a42 = mData[7];
	float a43 = mData[11];
	float a44 = mData[15];
	
	//compute matrix determinant
	float det = a11*a22*a33*a44 + a11*a23*a34*a42 + a11*a24*a32*a43
			  + a12*a21*a34*a43 + a12*a23*a31*a44 + a12*a24*a33*a41
			  + a13*a21*a32*a44 + a13*a22*a34*a41 + a13*a24*a31*a42
			  + a14*a21*a33*a42 + a14*a22*a31*a43 + a14*a23*a32*a41
			  - a11*a22*a34*a43 - a11*a23*a32*a44 - a11*a24*a33*a42
			  - a12*a21*a33*a44 - a12*a23*a34*a41 - a12*a24*a31*a43
			  - a13*a21*a34*a42 - a13*a22*a31*a44 - a13*a24*a32*a41
			  - a14*a21*a32*a43 - a14*a22*a33*a41 - a14*a23*a31*a42;


	float b11 = a22*a33*a44 + a23*a34*a42 + a24*a32*a43 - a22*a34*a43 - a23*a32*a44 - a24*a33*a42;
	float b12 = a12*a34*a43 + a13*a32*a44 + a14*a33*a42 - a12*a33*a44 - a13*a34*a42 - a14*a32*a43;
	float b13 = a12*a23*a44 + a13*a24*a42 + a14*a22*a42 - a12*a24*a43 - a13*a22*a44 - a14*a23*a42;
	float b14 = a12*a24*a33 + a13*a22*a34 + a14*a23*a32 - a12*a23*a34 - a13*a24*a32 - a14*a22*a33;
	float b21 = a21*a34*a43 + a23*a31*a44 + a24*a33*a41 - a21*a33*a44 - a23*a34*a41 - a24*a31*a43;
	float b22 = a11*a33*a44 + a13*a34*a41 + a14*a31*a43 - a11*a34*a43 - a13*a31*a44 - a14*a33*a41;
	float b23 = a11*a24*a43 + a13*a21*a44 + a14*a23*a41 - a11*a23*a44 - a13*a24*a41 - a14*a21*a43;
	float b24 = a11*a23*a34 + a13*a24*a31 + a14*a21*a33 - a11*a24*a33 - a13*a21*a34 - a14*a23*a31;
	float b31 = a21*a32*a44 + a22*a34*a41 + a24*a31*a42 - a21*a34*a42 - a22*a31*a44 - a24*a32*a41;
	float b32 = a11*a34*a42 + a12*a31*a44 + a14*a32*a41 - a11*a32*a44 - a12*a34*a41 - a14*a31*a43;
	float b33 = a11*a22*a44 + a12*a24*a41 + a14*a21*a42 - a11*a24*a42 - a12*a21*a44 - a14*a22*a41;
	float b34 = a11*a24*a32 + a12*a21*a34 + a14*a22*a31 - a11*a22*a34 - a12*a24*a31 - a14*a21*a32;
	float b41 = a21*a33*a42 + a22*a31*a43 + a23*a32*a43 - a21*a32*a43 - a22*a33*a41 - a23*a31*a42;
	float b42 = a11*a32*a43 + a12*a33*a41 + a13*a31*a42 - a11*a33*a42 - a12*a31*a43 - a13*a32*a41;
	float b43 = a11*a23*a42 + a12*a21*a43 + a13*a22*a41 - a11*a22*a43 - a12*a23*a41 - a13*a21*a42;
	float b44 = a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - a11*a23*a32 - a12*a21*a33 - a13*a22*a31;
	
	tmpMat.mData[0] = b11/det;
	tmpMat.mData[4] = b12/det;
	tmpMat.mData[8] = b13/det;
	tmpMat.mData[12] = b14/det;
	tmpMat.mData[1] = b21/det;
	tmpMat.mData[5] = b22/det;
	tmpMat.mData[9] = b23/det;
	tmpMat.mData[13] = b24/det;
	tmpMat.mData[2] = b31/det;
	tmpMat.mData[6] = b32/det;
	tmpMat.mData[10] = b33/det;
	tmpMat.mData[14] = b34/det;
	tmpMat.mData[3] = b41/det;
	tmpMat.mData[7] = b42/det;
	tmpMat.mData[11] = b43/det;
	tmpMat.mData[15] = b44/det;
	
	return tmpMat;
}


/*
	0	4	8	12
 
	1	5	9	13
 
	2	6	10	14
 
	3	7	11	15
 */
Matrix4 Matrix4::transpose()
{
	Matrix4 tmpMat;
	
	tmpMat.mData[0] = mData[0];
	tmpMat.mData[1] = mData[4];
	tmpMat.mData[2] = mData[8];
	tmpMat.mData[3] = mData[12];
	tmpMat.mData[4] = mData[1];
	tmpMat.mData[5] = mData[5];
	tmpMat.mData[6] = mData[9];
	tmpMat.mData[7] = mData[13];
	tmpMat.mData[8] = mData[2];
	tmpMat.mData[9] = mData[6];
	tmpMat.mData[10] = mData[10];
	tmpMat.mData[11] = mData[14];
	tmpMat.mData[12] = mData[3];
	tmpMat.mData[13] = mData[7];
	tmpMat.mData[14] = mData[11];
	tmpMat.mData[15] = mData[15];
	return tmpMat;
}