#include <QtCore\qdir.h>
#include <QtCore\qdebug.h>

#include <Shader/ShaderManager.h>
#include <Shader/MaterialManager.h>

#include <Texture/TextureManager.h>

#include <Model/ModelManager.h>
#include <Model/ModelController.h>
#include <Model/ModelBuilder.h>

#include <Package/AssetManager.h>
#include <Package/PackageManager.h>
#include <Scene/SceneManager.h>

#include <Light/LightController.h>

#include <Input/InputManager.h>

#include <TempHelpers/OglDevTut03.h>

#include <Interface/SceneGraphWidget.h>

#include <Interface/GuiStyleManager.h>

#include "TropicalEngineApplication.h"

TropicalEngineApplication::TropicalEngineApplication(int argc, char* argv[]) : QApplication(argc, argv)
{
	QDir::setCurrent(QCoreApplication::applicationDirPath() + "/../..");
	setWindowIcon(QIcon("./Resource Files/TropicalEngine.png"));

	splashImage = new QPixmap("./Resource Files/SplashScreen.png");
	splashScreen = new QSplashScreen(*splashImage);
	splashScreen->show();

	shaderManager = new ShaderManager();
	materialManager = new MaterialManager();

	textureManager = new TextureManager();

	modelManager = new ModelManager();
	modelController = new ModelController();
	modelBuilder = new ModelBuilder();

	assetManager = new AssetManager();
	packageManager = new PackageManager();
	sceneManager = new SceneManager();

	lightController = new LightController();

	inputManager = new InputManager();

	renderer = new OglDevTut03();

	styleManager = new GuiStyleManager();
	styleManager->ChangeStyle(*this, "./Resource Files/TropicalEngineEditorStyle.css");

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
	renderer->InitializeLevel();
	sceneGraph->Reload();
	splashScreen->close();
}

void TropicalEngineApplication::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	deltaTime = deltaTimer.restart();
	inputManager->Update();
	
	sceneManager->getCurrentCamera()->CalculateMatrix();

	sceneManager->EvaluateLevels();	///TODO: Evaluate only changed
	modelController->DrawAll(sceneManager->getCurrentCamera());
	
}