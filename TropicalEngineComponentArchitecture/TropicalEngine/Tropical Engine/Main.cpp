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
#include "OpenGLWidget.h"

#include "Entity.h"
#include "Level.h"
#include "OglDevTut03.h"
#include "TropicalEngineApplication.h"

Level* OglDevTut03::level;

int main(int argc, char* argv[])
{
	TropicalEngineApplication tropicalEngine(argc, argv);
	MainWindow* mainWindow = new MainWindow();
	QMenuBar* mainMenu = new QMenuBar();
	QStatusBar* statusBar = new QStatusBar();
	statusBar->showMessage("Engine Initialized");
	QMenu* fileMenu = new QMenu();
	fileMenu->setTitle("File");
	QMenu* assetsMenu = new QMenu();
	assetsMenu->setTitle("Assets");
	QMenu* miscelanousMenu = new QMenu();
	miscelanousMenu->setTitle("Miscelanous");

	QWidget* mainWidget = new QWidget();
	mainWindow->setCentralWidget(mainWidget);
	fileMenu->addAction("Exit");
	assetsMenu->addAction("Import Model");
	assetsMenu->addAction("Import Texture");
	miscelanousMenu->addAction("Log");
	miscelanousMenu->addAction("About");
	mainMenu->addMenu(fileMenu);
	mainMenu->addMenu(assetsMenu);
	mainMenu->addMenu(miscelanousMenu);
	mainWindow->setMenuBar(mainMenu);
	mainWindow->setStatusBar(statusBar);

	QHBoxLayout* mainLayout = new QHBoxLayout();
	QMenuBar* mainMenuBar = new QMenuBar();
	QSplitter* mainLayoutSplitter = new QSplitter();
	OpenGLWidget* openGLWindow = new OpenGLWidget();
	openGLWindow->grabKeyboard();
	//openGLWindow->grabMouse();
	QFrame* leftPanel = new QFrame();
	QFrame* rightPanel = new QFrame();
	QVBoxLayout* leftPanelLayout = new QVBoxLayout();
	QVBoxLayout* rightPanelLayout = new QVBoxLayout();

	QLabel* propertiesLabel = new QLabel();
	propertiesLabel->setText("Properties");
	//QTreeView* propertiesList = new QTreeView();
	//QToolBox* propertiesToolbox = new QToolBox();
	QGroupBox* lightGroupBox = new QGroupBox("Light Properties");

	QGroupBox* positionGroupBox = new QGroupBox("Position");
	QGroupBox* rotationGroupBox = new QGroupBox("Rotation");
	QGroupBox* scaleGroupBox = new QGroupBox("Scale");


	QFrame* leftPanelButtonFrame = new QFrame();
	QHBoxLayout* leftPanelButtonLayout = new QHBoxLayout();
	QPushButton* addComponentButton = new QPushButton();
	addComponentButton->setText("Add Component");
	QPushButton* deleteComponentButton = new QPushButton();
	deleteComponentButton->setText("Delete Component");
	//leftPanelButtonLayout->addWidget(addComponentButton);
	//leftPanelButtonLayout->addWidget(deleteComponentButton);
	leftPanelButtonFrame->setLayout(leftPanelButtonLayout);

	QLabel* sceneGraphLabel = new QLabel();
	sceneGraphLabel->setText("Scene Graph");
	QTreeView* sceneGraph = new QTreeView();
	QFrame* rightPanelButtonFrame = new QFrame();
	QHBoxLayout* rightPanelButtonLayout = new QHBoxLayout();
	QPushButton* addObjectButton = new QPushButton();
	addObjectButton->setText("Add Object");
	QPushButton* deleteObjectButton = new QPushButton();
	deleteObjectButton->setText("Delete Object");
	rightPanelButtonLayout->addWidget(addObjectButton);
	rightPanelButtonLayout->addWidget(deleteObjectButton);
	rightPanelButtonFrame->setLayout(rightPanelButtonLayout);

	leftPanel->setLayout(leftPanelLayout);
	rightPanel->setLayout(rightPanelLayout);
	leftPanelLayout->addWidget(propertiesLabel);
	//leftPanelLayout->addWidget(propertiesList);
	//leftPanelLayout->addWidget(propertiesToolbox);
	leftPanelLayout->addWidget(lightGroupBox);
	leftPanelLayout->addWidget(positionGroupBox);
	leftPanelLayout->addWidget(rotationGroupBox);
	leftPanelLayout->addWidget(scaleGroupBox);
	leftPanelLayout->addWidget(leftPanelButtonFrame);
	rightPanelLayout->addWidget(sceneGraphLabel);
	rightPanelLayout->addWidget(sceneGraph);
	rightPanelLayout->addWidget(rightPanelButtonFrame);
    mainLayoutSplitter->addWidget(leftPanel);
	mainLayoutSplitter->addWidget(openGLWindow);
	mainLayoutSplitter->addWidget(rightPanel);
	mainLayout->addWidget(mainLayoutSplitter);
	mainWidget->setLayout(mainLayout);

	//foreach(Entity* object, OglDevTut03::level->root.subobjects)
	//{
	//	if(object->name != nullptr)
	//	{
	//		qDebug(object->name->toLatin1());
	//	}
	//}

	mainWindow->show();

	return tropicalEngine.exec();
}