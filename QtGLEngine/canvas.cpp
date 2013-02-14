/*#include "canvas.h"
#include <QKeyEvent>
#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;


static GLfloat lightPosition[4] = { 0.0, 0.0, 15.0, 1.0 };
static GLfloat lightDiffuse[4] = {2, 2, 2, 1};
static GLfloat lightSpecular[4] = {-.2, -.2, -.2, 1};
static GLfloat lightAmbient[4] = {-.5, -.5, -.5, 1};

static GLfloat lightPosition2[4] = { -15.0, 0.0, 0.0, 1.0 };
static GLfloat lightDiffuse2[4] = {2, 2, 2, 1};
static GLfloat lightSpecular2[4] = {-.2, -.2, -.2, 1};
static GLfloat lightAmbient2[4] = {-.5, -.5, -.5, 1};

Canvas::Canvas(QWidget *parent) : QGLWidget(parent)
{
	this->resize(700, 700);

	xpos = 0;

	//render = true;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(10);
}

Canvas::~Canvas()
{
	cube->~CubePrimitive();
}

void Canvas::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);


	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_COLOR_MATERIAL);

	cube = new CubePrimitive(9);
	cube->setColor(1,1,1);
	lightPoint = new CubePrimitive(.5);
	lightPoint->setColor(1,1,1);
	lightPoint->setPos(-15,0,0);

	glMatrixMode(GL_MODELVIEW);



	//lightPosition = { -10.0, 0.0, 0.0, 1.0 };
	//lightDiffuse[4] = {2, 2, 2, 1};
	//lightSpecular[4] = {-.2, -.2, -.2, 1};
	//lightAmbient[4] = {-2, -2, -2, 1};
	//lightDirection[3] = {0, 0, 1};

	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient2);
	glEnable(GL_LIGHT1);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);

	//glDisable(GL_LIGHT0);

	setupShaders();

	glEnable(GL_NORMALIZE);
	glEnable(GL_RESCALE_NORMAL);

	glEnable(GL_COLOR_MATERIAL);

	glViewport(0,0,this->width(), this->height());
	cam.setPosition(0, 0, 30);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(65,this->width()/this->height(),1.0,5000.0);

	//gluLookAt(8,8,8,0,0,0,0,0,1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Canvas::startRendering()
{
	render = true;
}

void Canvas::stopRendering()
{
	render = false;
}

void Canvas::animate()
{
	if(render)
		updateGL();
}

void Canvas::keyPressEvent(QKeyEvent * e)
{
	if(e->key() == Qt::Key_Up)
		cam.translate(0,5,0);
	if(e->key() == Qt::Key_Down)
		cam.translate(0,-5,0);
	if(e->key() == Qt::Key_Right)
		cam.translate(5,0,0);
	if(e->key() == Qt::Key_Left)
		cam.translate(-5,0,0);
	if(e->key() == Qt::Key_W)
		cam.translate(0,0,-5);
	if(e->key() == Qt::Key_S)
		cam.translate(0,0,5);
	if(e->key() == Qt::Key_D)
		cam.rotate(0,-10,0);
	if(e->key() == Qt::Key_A)
		cam.rotate(0,10,0);


}

void Canvas::paintGL()
{
	static double cnt = 0;

	GLuint cam1Loc = glGetUniformLocation(p, "CAMERA_POSITION");
	GLuint texLoc = glGetUniformLocation(p, "baseTex");
	GLuint heightLoc = glGetUniformLocation(p, "heightMap");
	GLuint numLights = glGetUniformLocation(p, "numLights");
	GLuint fpNumLights = glGetUniformLocation(p, "fpNumLights");

	GLfloat fLargest;
	xrot += .6;
	xpos = 10*sin((cnt += .1));


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0,0,0,1);

	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

	//cube->setRot(xrot, 0, 0);

	glUseProgram(p);

	glUniform1i(texLoc, 0);
	glUniform1i(heightLoc, 1);
	glUniform3f(cam1Loc, cam.getPosition()[0], cam.getPosition()[1], cam.getPosition()[2]);
	glUniform1i(numLights, 1);
	glUniform1i(fpNumLights, 1);


	glPushMatrix();

		cam.draw();

		lightPosition[0] = xpos;
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);

		glPushMatrix();
			cube->draw();
		glPopMatrix();


		glDisable(GL_LIGHT0);
		glPushMatrix();
			glBegin(GL_LINE_STRIP);
				//x Axis
				glColor3f(1,0,0);
				glVertex3f(0,0,0);
				glVertex3f(70,0,0);

				//y Axis
				glColor3f(0,1,0);
				glVertex3f(0,0,0);
				glVertex3f(0,70,0);

				//z Axis
				glColor3f(0,0,1);
				glVertex3f(0,0,0);
				glVertex3f(0,0,70);

			glEnd();
		glPopMatrix();
		glEnable(GL_LIGHT0);

		glPushMatrix();
			lightPoint->draw();
		glPopMatrix();



	glPopMatrix();

}

void Canvas::setupShaders()
{
	string fragSrc;
	string vertSrc;
	GLint testVal;

	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);

	vertSrc = readShaderFile("../../vertex.vs");
	fragSrc = readShaderFile("../../fragment.fs");

	const char * vv = vertSrc.c_str();
	const char * ff = fragSrc.c_str();

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);

	//free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);

	glGetShaderiv(v, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[1024];
		glGetShaderInfoLog(v, 1024, NULL, infoLog);
		cout << "Vertex shader compile failed! Error: " << infoLog << endl;
	}

	glGetShaderiv(f, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[1024];
		glGetShaderInfoLog(v, 1024, NULL, infoLog);
		cout << "Fragment shader compile failed! Error: " << infoLog << endl;
	}

	p = glCreateProgram();

	glAttachShader(p,v);
	glAttachShader(p,f);

	glLinkProgram(p);
}

string Canvas::readShaderFile(string fileName)
{
	ifstream iFile;
	string output;

	iFile.open(fileName.c_str());

	if(iFile.fail())
	{
		cout << "fail" << endl;
		return "fail";
	}

	while(!iFile.eof())
	{
		string temp;
		iFile >> temp;
		if(temp.find(";") != -1)
			temp += "\n";
		output += (" " + temp);
	}
	cout << output << endl;
	return output;
}
 
 */
