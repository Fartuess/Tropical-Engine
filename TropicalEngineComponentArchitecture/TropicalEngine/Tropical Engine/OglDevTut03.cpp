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

#include <vector>

glm::vec2 OglDevTut03::cameraPosition = glm::vec2(-0.5f, 0.5f);

void OglDevTut03::Initialize()
{
	glm::vec3 Vertices[3];
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	//ModelBuilder::Instance().CreateTriangle("Triangle");
	//triangleModel = ModelManager::Instance().getModel("Triangle");
	//triangleModel = TropicalEngineApplication::instance()->modelBuilder->CreateTriangle("Triangle");

	ModelBuilder tempModelBuilder = ModelBuilder();
	//triangleModel = tempModelBuilder.CreateTriangle("Triangle");
	triangleModel = tempModelBuilder.CreateSphere("Triangle");

	cameraPosition = glm::vec2(0.0f, 0.5f);

	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//QVector<GLfloat>* testBuffer = new QVector<GLfloat>();
	//testBuffer->size();
	//triangleModel->meshes[0].testVertices->count();

	//GLfloat* testVertices = (GLfloat*) malloc(3 * 3 *sizeof(GLfloat));
	//memcpy(testVertices, triangleModel->meshes[0].testVertices->data(), 3 * 3 *sizeof(GLfloat));

	//std::vector<glm::vec3>* testVector = new std::vector<glm::vec3>();
	//QVector<glm::vec3>* testVector2 = new QVector<glm::vec3>();

	//testVector = (glm::vec3*) malloc(3 * sizeof(glm::vec3));
	//testVector->push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	//testVector->push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	//testVector->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	//
	//testVector2->push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	//testVector2->push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	//testVector2->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	//
	//int t1 = sizeof(Vertices);
	//int t2 = sizeof(GLfloat) * 3 * 3;
	//int t3 = sizeof(glm::vec3) * 3;
	//bool test = sizeof(Vertices) == sizeof(GLfloat) * triangleModel->meshes[0].testVertices->count();

	//triangleModel->meshes[0].testVertices[0][0] = Vertices[0];
	//triangleModel->meshes[0].testVertices[0][1] = Vertices[1];
	//triangleModel->meshes[0].testVertices[0][2] = Vertices[2];

	//Vertices[0] = triangleModel->meshes[0].testVertices[0][0];
	//Vertices[1] = triangleModel->meshes[0].testVertices[0][1];
	//Vertices[2] = triangleModel->meshes[0].testVertices[0][2];


	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * triangleModel->meshes[0].testVertices->size(), triangleModel->meshes[0].testVertices->data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * testVector2->size(), testVector2->data(), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	//simple = new Shader("../Tropical Engine/Simple_VS.glsl", "../Tropical Engine/Simple_PS.glsl", "Simple");
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

	//glGenVertexArrays(1, &triangleModel->meshes[0].VAO);
	glBindVertexArray(triangleModel->meshes[0].VAO);

	//glEnableVertexAttribArray(simple->getVertexLocation());
	//glBindBuffer(GL_ARRAY_BUFFER, triangleModel->meshes[0].vertexVBO);
    //glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//
	//glEnableVertexAttribArray(simple->getNormalLocation());
	//glBindBuffer(GL_ARRAY_BUFFER, triangleModel->meshes[0].normalVBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//
	//glBindVertexArray(triangleModel->meshes[0].VAO);

	//ShaderManager::Instance().UseShader(simple);

	glDrawArrays(GL_TRIANGLES, 0, triangleModel->meshes[0].NumVertex);

    //glDisableVertexAttribArray(simple->getVertexLocation());
	//glDisableVertexAttribArray(simple->getNormalLocation());

	glBindVertexArray(0);

	//ModelController::Instance().DrawAll(SceneManager::Instance().getCurrentCamera());
}