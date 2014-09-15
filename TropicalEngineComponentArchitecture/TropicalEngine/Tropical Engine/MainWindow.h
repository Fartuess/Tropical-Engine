#pragma once
#include <QtWidgets\qmainwindow.h>
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
#include "OpenGLWidget.h"
#include "SceneGraphWidget.h"
#include "PropertiesWidget.h"

class MainWindow : public QMainWindow
{
public:
	QMenuBar* mainMenu;
	QStatusBar* statusBar;
	QMenu* fileMenu;
	QMenu* assetsMenu;
	QMenu* miscelanousMenu;
	QWidget* mainWidget;
	QHBoxLayout* mainLayout;
	OpenGLWidget* openGLWindow;

	QMenuBar* mainMenuBar;
	QVBoxLayout* leftPanelLayout;
	QVBoxLayout* rightPanelLayout;

	SceneGraphWidget* sceneGraph;
	PropertiesWidget* propertiesWidget;

	MainWindow(void);
	~MainWindow(void);
};

