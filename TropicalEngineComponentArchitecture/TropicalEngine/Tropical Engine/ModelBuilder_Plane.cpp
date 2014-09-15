#include <gl\glew.h>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreatePlane(QString name, float sizeX, float sizeY, int subdivisionsX, int subdivisionsY)
{
	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = subdivisionsX * subdivisionsY * 6;

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

	for(int j = 0; j < subdivisionsY; j++)
	{
		for(int i = 0; i < subdivisionsX; i++)
		{
			vertices->push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
		}
	}

	glGenBuffers(1, &Mesh->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh->vertexVBO);

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

	glEnableVertexAttribArray(0); 
	glBindVertexArray(0);

	Model* model = new Model(name);
	model->meshes.append(*Mesh);
	return model;
}