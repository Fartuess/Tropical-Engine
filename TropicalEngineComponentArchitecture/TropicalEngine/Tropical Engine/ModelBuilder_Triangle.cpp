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
	//Triangle->numberIndices = 3;

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();

	Triangle->testVertices = new QVector<glm::vec3>();
	
	//float verticies_l[] = {	0.0f, 0.0f, 0.0f, 1.0f,
	//						1.0f, 0.0f, 0.0f, 1.0f,
	//						1.0f, 1.0f, 0.0f, 1.0f};
	//float normals_l[] = {	0.0f, 1.0f, 0.0f,
	//						0.0f, 1.0f, 0.0f,
	//						0.0f, 1.0f, 0.0f};
	//float tangents_l[] = {	1.0f, 0.0f, 0.0f,
	//						1.0f, 0.0f, 0.0f,
	//						1.0f, 0.0f, 0.0f};
	//float bitangents_l[] = {0.0f, 0.0f, 1.0f,
	//						0.0f, 0.0f, 1.0f,
	//						0.0f, 0.0f, 1.0f};
	//float texCoords_l[] = {	0.0f, 0.0f,
	//						1.0f, 0.0f,
	//						1.0f, 1.0f};
	//unsigned int indices_l[] = {0, 1, 2};
	


	vertices->reserve(4 * Triangle->NumVertex);
	normals->reserve(3 * Triangle->NumVertex);
    tangents->reserve(3 * Triangle->NumVertex);
	bitangents->reserve(3 * Triangle->NumVertex);
    texCoords->reserve(2 * Triangle->NumVertex);

	Triangle->testVertices->reserve(4 * Triangle->NumVertex);
	{
		vertices->push_back(0.0f); vertices->push_back(0.0f); vertices->push_back(0.0f); vertices->push_back(1.0f);
		normals->push_back(0.0f); normals->push_back(1.0f); normals->push_back(0.0f);
		tangents->push_back(1.0f); tangents->push_back(0.0f); tangents->push_back(0.0f);
		bitangents->push_back(0.0f); bitangents->push_back(0.0f); bitangents->push_back(1.0f);
		texCoords->push_back(0.0f); texCoords->push_back(0.0f);

		vertices->push_back(1.0f); vertices->push_back(0.0f); vertices->push_back(0.0f); vertices->push_back(1.0f);
		normals->push_back(0.0f); normals->push_back(1.0f); normals->push_back(0.0f);
		tangents->push_back(1.0f); tangents->push_back(0.0f); tangents->push_back(0.0f);
		bitangents->push_back(0.0f); bitangents->push_back(0.0f); bitangents->push_back(1.0f);
		texCoords->push_back(1.0f); texCoords->push_back(0.0f);

		vertices->push_back(1.0f); vertices->push_back(1.0f); vertices->push_back(0.0f); vertices->push_back(1.0f);
		normals->push_back(0.0f); normals->push_back(1.0f); normals->push_back(0.0f);
		tangents->push_back(1.0f); tangents->push_back(0.0f); tangents->push_back(0.0f);
		bitangents->push_back(0.0f); bitangents->push_back(0.0f); bitangents->push_back(1.0f);
		texCoords->push_back(1.0f); texCoords->push_back(1.0f);

		Triangle->testVertices->push_back(glm::vec3(0.0f, 0.0f, 0.0f));// Triangle->testVertices->push_back(1.0f);
		Triangle->testVertices->push_back(glm::vec3(1.0f, 0.0f, 0.0f));// Triangle->testVertices->push_back(1.0f);
		Triangle->testVertices->push_back(glm::vec3(1.0f, 1.0f, 0.0f));// Triangle->testVertices->push_back(1.0f);
	}

	glGenVertexArrays(1, &Triangle->VAO);
	glBindVertexArray(Triangle->VAO);

	glGenBuffers(1, &Triangle->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Triangle->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Triangle->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Triangle->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Triangle->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Triangle->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.push_back(*Triangle);
	//Triangle->testVertices[0];
	//Triangle->testVertices = &QVector<GLfloat>(*vertices);
	//Triangle->testVertices->data();
	Triangle->testVertices->count();
	return model;
}