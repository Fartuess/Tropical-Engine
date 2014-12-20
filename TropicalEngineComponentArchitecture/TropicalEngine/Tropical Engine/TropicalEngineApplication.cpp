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

#include "SceneGraphWidget.h"

#include "GuiStyleManager.h""

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

	styleManager = new GuiStyleManager();
	styleManager->ChangeStyle(*this, "../Tropical Engine/TropicalEngineEditorStyle.css");

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
}

void TropicalEngineApplication::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	deltaTime = deltaTimer.restart();
	inputController->Update(deltaTime);
	sceneManager->getCurrentCamera()->CalculateMatrix();

	sceneManager->EvaluateLevels();	///TODO: Evaluate only changed
	modelController->DrawAll(sceneManager->getCurrentCamera());
}