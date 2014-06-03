#include <gl\glew.h>
#include <gtc\constants.hpp>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreateCone(QString name, float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	MeshEntry* Cone = new MeshEntry();

	Cone->NumVertex = subdivisionsAxis * subdivisionsHeight * 9;
	//Cone->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	QVector<float>* vertices = new QVector<float>();
	QVector<float>* normals = new QVector<float>();
	QVector<float>* tangents = new QVector<float>();
	QVector<float>* bitangents = new QVector<float>();
	QVector<float>* texCoords = new QVector<float>();
	//QVector<unsigned int>* indices = new QVector<unsigned int>();

	vertices->reserve(4 * Cone->NumVertex);
	normals->reserve(3 * Cone->NumVertex);
    tangents->reserve(3 * Cone->NumVertex);
	bitangents->reserve(3 * Cone->NumVertex);
    texCoords->reserve(2 * Cone->NumVertex);

	for(int i = -1; i < subdivisionsHeight - 1; i++)
	{
		float h = radius * (1 - ((float)(i + 1) / subdivisionsHeight));
		float h2 = radius * (1 - ((float)(i + 2) / subdivisionsHeight));
		//one loop
		for(int j = -1; j <subdivisionsAxis - 1; j++)
		{
			vertices->push_back(h * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h2 * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);

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

			vertices->push_back(h2 * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h2 * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)));vertices->push_back(1.0f);

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

	glGenVertexArrays(1, &Cone->VAO);
	glBindVertexArray(Cone->VAO);

	glGenBuffers(1, &Cone->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cone->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cone->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cone->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cone->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cone->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cone->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cone->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cone->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cone->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model();
	model->meshes.append(*Cone);
	return model;
}