#include <glm.hpp>
#include "Shader.h"
#include "ModelController.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "CameraComponent.h"
#include "OglDevTut03.h"

glm::vec2 OglDevTut03::cameraPosition = glm::vec2(0.0f, 0.5f);

void OglDevTut03::Initialize()
{
	glm::vec3 Vertices[3];
    Vertices[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
    Vertices[1] = glm::vec3(1.0f, -1.0f, 0.0f);
    Vertices[2] = glm::vec3(0.0f, 1.0f, 0.0f);

	cameraPosition = glm::vec2(0.0f, 0.5f);

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	simple = new Shader("../Tropical Engine/Simple_VS.glsl", "../Tropical Engine/Simple_PS.glsl", "Simple");

	cameraLocation = glGetUniformLocation(simple->shaderProgram, "u_cameraPosition");

	InitializeLevel();
}

void OglDevTut03::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	SceneManager::Instance().getCurrentCamera()->CalculateMatrix();

	ShaderManager::Instance().UseShader(simple);

	glUniform2f(cameraLocation, OglDevTut03::cameraPosition.x, cameraPosition.y);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//ShaderManager::Instance().UseShader(simple);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

	ModelController::Instance().DrawAll(SceneManager::Instance().getCurrentCamera());
}