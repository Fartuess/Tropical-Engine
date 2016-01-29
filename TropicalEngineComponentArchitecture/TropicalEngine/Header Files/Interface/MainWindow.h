#pragma once
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qstatusbar.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qtreeview.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qgroupbox.h>

#include "OpenGLWidget.h"
#include "SceneGraphWidget.h"
#include "PropertiesWidget.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Main window of Editor Application.
	  */
	#pragma endregion
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

		MainWindow(QWidget* parrent = 0, bool isFrameless = false);
		~MainWindow(void);

		public slots:
		void newLevel();
		void saveLevel();
		void saveLevelAs();

	private:
		QSizePolicy* expandVertically;
	};

}