//
//  Vector3.h
//  QtGLEngine
//
//  Created by Rob Rau on 6/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QtGLEngine_Vector3_h
#define QtGLEngine_Vector3_h

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	
	float& operator[] (int i);
	Vector3 operator+ (const Vector3& vec3) const;
	Vector3 operator- (const Vector3& vec3) const;
	Vector3 operator* (const float& scalar) const;
	Vector3 operator/ (const float& scalar) const;
	
	float length();
	void normalize();
	float dot(Vector3& vec3);
	Vector3 cross(Vector3& vec3);
	
	
private:
	float mData[3];
};


#endif
