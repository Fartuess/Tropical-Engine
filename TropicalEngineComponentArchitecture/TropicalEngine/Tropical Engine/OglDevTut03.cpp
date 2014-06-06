#include <glm.hpp>
#include <QtCore\qvector.h>
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

glm::vec2 OglDevTut03::cameraPosition = glm::vec2(0.0f, 0.5f);

void OglDevTut03::Initialize()
{
	glm::vec3 Vertices[3];
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	//ModelBuilder::Instance().CreateTriangle("Triangle");
	//triangleModel = ModelManager::Instance().getModel("Triangle");
	triangleModel = TropicalEngineApplication::instance()->modelBuilder->CreateTriangle("Triangle");

	cameraPosition = glm::vec2(0.0f, 0.5f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	QVector<GLfloat>* testBuffer = new QVector<GLfloat>();
	testBuffer->size();
	//triangleModel->meshes[0].testVertices->count();
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangleModel->meshes[0].testVertices->count(), triangleModel->meshes[0].testVertices->data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	simple = new Shader("../Tropical Engine/Simple_VS.glsl", "../Tropical Engine/Simple_PS.glsl", "Simple");

	cameraLocation = glGetUniformLocation(simple->shaderProgram, "u_cameraPosition");

	InitializeLevel();
}

void OglDevTut03::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	TropicalEngineApplication::instance()->sceneManager->getCurrentCamera()->CalculateMatrix();

	TropicalEngineApplication::instance()->shaderManager->UseShader(simple);

	glUniform2f(cameraLocation, OglDevTut03::cameraPosition.x, cameraPosition.y);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//ShaderManager::Instance().UseShader(simple);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

	//ModelController::Instance().DrawAll(SceneManager::Instance().getCurrentCamera());
}