//#include <QtGui/QApplication>

//#include "canvas.h"
#include <iostream>
#include "Core.h"
#include "cubeprimitive.h"
#ifdef __APPLE__
#include "mach-o/dyld.h"
#endif
#include <SceneTree.h>
#include <Node.h>
#include "app.h"

int main(int argc, char *argv[])
{	
	App app(argc, argv);
	app.init();
	return app.Run();
}