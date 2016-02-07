#include <QtCore/qdir.h>
#include <QtCore/qdebug.h>

#include <Shader/ShaderManager.h>
#include <Shader/MaterialManager.h>

#include <Texture/TextureManager.h>

#include <Model/ModelManager.h>
#include <Model/ModelBuilder.h>

#include <Package/AssetManager.h>
#include <Package/PackageManager.h>

#include <Scene/Scene.h>
#include <Scene/SceneManager.h>

#include <Rendering/RenderingManager.h>

#include <Light/LightController.h>

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
		//math::registerGLMtypes();

		QDir::setCurrent(QCoreApplication::applicationDirPath() + "/../..");
		setWindowIcon(QIcon("./Resource Files/TropicalEngine.png"));

		splashImage = new QPixmap("./Resource Files/SplashScreen.png");
		splashScreen = new QSplashScreen(*splashImage);
		splashScreen->show();

		//shaderManager = new ShaderManager();
		//materialManager = new MaterialManager();
		//
		//textureManager = new TextureManager();
		//
		//modelManager = new ModelManager();
		//modelBuilder = new ModelBuilder();
		//
		//assetManager = new AssetManager();
		//packageManager = new PackageManager();
		//sceneManager = new SceneManager();
		tempScene = new Scene();
		//renderingManager = new RenderingManager();
		//
		//lightController = new LightController();
		//
		//updateManager = new UpdateManager();
		//
		//inputManager = new InputManager();
		//
		//renderer = new OglDevTut03();
		//

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

		tempScene->getCurrentCamera()->CalculateMatrix();

		tempScene->EvaluateLevels();	// TODO: Evaluate only changed
		RenderingManager::instance().DrawAll(tempScene);
	}

}