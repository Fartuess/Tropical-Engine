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
#include <QtWidgets\qfiledialog.h>
#include <QtCore\qjsondocument.h>

#include "Interface\OpenGLWidget.h"
#include "Interface\SceneGraphItem.h"

#include "TropicalEngineApplication.h"
#include "Interface\GuiStyleManager.h"

#include "Interface\MainWindow.h"
#include "Interface\TitleBar.h"

#include "Scene\SceneManager.h"
#include "Scene\Level.h"

#include <QtCore\qdebug.h>

MainWindow::MainWindow(QWidget* parrent, bool isFrameless): QMainWindow(parrent)
	///TODO: Figure out which references to UI elements should be kept.
{
	if(isFrameless == true)
	{
		setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
	}

	show();
	resize(800, 600);

	expandVertically = new QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	//
	//TitleBar = new QWidget();
	//TitleBarLayout = new QHBoxLayout();
	////TitleBar->setMinimumHeight(30);
	////TitleBar->setMaximumHeight(30);
	//TitleBar->setSizePolicy(*expandVertically);
	//
	//QLabel* Title = new QLabel("Tropical Engine");
	//Title->setObjectName("Title");
	//QPushButton* minimize = new QPushButton("-");
	//QPushButton* maximize = new QPushButton("O");
	//QPushButton* close = new QPushButton("X");
	//
	//TitleBarLayout->addWidget(Title);
	//TitleBarLayout->addStretch();
	//TitleBarLayout->addWidget(minimize);
	//TitleBarLayout->addWidget(maximize);
	//TitleBarLayout->addWidget(close);

	titleBar = new TitleBar(this);

	mainMenu = new QMenuBar();
	statusBar = new QStatusBar();
	statusBar->showMessage("Engine Initialized");
	fileMenu = new QMenu();
	fileMenu->setTitle("File");
	assetsMenu = new QMenu();
	assetsMenu->setTitle("Assets");
	miscelanousMenu = new QMenu();
	miscelanousMenu->setTitle("Miscelanous");

	superWidget = new QWidget();
	mainWidget = new QWidget();
	setCentralWidget(superWidget);
	QAction* saveAsAction = fileMenu->addAction("Save as");
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	fileMenu->addAction("Exit");
	assetsMenu->addAction("Import Model");
	assetsMenu->addAction("Import Texture");
	miscelanousMenu->addAction("Log");
	miscelanousMenu->addAction("About");
	mainMenu->addMenu(fileMenu);
	mainMenu->addMenu(assetsMenu);
	mainMenu->addMenu(miscelanousMenu);
	//setMenuBar(mainMenu);
	//setStatusBar(statusBar);
	mainMenu->setSizePolicy(*expandVertically);
	statusBar->setSizePolicy(*expandVertically);
	//mainMenu->setMaximumHeight(20);
	//statusBar->setMaximumHeight(20);

	superLayout = new QVBoxLayout();
	mainLayout = new QHBoxLayout();
	
	mainMenuBar = new QMenuBar();
	QSplitter* mainLayoutSplitter = new QSplitter();
	openGLWindow = new OpenGLWidget();
	openGLWindow->grabKeyboard();
	//openGLWindow->grabMouse();
	QFrame* leftPanel = new QFrame();
	QFrame* rightPanel = new QFrame();
	leftPanelLayout = new QVBoxLayout();
	rightPanelLayout = new QVBoxLayout();

	QLabel* propertiesLabel = new QLabel();
	propertiesLabel->setText("Properties");
	propertiesWidget = new PropertiesWidget();

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
	//sceneGraphLabel->setPixmap(QPixmap("../Assets/Core/DefaultTexturePNG.png"));
	//sceneGraphLabel->show();
	sceneGraph = new SceneGraphWidget();
	TropicalEngineApplication::instance()->sceneGraph = sceneGraph;

	connect(sceneGraph, SIGNAL(itemSelectionChanged()), propertiesWidget, SLOT(Reload()));

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
	leftPanelLayout->addWidget(propertiesWidget);
	leftPanelLayout->addWidget(leftPanelButtonFrame);
	rightPanelLayout->addWidget(sceneGraphLabel);
	rightPanelLayout->addWidget(sceneGraph);
	rightPanelLayout->addWidget(rightPanelButtonFrame);
    mainLayoutSplitter->addWidget(leftPanel);
	mainLayoutSplitter->addWidget(openGLWindow);
	mainLayoutSplitter->addWidget(rightPanel);
	mainLayout->addWidget(mainLayoutSplitter);
	mainWidget->setLayout(mainLayout);
	superWidget->setLayout(superLayout);

	if(isFrameless)
	{
		superLayout->addWidget(titleBar);
	}
	superLayout->addWidget(mainMenu);
	superLayout->addWidget(mainWidget);
	superLayout->addWidget(statusBar);
	superLayout->setMargin(0);
	superLayout->setSpacing(0);

	//titleBar->setLayout(TitleBarLayout);
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save Level"), "",
		tr("ASCII Tropical Level (*.tlvl);;All Files (*)")
		);
		//, 0,
		//QFileDialog::DontUseNativeDialog);
	qDebug() << fileName;

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly))
	{
		return;
	}
	QTextStream out(&file);
	///TODO: figure out which level to save
	out << 	QJsonDocument(TropicalEngineApplication::instance()->sceneManager->getLevels().first()->toJSON()).toJson();
	file.close();
}