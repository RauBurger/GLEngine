//
//  Node.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 11/8/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#include <iostream>
#include "Node.h"
#include "math.h"
#include "Camera.h"

Node::Node(std::string name)
{
	mName = name;
	mParentNode = NULL;
	mSceneTree = NULL;
	mNumChildNodes = 0;
	mChildrenNodes = 0;
	//mChildrenNodes = new std::vector<Node*>;
}

void Node::attachObject(Object* obj)
{
	obj->setParentNode(this);
	//obj->setWorldViewMatrixPtr(mWorldViewMat);
}

void Node::attachObject(Node* node)
{
	node->mParentNode = this;
	//getChildVector()->push_back(node);
	if(mChildrenNodes != NULL)
	{
		Node** tmpObj;
		tmpObj = new Node*[mNumChildNodes + 1];
		for(int i = 0; i < mNumChildNodes; i++)
		{
			tmpObj[i] = mChildrenNodes[i];
		}
		mNumChildNodes++;
		delete [] mChildrenNodes;
		mChildrenNodes = tmpObj;
		mChildrenNodes[mNumChildNodes - 1] = node;
		mChildNodeNames[node->mName] = mNumChildNodes - 1;
	}
	else
	{
		mNumChildNodes++;
		mChildrenNodes = new Node*[mNumChildNodes];
		mChildrenNodes[mNumChildNodes - 1] = node;
		mChildNodeNames[node->mName] = mNumChildNodes - 1;
	}
}

Node* Node::createNode(std::string name)
{
	if(mChildrenNodes != NULL)
	{
		Node** tmpObj;
		tmpObj = new Node*[mNumChildNodes + 1];
		for(int i = 0; i < mNumChildNodes; i++)
		{
			tmpObj[i] = mChildrenNodes[i];
		}
		mNumChildNodes++;
		delete [] mChildrenNodes;
		mChildrenNodes = tmpObj;
		mChildrenNodes[mNumChildNodes - 1] = new Node(name);
		mChildNodeNames[name] = mNumChildNodes - 1;
		mChildrenNodes[mNumChildNodes - 1]->mParentNode = this;
		return mChildrenNodes[mNumChildNodes - 1];
	}
	else
	{
		mNumChildNodes++;
		mChildrenNodes = new Node*[mNumChildNodes];
		mChildrenNodes[mNumChildNodes - 1] = new Node(name);
		mChildNodeNames[name] = mNumChildNodes - 1;
		mChildrenNodes[mNumChildNodes - 1]->mParentNode = this;
		return mChildrenNodes[mNumChildNodes - 1];
	}	
	//mChildrenNodes->clear();
	/*int x = getChildVector()->size();
	Node* tmp = new Node(name);
	tmp->mParentNode = this;
	getChildVector()->push_back(tmp);
	return tmp;*/
}

void Node::attachCamera(Camera *camera)
{
	camera->setParent(this);
}
void Node::setSceneTree(SceneTree* scnTree)
{
	mSceneTree = scnTree;
}

void Node::setWorldViewMatrixPtr(Matrix4* worldViewMat)
{
	mWorldViewMat = worldViewMat;
}

Node* Node::getParentNode()
{
	return mParentNode;
}

const Matrix4 Node::_getModelMatrix()
{
	if(mParentNode)
	{
		//return mParentNode->_getModelMatrix() * mLocalTransform;
		return mLocalTransform * mParentNode->_getModelMatrix();
		//return mLocalModelMat * mParentNode->_getModelMatrix();
	}
	return mLocalTransform;
}

const Matrix4& Node::getWorldTransform()
{
	return mWorldTransform;
}

void Node::update()
{
	if(mParentNode)
	{
		mWorldTransform = mParentNode->mWorldTransform * mLocalTransform;
		//mWorldTransform = mLocalTransform * mParentNode->mWorldTransform;
		//mWorldTransform = mLocalTransform * mParentNode->mWorldTransform;
	}
	for(int i = 0; i < mNumChildNodes; i++)
	{
		mChildrenNodes[i]->update();
	}
}

void Node::rotateNodeLocal(float angle, float x, float y, float z)
{
	Matrix3 tmpMat;
	float cs = cos(angle);
	float sn = sin(angle);
	
	float mag = sqrt((x*x)+(y*y)+(z*z));
	x = x/mag;
	y = y/mag;
	z = z/mag;
	
	float xx = x*x;
	float xy = x*y;
	float xz = x*z;
	float yy = y*y;
	float yz = y*z;
	float zz = z*z;
	float one_cs = 1 - cs;
	
	#define M(x) tmpMat[x]
	M(0) = cs + xx*one_cs; M(3) = xy*one_cs-z*sn; M(6)  = xz*one_cs+y*sn;// M(12) = 0.0f;
	M(1) = xy*one_cs+z*sn; M(4) = cs+yy*one_cs;	  M(7)  = yz-x*sn;		 // M(13) = 0.0f;
	M(2) = xz*one_cs-y*sn; M(5) = yz*one_cs+x*sn; M(8) = cs+zz*one_cs;	 // M(14) = 0.0f;
	#undef M
	
	//tmpMat = mLocalTransform.extractRotationMatrix() * tmpMat;
	tmpMat = tmpMat * mLocalTransform.extractRotationMatrix();
	
	mLocalTransform.setRotationMatrix(tmpMat);
}

void Node::translateNodeLocal(float x, float y, float z)
{
	mLocalTransform[12] += x;
	mLocalTransform[13] += y;
	mLocalTransform[14] += z;
}

/*std::vector<Node*>* Node::getChildVector()
{
	static std::vector<Node*>* mChildrenNodes = 0;
	if(!mChildrenNodes)
	{
		mChildrenNodes = new std::vector<Node*>;
	}
	return mChildrenNodes;
}*/




