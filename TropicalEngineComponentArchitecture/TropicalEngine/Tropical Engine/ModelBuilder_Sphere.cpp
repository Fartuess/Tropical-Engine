#include <gl\glew.h>
#include <gtc\constants.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreateSphere(QString name, float radius, int subdivisionsAxis, int subdivisionsHeight)
{
	MeshEntry* Sphere = new MeshEntry();

	Sphere->NumVertex = subdivisionsAxis * subdivisionsHeight * 6;
	//Sphere->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();
	//vector<unsigned int>* indices = new vector<unsigned int>();

	vertices->reserve(4 * Sphere->NumVertex);
	normals->reserve(3 * Sphere->NumVertex);
    tangents->reserve(3 * Sphere->NumVertex);
	bitangents->reserve(3 * Sphere->NumVertex);
    texCoords->reserve(2 * Sphere->NumVertex);

	for(int i = 0; i < subdivisionsHeight; i++)
	{
		for(int j = 0; j < subdivisionsAxis; j++)
		{
			//
			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			//
			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis));
			normals->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (glm::pi<float>() / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * glm::pi<float>() / subdivisionsAxis));
			bitangents->push_back(cosf(i * (glm::pi<float>() / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
		}
	}

	glGenVertexArrays(1, &Sphere->VAO);
	glBindVertexArray(Sphere->VAO);

	glGenBuffers(1, &Sphere->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Sphere->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Sphere->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Sphere->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Sphere->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Sphere->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.append(*Sphere);
	return model;
}