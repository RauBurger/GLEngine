#ifndef CANVAS_H
#define CANVAS_H

//#include <QWidget>
/*
#ifdef __APPLE__
	#include <QtOpenGL/QGLWidget>
	#include <QtCore/QTimer>
#elif _WIN32
	#include <QGLWidget>
	#include <QTimer>
#endif

#include <vector>
#include <string>
#include "Object.h"
#include "cubeprimitive.h"
#include "Camera.h"

using namespace std;

class Canvas : public QGLWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

	void startRendering();
	void stopRendering();

	//Object* createObject(string name);
	//Camera* createCamera(string name);
protected:
    void initializeGL();
    void paintGL();

	void keyPressEvent(QKeyEvent *);

	//void paintEvent(QPaintEvent*);
	//void timerEvent(QTimerEvent* event);

public slots:
	void animate();

private:
	void setupShaders();
	string readShaderFile(string fileName);

	GLuint p;
	QTimer *timer;
	//vector<Object> objs;
	//vector<string> names;
	CubePrimitive* cube;
	CubePrimitive* lightPoint;
	//vector<Camera> cams;
	Camera cam;
	double xrot;
	double xpos;
	bool render;

};
*/
#endif // CANVAS_H
