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
#include "Interface\OpenGLWidget.h"
#include "Interface\SceneGraphWidget.h"
#include "Interface\PropertiesWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	QWidget* titleBar;
	QHBoxLayout* TitleBarLayout;

	QMenuBar* mainMenu;
	QStatusBar* statusBar;
	QMenu* fileMenu;
	QMenu* assetsMenu;
	QMenu* miscelanousMenu;
	QWidget* superWidget;
	QWidget* mainWidget;
	QVBoxLayout* superLayout;	
	QHBoxLayout* mainLayout;
	OpenGLWidget* openGLWindow;

	QMenuBar* mainMenuBar;	//is it needed?
	QVBoxLayout* leftPanelLayout;
	QVBoxLayout* rightPanelLayout;

	SceneGraphWidget* sceneGraph;
	PropertiesWidget* propertiesWidget;

private:
	QSizePolicy* expandVertically;
public:
	MainWindow(QWidget* parrent = 0, bool isFrameless = false);
	~MainWindow(void);

public slots:
	void saveAs();
};

