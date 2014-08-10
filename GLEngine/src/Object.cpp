//
//  Object.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 10/27/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//
#define TIXML_USE_STL
#include "../tinyxml/tinyxml.h"
#include "Object.h"
#include "Node.h"
#include "Core.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include "RenderWindow.cpp"
#include <math.h>

static GLfloat lightPosition[4] = { 0.0, 0.0, -60.0, 1.0 };
static GLfloat lightDiffuse[4] = {1, 1, 1, 1};
static GLfloat lightSpecular[4] = {-.7, -.7, -.7, 1};
static GLfloat lightAmbient[4] = {-.5, -.5, -.5, 1};

static GLfloat lightPosition2[4] = { -50.0, 0.0, -350.0, 1.0 };
static GLfloat lightDiffuse2[4] = {0, 0, 0, 1};
static GLfloat lightSpecular2[4] = {-.7, -.7, -.7, 1};
static GLfloat lightAmbient2[4] = {-.5, -.5, -.5, 1};

Object::Object()
{
	mParentNode = NULL;
	mNumVerts = 0;
	mNumNormals = 0;
	mNumFaces = 0;
}

Object::~Object()
{
	
}

void Object::loadModelPly()
{
	std::ifstream model;
	char in[2048];
	int verts = 0;
	int faces = 0;
	//model.open("/motorcycleFairing2_5x.ply");
#ifdef __linux
	model.open("/home/rrau/GLEngine/TestApp/data/models/house.ply");
//#elif _WIN32
//	model.open("C:\\Users\\Rob\ Rau\\GLEngine\\TestApp\\data\\models\\huose.ply");
#else
	model.open("/house.ply");
#endif
	if(model.fail())
	{
		std::cout << "Bad file" << std::endl;
		exit(0);
	}
	int cntv = 0;
	int cntn = 0;
	int cntf = 0;
	bool startVerts = false;
	
	while(!model.eof())
	{
		model.getline(in, 2048, '\n');
		std::string inStr = in;
		int pos = inStr.find("element vertex");
		if(pos >= 0)
		{
			std::cout << "found vert header" << std::endl;
			std::string numVerts = inStr.substr(15, 10);
			verts = atoi(numVerts.c_str());
			mVerticies = new GLfloat[verts * 3];
			mNormals = new GLfloat[verts * 3];
		}
		pos = inStr.find("element face");
		if(pos >= 0)
		{
			std::cout << "found face header" << std::endl;
			std::string numFaces = inStr.substr(13, 10);
			faces = atoi(numFaces.c_str());
			mIndicies = new GLuint[faces * 3];
		}
		//std::cout << inStr << std::endl;
		if(inStr == "end_header")
		{
			startVerts = true;
		}
		//else if((startVerts) && (inStr[0] != '3') && (inStr[1] != ' '))
		else if((startVerts) && (inStr[1] != ' '))
		{
			std::stringstream ssIn;
			
			ssIn << inStr;
			ssIn >> mVerticies[cntv] >> mVerticies[cntv + 1] >> mVerticies[cntv + 2] >> mNormals[cntn] >> mNormals[cntn + 1] >> mNormals[cntn + 2];
			mVerticies[cntv] *= .04;
			mVerticies[cntv+1] *= .04;
			mVerticies[cntv+2] *= .04;
			//mVerticies[cntv] *= 10;
			//mVerticies[cntv+1] *= 10;
			//mVerticies[cntv+2] *= 10;
			cntv += 3;
			cntn += 3;
		}
		else if((inStr[0] == '3') && (inStr[1] == ' '))
		{
			startVerts = false;
			std::stringstream ssIn;
			int trash;
			ssIn << inStr;
			ssIn >> trash >> mIndicies[cntf] >> mIndicies[cntf + 1] >> mIndicies[cntf + 2];
			cntf += 3;
			
		}
	}
	
	/*for(int i = 0; i < verts*3; i += 3)
	{
		std::cout << "(" << mVerticies[i] << ", " << mVerticies[i+1] << ", " << mVerticies[i+2] << ")" << std::endl;
	}*/
	/*for(int i = 0; i < faces*3; i += 3)
	{
		std::cout << "<" << mIndicies[i] << ", " << mIndicies[i+1] << ", " << mIndicies[i+2] << ">" << std::endl;
	}
	for(int i = 0; i < verts*3; i += 3)
	{
		std::cout << "(" << mNormals[i] << ", " << mNormals[i+1] << ", " << mNormals[i+2] << ")" << std::endl;
	}*/
	
	std::cout << cntv << std::endl;
	std::cout << "Verts/Normals: " << verts << std::endl;
	std::cout << "Faces: " << faces << std::endl;
	mNumVerts = verts;
	mNumFaces = faces;
	mNumNormals = verts;

	glGenVertexArrays(1, &mVertArrayObj);
	glBindVertexArray(mVertArrayObj);
	// generate a new VBO and get the associated ID
	glGenBuffers(3, ids);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts * 3, mVerticies, GL_STATIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * verts * 3, mVerticies);
	
	glBindBuffer(GL_ARRAY_BUFFER, ids[1]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts * 3, mNormals, GL_STATIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * verts, mNormals);
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * faces * 3, mIndicies, GL_STATIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	int maxAttrib;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttrib);
	std::cout << "Maximum shader attributes supported: " << maxAttrib << std::endl;
	
	
	glEnableVertexAttribArray(0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	glEnableVertexAttribArray(1);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBindBuffer(GL_ARRAY_BUFFER, ids[1]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
}
/*
void Object::loadModelx3d()
{
	TiXmlDocument* doc;
	doc = new TiXmlDocument("/motorcycleFairing2_5x.xml");
	if(!doc->LoadFile())
	{
		printf("model read fail\n");
		return;
	}
	
	std::stringstream sstrm;
	
	TiXmlElement* xRoot = doc->RootElement();
	//std::string gui = xRoot->Attribute("gui");
	TiXmlElement* xChild = (TiXmlElement*)xRoot->IterateChildren(0);
	int cnt = 0;
	//iterate through the child elements in the config file
	for(xChild; xChild; xChild = (TiXmlElement*)xRoot->IterateChildren(xChild))
	{
		cnt++;
	}
	
	//std::cout << cnt << std::endl;
	//std::cout << "hello?" << std::endl;
	//std::cout.flush();
	printf("Hello? again?");
}
*/
void Object::loadModel()
{
	std::ifstream model;
	model.open("/motorcycleFairing2_5x.obj");
	//model.open("QtGLEngine.app/Contents/Resources/motorcycleFairing2_5x.obj");
	
	bool haveVertex = false;
	bool haveFace = false;
	bool haveNormal = false;
	int vertNum = 0;
	int faceNum = 0;
	int normNum = 0;
	int cnt = 0;
	
	mVerticies = new GLfloat[352*3];
	mIndicies = new GLuint[638*6];
	mNormals = new GLfloat[300*3];
	
	while(!model.eof())
	{
		std::string tmp;
		model >> tmp;
		//std::cout << tmp << std::endl;
		
		if(tmp == "v")
		{
			haveVertex = true;
			haveFace = false;
			haveNormal = false;
		}
		else if(tmp == "f")
		{
			haveVertex = false;
			haveNormal = false;
			haveFace = true;
		}
		else if(tmp == "vn")
		{
			haveVertex = false;
			haveNormal = true;
			haveFace = false;
		}
		else if(((tmp[0] > 47) && (tmp[0] < 58)) || (tmp[0] == 45))
		{
			
			if(haveVertex)
			{
				//std::cout << "string: " << tmp << std::endl;
				//std::cout << "atof: " << atof(tmp.c_str()) << std:: endl;
				mVerticies[vertNum] = (atof(tmp.c_str()) * 20);
				vertNum++;
			}
			if(haveFace)
			{
				std::string tmp2, tmp3;
				
				int p = tmp.find("/");
				if(p > -1)
				{
					tmp2 = tmp.substr(0, p);
					tmp3 = tmp.substr(p+2, tmp.size()-1);
				}
				
				mIndicies[faceNum] = atoi(tmp2.c_str()) - 1.0;
				mIndicies[faceNum + 3] = atoi(tmp3.c_str()) - 1.0;
				if(cnt < 2)
				{
					faceNum++;
					cnt++;
				}
				else
				{
					faceNum += 4;
					cnt = 0;
				}
			}
			if(haveNormal)
			{
				mNormals[normNum] = atof(tmp.c_str());
				normNum++;
			}
		}
	}
	
	/*for(int i = 0; i < 352*3; i += 3)
	{
		std::cout << "(" << mVerticies[i] << ", " << mVerticies[i+1] << ", " << mVerticies[i+2] << ")" << std::endl;
	}
	for(int i = 0; i < 638*6; i += 6)
	{
		std::cout << "<" << mIndicies[i] << ", " << mIndicies[i+1] << ", " << mIndicies[i+2] << ">" << std::endl;
		std::cout << "<<" << mIndicies[i+3] << ", " << mIndicies[i+4] << ", " << mIndicies[i+5] << ">>" << std::endl;
	}
	for(int i = 0; i < 300*3; i += 3)
	{
		std::cout << "(" << mNormals[i] << ", " << mNormals[i+1] << ", " << mNormals[i+2] << ")" << std::endl;
	}*/
	
	// generate a new VBO and get the associated ID
	glGenBuffers(3, ids);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 352 * 3, mVerticies, GL_DYNAMIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 352 * 3, mVerticies);
	
	glBindBuffer(GL_ARRAY_BUFFER, ids[1]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 291 * 3, mNormals, GL_DYNAMIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * 291, mNormals);
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 638 * 6, mIndicies, GL_DYNAMIC_DRAW);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ids[1]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);	
	//glBindAttribLocation(p, 0, "vVerts");
	//getGlError("Object::loadModel() line:151, glBindAttribLocation");
}

void Object::setProgram(GLuint i)
{
	p = i;
}

void Object::draw(Matrix4* viewMat, Matrix4* projMat)
{
	Matrix4 modelViewMat;
	Matrix4 modelViewProjMat;
	static GLfloat xpos = -.01;
	static int ypos = 0;
	static double cnt = 0;
	
	xpos = 25*sin((cnt += .02));
	//ypos = 25*cos((cnt += .05));
	//mModelMat[12] = xpos;
	//lightPosition[0] = xpos;
	//lightPosition[2] = ypos;
	//std::cout << lightPosition[0] << std::endl;
	if(mParentNode)
	{
		modelViewProjMat = (*projMat) * (*viewMat).getInverse() * mParentNode->getWorldTransform();// * mModelMat.transpose();
	}
	else
	{
		//xpos = 4*sin((cnt += .05));
		//mModelMat[14] = xpos;
		modelViewMat = (*viewMat) * mModelMat;
		modelViewProjMat = (*projMat) * modelViewMat;
	}
		
	//mNormalMat = modelViewMat.extractRotationMatrix();
	mNormalMat = (mParentNode->getWorldTransform() * mModelMat).extractRotationMatrix();
	//mNormalMat.printMatrix();
	//std::cout << std::endl;
	if (glIsProgram(p) != GL_TRUE)
	{
		setupShaders();
	}
	glUseProgram(p);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	glUniform3f(mVpLight1, lightPosition[0], lightPosition[1], lightPosition[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniform3f(mVpLight2, lightPosition2[0], lightPosition2[1], lightPosition2[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	glUniform1i(mNumLights, 2);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniform1i(mFpNumLights, 2);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	glUniform3f(mLight1Ptr, lightPosition[0], lightPosition[1], lightPosition[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniformMatrix3fv(mWorldRotPtr, 1, GL_FALSE, modelViewMat.extractRotationMatrix().getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	glUniformMatrix4fv(mWMatrixPtr, 1, GL_FALSE, modelViewMat.getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniformMatrix4fv(mMVMatPtr, 1, GL_FALSE, modelViewMat.getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniform3f(mCamPosPtr, (*viewMat)[12], (*viewMat)[13], (*viewMat)[14]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	//Matrix uniforms
	glUniformMatrix4fv(mMVPMptr, 1, GL_FALSE, modelViewProjMat.getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniformMatrix4fv(mMMat, 1, GL_FALSE, (mModelMat * mParentNode->getWorldTransform()).getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniformMatrix4fv(mMVMptr, 1, GL_FALSE, modelViewMat.getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glUniformMatrix3fv(mNMptr, 1, GL_FALSE, mNormalMat.getData());
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	glBindBuffer(GL_ARRAY_BUFFER, ids[0]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glBindBuffer(GL_ARRAY_BUFFER, ids[1]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ids[2]);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glDrawElements( GL_TRIANGLES, mNumFaces*3, GL_UNSIGNED_INT, 0);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	//glUseProgram(NULL);

}

void Object::setParentNode(Node *node)
{
	mParentNode = node;
}

void Object::setupShaders()
{
	std::string fragSrc;
	std::string vertSrc;
	GLint testVal;
	
	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

#ifdef __linux
	vertSrc = readShaderFile("/home/rrau/GLEngine/TestApp/data/shaders/vertexMP.vs");
	fragSrc = readShaderFile("/home/rrau/GLEngine/TestApp/data/shaders/fragmentMP.fs");
#elif _WIN32
	vertSrc = readShaderFile("/vertexMP.vs");
	fragSrc = readShaderFile("/fragmentMP.fs");
#else
	vertSrc = readShaderFile("TestApp.app/Contents/Resources/vertexMP.vs");
	fragSrc = readShaderFile("TestApp.app/Contents/Resources/fragmentMP.fs");
#endif

	const char * vv = vertSrc.c_str();
	const char * ff = fragSrc.c_str();
	
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	
	//free(vs);free(fs);
	glCompileShader(v);
	
	glGetShaderiv(v, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[4096];
		glGetShaderInfoLog((GLint)v, 4096, NULL, infoLog);
		std::cout << "Vertex shader compile failed! Error: " << infoLog << std::endl;
	}
	
	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog1[4096];
		glGetShaderInfoLog((GLint)f, 4096, NULL, infoLog1);
		std::cout << "Fragment shader compile failed! Error: " << infoLog1 << std::endl;
	}
	
	p = glCreateProgram();
	
	glAttachShader(p, v);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	glAttachShader(p, f);
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	glBindAttribLocation(p, 0, "vVert");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	glBindAttribLocation(p, 1, "vNorm");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	//glVertexAttribDivisorARB(2, 3);
	//getGlError("RenderWindow::setupShaders() line:336, glVertexAttribDivisorARB");
	
	glLinkProgram(p);
	
    glGetProgramiv(p, GL_LINK_STATUS, &testVal);
    if(testVal == GL_FALSE)
	{
		char infoLog[4096];
		glGetProgramInfoLog(p, 4096, NULL, infoLog);
		Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
		std::cout << "Link failed! Error: " << infoLog << std::endl;
	}
	
	glValidateProgram(p);
	glGetProgramiv(p, GL_VALIDATE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[2048];
		glGetProgramInfoLog(p, 2048, NULL, infoLog);
		Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
		std::cout << "Program Validation error: " << infoLog << std::endl;
	}
	
	mVpLight1 = glGetUniformLocation(p, "light1");
	mVpLight2 = glGetUniformLocation(p, "light2");
	
	mNumLights = glGetUniformLocation(p, "numLights");
	mFpNumLights = glGetUniformLocation(p, "fpNumLights");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mFpLightNum = glGetUniformLocation(p, "numLight");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	//matrix uniforms
	mMVPMptr = glGetUniformLocation(p, "mvpMat");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mMVMptr = glGetUniformLocation(p, "mvMat");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mNMptr = glGetUniformLocation(p, "vNormMat");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	
	mLight1Ptr = glGetUniformLocation(p, "lightPos1");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mCamPosPtr = glGetUniformLocation(p, "camPos");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mWorldRotPtr = glGetUniformLocation(p, "WorldRot");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mWMatrixPtr = glGetUniformLocation(p, "WMatrix");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
	mMVMatPtr = glGetUniformLocation(p, "mvMat");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);

	mMMat = glGetUniformLocation(p, "mMat");
	Core::GetGlError(__FILE__, __FUNCTION__, __LINE__-1);
}

std::string Object::readShaderFile(std::string fileName)
{
	std::ifstream iFile;
	std::string output;
	
	iFile.open(fileName.c_str());
	
	if(iFile.fail())
	{
		std::cout << fileName << std::endl;
		std::cout << "fail" << std::endl;
		return "fail";
	}
	
	bool forFind = false;
	while(!iFile.eof())
	{
		std::string temp;
		iFile >> temp;
		if(temp.find("for") != -1)
			if((temp[temp.find("for")+3] == '(') || (temp[temp.find("for")+3] == ' '))
				forFind = true;
		if(temp.find(")") != -1)
			if(forFind)
			{
				temp += "\n";
				forFind = false;
			}
		
		if(temp.find(";") != -1)
			if(!forFind)
				temp += "\n";
		if(temp.find("}") != -1)
			temp += "\n";
		if(temp.find("{") != -1)
			temp += "\n";
		output += (" " + temp);
	}
	std::cout << output << std::endl;
	return output;
}
