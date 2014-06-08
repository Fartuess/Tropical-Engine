#include <gl\glew.h>
#include <glm.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreateTriangle(QString name)
{
	MeshEntry* Triangle = new MeshEntry();

	Triangle->NumVertex = 3;

	QVector<glm::vec4>* vertices = new QVector<glm::vec4>();
	QVector<glm::vec3>* normals = new QVector<glm::vec3>();
	QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
	QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
	QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();

	vertices->reserve(Triangle->NumVertex);
	normals->reserve(Triangle->NumVertex);
    tangents->reserve(Triangle->NumVertex);
	bitangents->reserve(Triangle->NumVertex);
    texCoords->reserve(Triangle->NumVertex);

	{
		vertices->push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords->push_back(glm::vec2(0.0f, 0.0f));

		vertices->push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords->push_back(glm::vec2(1.0f, 0.0f));

		vertices->push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords->push_back(glm::vec2(1.0f, 1.0f));
	}

	glGenVertexArrays(1, &Triangle->VAO);
	glBindVertexArray(Triangle->VAO);

	glGenBuffers(1, &Triangle->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Triangle->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), normals->data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &Triangle->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), tangents->data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &Triangle->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), bitangents->data(), GL_STATIC_DRAW);
	
	glGenBuffers(1, &Triangle->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices->size(), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.push_back(*Triangle);
	return model;
}