#include <glm.hpp>
#include <QtCore\qvector.h>
#include "InputController.h"
#include "Shader.h"
#include "Model.h"
#include "ModelManager.h"
#include "ModelBuilder.h"
#include "ModelController.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "CameraComponent.h"
#include "OglDevTut03.h"

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
	TropicalEngineApplication::instance()->inputController->Update(deltaTime);
	TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->CalculateMatrix();

	TropicalEngineApplication::instance()->sceneManager->EvaluateLevels();	///TODO: Evaluate only changed
	TropicalEngineApplication::instance()->modelController->DrawAll(TropicalEngineApplication::instance()->sceneManager->getCurrentCamera());
}