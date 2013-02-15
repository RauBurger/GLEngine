//
//  Matrix4.h
//  QtGLEngine
//
//  Created by Rob Rau on 11/4/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#ifndef MATRIX4_H_
#define MATRIX4_H_
class Matrix3;

class Matrix4
{
public:
	Matrix4();
	
	float& operator[] (int index);
	Matrix4 operator = (Matrix4 mat4);
	//Matrix4 operator * (const Matrix4& mat4);
	Matrix4 operator * (const Matrix4& mat4) const;
	float* getData();
	
	Matrix3 extractRotationMatrix();
	void setRotationMatrix(Matrix3& rotMat);
	
	Matrix4 getInverse();
	
	Matrix4 transpose();
	
	void printMatrix();
private:
	void setData(float* data);
	const float* getData() const;
	float mData[16];
};


#endif //MATRIX4_H_