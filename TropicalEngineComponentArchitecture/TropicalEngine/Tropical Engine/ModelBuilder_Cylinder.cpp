#include <gl\glew.h>
#include <gtc\constants.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreateCylinder(QString name, float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	MeshEntry* Cylinder = new MeshEntry();

	Cylinder->NumVertex = subdivisionsAxis * subdivisionsHeight * 12;
	//Cylinder->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();
	//QVector<unsigned int>* indices = new vector<unsigned int>();

	vertices->reserve(4 * Cylinder->NumVertex);
	normals->reserve(3 * Cylinder->NumVertex);
    tangents->reserve(3 * Cylinder->NumVertex);
	bitangents->reserve(3 * Cylinder->NumVertex);
    texCoords->reserve(2 * Cylinder->NumVertex);

	//glm::pi

	for(int i = -1; i < subdivisionsHeight - 1; i++)	//Tangents bitangents fix for sides
	{
		for(int j = -1; j < subdivisionsAxis - 1; j++)
		{
			//Side

			vertices->push_back(radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));
			normals->push_back(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));
			normals->push_back(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));

			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));

			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			vertices->push_back(radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));
			normals->push_back(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));
			normals->push_back(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));

			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));

			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
			texCoords->push_back((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
			texCoords->push_back((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			//Top
			vertices->push_back(radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * 0.5f);
			vertices->push_back(radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(0.0f);vertices->push_back(height * 0.5f);
			vertices->push_back(0.0f);vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * 0.5f);
			vertices->push_back(radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);

			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);

			texCoords->push_back(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(0.5f);texCoords->push_back(0.5f);
			texCoords->push_back(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);

			//Bottom
			vertices->push_back(radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * (-0.5f));
			vertices->push_back(radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * (-0.5f));
			vertices->push_back(radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(0.0f);vertices->push_back(height * (-0.5f));
			vertices->push_back(0.0f);vertices->push_back(1.0f);

			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);

			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);

			texCoords->push_back(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(0.5f);texCoords->push_back(0.5f);
		}
	}

	glGenVertexArrays(1, &Cylinder->VAO);
	glBindVertexArray(Cylinder->VAO);

	glGenBuffers(1, &Cylinder->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinder->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cylinder->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinder->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cylinder->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinder->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cylinder->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinder->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cylinder->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cylinder->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.append(*Cylinder);
	return model;
}