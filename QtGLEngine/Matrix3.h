//
//  Matrix3.h
//  QtGLEngine
//
//  Created by Rob Rau on 11/4/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#ifndef	MATRIX3_H_
#define MATRIX3_H_

class Matrix3
{
public:
	Matrix3();
	
	float& operator[] (int index);
	Matrix3 operator = (Matrix3 mat3);
	//Matrix4 operator * (const Matrix4& mat4);
	Matrix3 operator * (const Matrix3& mat3) const;
	float* getData();
	void setData(float* data);
	
	void printMatrix();
private:
	const float* getData() const;
	float mData[9];
};

#endif //MATRIX3_H_