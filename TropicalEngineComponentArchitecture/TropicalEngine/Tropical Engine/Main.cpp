//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <gl\glew.h>

#include "MainWindow.h"
#include <QtWidgets\qapplication.h>
#include <QtWidgets\qmenubar.h>
#include <QtWidgets\qstatusbar.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\qsplitter.h>
#include <QtWidgets\qtreeview.h>
#include <QtWidgets\qpushbutton.h>
//#include <QtWidgets\qtoolbox.h>
#include <QtWidgets\qgroupbox.h>
#include <QtWidgets\qspinbox.h>
#include <QtCore\qthread.h>

#include "Entity.h"
#include "Level.h"
#include "OglDevTut03.h"
#include "TropicalEngineApplication.h"

Level* OglDevTut03::level;

int main(int argc, char* argv[])
{
	TropicalEngineApplication tropicalEngine(argc, argv);
	MainWindow* mainWindow = new MainWindow();
	mainWindow->show();

	return tropicalEngine.exec();
}