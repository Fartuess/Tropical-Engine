#include <gl/glew.h>
#include <glm.hpp>
#include <QtCore/qvector.h>
#include <QtCore/qstring.h>
#include "Model/Model.h"
#include "Model/ModelBuilder.h"

Model* ModelBuilder::CreateTriangle(QString name)
{
	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = 3;

	QVector<glm::vec4>* vertices = new QVector<glm::vec4>();
	QVector<glm::vec3>* normals = new QVector<glm::vec3>();
	QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
	QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
	QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();

	vertices->reserve(Mesh->NumVertex);
	normals->reserve(Mesh->NumVertex);
    tangents->reserve(Mesh->NumVertex);
	bitangents->reserve(Mesh->NumVertex);
    texCoords->reserve(Mesh->NumVertex);

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

	glGenVertexArrays(1, &Mesh->vertexVBO);
	glBindVertexArray(Mesh->vertexVBO);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec2) * vertices->size(), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		sizeof(glm::vec4) * vertices->size(), vertices->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), normals->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), tangents->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), bitangents->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec2) * vertices->size(), texCoords->data());
	
	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}