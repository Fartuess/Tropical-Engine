#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "MainWindow.h"
#include <QtWidgets\qapplication.h>
#include <QtWidgets\QHBoxLayout>
#include <QtWidgets\qsplitter.h>
#include <QtWidgets\qtreeview.h>
#include "OpenGLWidget.h"

int main(int argc, char* argv[])
{
	QApplication tropicalEngine(argc, argv);
	MainWindow* mainWindow = new MainWindow();
	QHBoxLayout* mainLayout = new QHBoxLayout();
	QSplitter* mainLayoutSplitter = new QSplitter();
	OpenGLWidget* openGLWindow = new OpenGLWidget();
	QTreeView* leftPanel = new QTreeView();
	QTreeView* rightPanel = new QTreeView();
    mainLayoutSplitter->addWidget(leftPanel);
	mainLayoutSplitter->addWidget(openGLWindow);
	mainLayoutSplitter->addWidget(rightPanel);
	mainLayout->addWidget(mainLayoutSplitter);
	mainWindow->setLayout(mainLayout);
	mainWindow->show();

	return tropicalEngine.exec();
}