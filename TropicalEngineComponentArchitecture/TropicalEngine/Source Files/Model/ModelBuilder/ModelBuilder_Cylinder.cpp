#include <gl\glew.h>
#include <glm.hpp>
#include <gtc\constants.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model\Model.h"
#include "Model\ModelBuilder.h"

#include <QtCore\qdebug.h>

Model* ModelBuilder::CreateCylinder(QString name, float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = (subdivisionsAxis * subdivisionsHeight * 6) + (subdivisionsAxis * 6);

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

	for (int i = 0; i < subdivisionsHeight; i++)	//Tangents bitangents fix for sides
	{
		for (int j = 0; j < subdivisionsAxis; j++)
		{
			//Side
			vertices->push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + ((i * height) / subdivisionsHeight),
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + ((i * height) / subdivisionsHeight),
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));

			normals->push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
			normals->push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
			normals->push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));

			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			
			tangents->push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
			tangents->push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
			tangents->push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));

			texCoords->push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));
			texCoords->push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
			texCoords->push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));

			vertices->push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + ((i * height) / subdivisionsHeight),
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));

			normals->push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
			normals->push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
			normals->push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));

			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			
			tangents->push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
			tangents->push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
			tangents->push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));

			texCoords->push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
			texCoords->push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));
			texCoords->push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
		}
	}

	for (int j = -1; j < subdivisionsAxis - 1; j++)
	{
			//Top
			vertices->push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * 0.5f,
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				0.0f,
				height * 0.5f,
				0.0f,
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * 0.5f,
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));

			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));

			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));

			texCoords->push_back(glm::vec2(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords->push_back(glm::vec2(0.5f, 0.5f));
			texCoords->push_back(glm::vec2(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));

			//Bottom
			vertices->push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * (-0.5f),
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * (-0.5f),
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
			));
			vertices->push_back(glm::vec4(
				0.0f,
				height * (-0.5f),
				0.0f,
				1.0f
			));

			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));

			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));

			texCoords->push_back(glm::vec2(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords->push_back(glm::vec2(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords->push_back(glm::vec2(0.5f, 0.5f));
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

	Model* model = new Model(name);
	model->meshes.append(*Mesh);
	return model;
}