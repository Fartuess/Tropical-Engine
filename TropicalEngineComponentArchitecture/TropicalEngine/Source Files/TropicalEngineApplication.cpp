#include <QtCore/qdir.h>
#include <QtCore/qdebug.h>

#include <Scene/Scene.h>

#include <Rendering/RenderingManager.h>

#include <Input/InputManager.h>

#include <TempHelpers/OglDevTut03.h>

#include <Interface/SceneGraphWidget.h>
#include <Interface/GuiStyleManager.h>

#include <Utills/MathUtills.h>
#include <Utills/UpdateManager.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	TropicalEngineApplication::TropicalEngineApplication(int argc, char* argv[]) : QApplication(argc, argv)
	{

		QDir::setCurrent(QCoreApplication::applicationDirPath() + "/../..");
		setWindowIcon(QIcon("./Resource Files/TropicalEngine.png"));

		splashImage = new QPixmap("./Resource Files/SplashScreen.png");
		splashScreen = new QSplashScreen(*splashImage);
		splashScreen->show();

		tempScene = new Scene();

		GuiStyleManager::instance().ChangeStyle(*this, "./Resource Files/TropicalEngineEditorStyle.css");

		EngineSettings = new QSettings("./Resource Files/EngineSettings.ini", QSettings::IniFormat);
		EditorSettings = new QSettings("./Resource Files/EditorSettings.ini", QSettings::IniFormat);
	}

	TropicalEngineApplication::~TropicalEngineApplication(void)
	{
	}

	TropicalEngineApplication* TropicalEngineApplication::instance()
	{
		return (TropicalEngineApplication*)(QApplication::instance());
	}

	void TropicalEngineApplication::Initialize()
	{
		deltaTimer.start();
		RenderingManager::instance();
		OglDevTut03::instance().InitializeLevel(tempScene);
		sceneGraph->Reload();
		splashScreen->close();
	}

	void TropicalEngineApplication::Draw()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPatchParameteri(GL_PATCH_VERTICES, 3);

		UpdateManager::instance().UpdateAll();
		InputManager::instance().Update();
		deltaTime = deltaTimer.restart();

		tempScene->EvaluateLevels();	// TODO: Evaluate only changed
		RenderingManager::instance().DrawAll(tempScene);
	}

}