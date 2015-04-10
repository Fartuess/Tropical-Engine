#include <glm.hpp>
#include <QtCore\qvector.h>
#include "Input\InputManager.h"
#include "Shader\Shader.h"
#include "Model\Model.h"
#include "Model\ModelManager.h"
#include "Model\ModelBuilder.h"
#include "Model\ModelController.h"
#include "Shader\ShaderManager.h"
#include "Scene\SceneManager.h"
#include "Camera/CameraComponent.h"
#include "TempHelpers\OglDevTut03.h"

#include "TropicalEngineApplication.h"

void OglDevTut03::Initialize()
{
	InitializeLevel();
	deltaTimer.start();
}

void OglDevTut03::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	deltaTime = deltaTimer.restart();
	TropicalEngineApplication::instance()->inputManager->Update();
	TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->CalculateMatrix();

	TropicalEngineApplication::instance()->sceneManager->EvaluateLevels();	///TODO: Evaluate only changed
	TropicalEngineApplication::instance()->modelController->DrawAll(TropicalEngineApplication::instance()->sceneManager->getCurrentCamera());
}