#include <gl\glew.h>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreatePlane(QString name, float sizeX, float sizeY, int subdivisionsX, int subdivisionsY)
{
	MeshEntry* Plane = new MeshEntry();

	Plane->NumVertex = subdivisionsX * subdivisionsY * 6;

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();

	vertices->reserve(4 * Plane->NumVertex);
	normals->reserve(3 * Plane->NumVertex);
    tangents->reserve(3 * Plane->NumVertex);
	bitangents->reserve(3 * Plane->NumVertex);
    texCoords->reserve(2 * Plane->NumVertex);

	for(int j = -1; j < subdivisionsY - 1; j++)
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}

	glGenVertexArrays(1, &Plane->VAO);
	glBindVertexArray(Plane->VAO);

	glGenBuffers(1, &Plane->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.append(*Plane);
	return model;
}