#pragma once
#include <QtWidgets\qmainwindow.h>

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

	MainWindow(void);
	~MainWindow(void);
};

