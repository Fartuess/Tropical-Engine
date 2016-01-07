//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <GL/glew.h>
#include <GL/GL.h>

#include <Interface/MainWindow.h>

#include <Scene/Level.h>
#include <TempHelpers/OglDevTut03.h>

#include "TropicalEngineApplication.h"

using namespace TropicalEngine;

	Level* OglDevTut03::level;

	int main(int argc, char* argv[])
	{
		TropicalEngineApplication tropicalEngine(argc, argv);
		MainWindow mainWindow(0, true);

		return tropicalEngine.exec();
	}
