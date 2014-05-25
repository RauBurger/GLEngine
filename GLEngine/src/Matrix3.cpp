//
//  Matrix3.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 11/16/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#include <iostream>
#include "Matrix3.h"

Matrix3::Matrix3()
{
	mData[0] = 1; mData[3] = 0; mData[6] = 0;
	mData[1] = 0; mData[4] = 1; mData[7] = 0;
	mData[2] = 0; mData[5] = 0; mData[8] = 1;
	
}

float& Matrix3::operator[](int index)
{
	return mData[index];
}

Matrix3 Matrix3::operator=(Matrix3 mat3)
{
	float* tmp = mat3.getData();
	for(int i = 0; i < 9; i++)
		mData[i] = tmp[i];
	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat3) const
{
	Matrix3 tmp;
	const float* matData = mat3.getData();
	float tmpData[9];
	
	tmpData[0] = (mData[0] * matData[0]) + (mData[3] * matData[1]) + (mData[6] * matData[2]);
	tmpData[1] = (mData[1] * matData[0]) + (mData[4] * matData[1]) + (mData[7] * matData[2]);
	tmpData[2] = (mData[2] * matData[0]) + (mData[5] * matData[1]) + (mData[8] * matData[2]);
	tmpData[3] = (mData[0] * matData[3]) + (mData[3] * matData[4]) + (mData[6] * matData[5]);
	tmpData[4] = (mData[1] * matData[3]) + (mData[4] * matData[4]) + (mData[7] * matData[5]);
	tmpData[5] = (mData[2] * matData[3]) + (mData[5] * matData[4]) + (mData[8] * matData[5]);
	tmpData[6] = (mData[0] * matData[6]) + (mData[3] * matData[7]) + (mData[6] * matData[8]);
	tmpData[7] = (mData[1] * matData[6]) + (mData[4] * matData[7]) + (mData[7] * matData[8]);
	tmpData[8] = (mData[2] * matData[6]) + (mData[5] * matData[7]) + (mData[8] * matData[8]);
	
	tmp.setData(tmpData);
	return tmp;
}

float* Matrix3::getData()
{
	return mData;
}

const float* Matrix3::getData() const
{
	return mData;
}

void Matrix3::setData(float *data)
{
	for(int i = 0; i < 9; i++)
		mData[i] = data[i];
}

void Matrix3::printMatrix()
{
	std::cout << "[" << mData[0] << " " << mData[3] << " " << mData[6] << "]" << std::endl <<
				 "[" << mData[1] << " " << mData[4] << " " << mData[7] << "]" << std::endl <<
				 "[" << mData[2] << " " << mData[5] << " " << mData[8] << "]" << std::endl;

}