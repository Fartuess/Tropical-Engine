#include "TropicalEngineApplication.h"

#include "ShaderManager.h"
#include "MaterialManager.h"

#include "TextureManager.h"

#include "ModelManager.h"
#include "ModelController.h"
#include "ModelBuilder.h"

#include "PackageManager.h"
#include "SceneManager.h"

#include "LightController.h"

#include "InputController.h"

#include "OglDevTut03.h"

TropicalEngineApplication::TropicalEngineApplication(int argc, char* argv[]) : QApplication(argc, argv)
{
	shaderManager = new ShaderManager();
	materialManager = new MaterialManager();

	textureManager = new TextureManager();

	modelManager = new ModelManager();
	modelController = new ModelController();
	modelBuilder = new ModelBuilder();

	packageManager = new PackageManager();
	sceneManager = new SceneManager();

	lightController = new LightController();

	inputController = new InputController();

	renderer = new OglDevTut03();
}

TropicalEngineApplication::~TropicalEngineApplication(void)
{
}

TropicalEngineApplication* TropicalEngineApplication::instance()
{
	return (TropicalEngineApplication*)(QApplication::instance());
}