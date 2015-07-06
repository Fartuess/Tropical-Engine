//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


#include <gl/glew.h>
#include <glm.hpp>

#include "Interface/MainWindow.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qstatusbar.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qspinbox.h>
#include <QtCore/qthread.h>

#include "Scene/Entity.h"
#include "Scene/Level.h"
#include "TempHelpers/OglDevTut03.h"
#include "TropicalEngineApplication.h"

Level* OglDevTut03::level;


int main(int argc, char* argv[])
{
	TropicalEngineApplication tropicalEngine(argc, argv);
	MainWindow mainWindow(0, true);

	return tropicalEngine.exec();
}