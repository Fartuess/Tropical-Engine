#include <gl\glew.h>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

Model* ModelBuilder::CreateBox(QString name, float sizeX, float sizeY, float sizeZ, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	MeshEntry* Cube = new MeshEntry();

	Cube->NumVertex = subdivisionsX * subdivisionsY * 6 * 6;
	//Cube->numberIndices = (subdivisionsY - 1) * subdivisionsX * 2
	//	+ subdivisionsY * (subdivisionsX - 1) * 2
	//	+ (subdivisionsZ - 1) * subdivisionsY * 2
	//	+ subdivisionsZ * (subdivisionsY - 1) * 2
	//	+ (subdivisionsZ - 1) * subdivisionsX * 2
	//	+ subdivisionsZ * (subdivisionsX - 1) * 2;

	QVector<glm::vec4>* vertices = new QVector<glm::vec4>();
	QVector<glm::vec3>* normals = new QVector<glm::vec3>();
	QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
	QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
	QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();

	//vector<unsigned int>* indices = new vector<unsigned int>();

	vertices->reserve(Cube->NumVertex);
	normals->reserve(Cube->NumVertex);
    tangents->reserve(Cube->NumVertex);
	bitangents->reserve(Cube->NumVertex);
    texCoords->reserve(Cube->NumVertex);

	for(int j = -1; j < subdivisionsZ - 1; j++)	//Top Face
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2((i * sizeX / subdivisionsX), (j + 1) * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j * sizeZ / subdivisionsZ)));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));
		}
	}

	for(int j = -1; j < subdivisionsZ - 1; j++)	//Bottom Face
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));
			
			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				-0.5f * sizeY,
				(-0.5f + j + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			tangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			bitangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));
		}
	}
	
	for(int j = - 1; j < subdivisionsY - 1; j++)	//Front Face
	{
		for(int i = - 1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f ,1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			tangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			bitangents->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Back Face
	{
		for(int i = - 1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));
			
			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				(-0.5f + i + 1) * sizeX / subdivisionsX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				-0.5f * sizeZ,
				1.0f
			));
			normals->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			tangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			bitangents->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Left Face
	{
		for(int i = - 1; i < subdivisionsZ - 1; i++)
		{
			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));
			
			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				-0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents->push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Right Face
	{
		for(int i = - 1; i < subdivisionsZ - 1; i++)
		{
			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));
			
			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f ,0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f ,0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords->push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

			vertices->push_back(glm::vec4(
				0.5f * sizeX,
				(-0.5f + j + 1) * sizeY / subdivisionsY,
				(-0.5f + i + 1) * sizeZ / subdivisionsZ,
				1.0f
			));
			normals->push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents->push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			bitangents->push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			texCoords->push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));
		}
	}
	
	glGenVertexArrays(1, &Cube->VAO);
	glBindVertexArray(Cube->VAO);

	glGenBuffers(1, &Cube->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size(), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cube->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), normals->data(), GL_STATIC_DRAW);

	//glGenBuffers(1, &Cube->tangentVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Cube->tangentVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), tangents->data(), GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &Cube->bitangentVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Cube->bitangentVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), bitangents->data(), GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &Cube->texcoordVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Cube->texcoordVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices->size(), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model(name);
	model->meshes.append(*Cube);
	return model;
}

Model* ModelBuilder::CreateBox(QString name, glm::vec3 size, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	return CreateBox(name, size.x, size.y, size.z, subdivisionsX, subdivisionsY, subdivisionsZ);
}

Model* ModelBuilder::CreateBox(QString name, glm::vec3 size, glm::vec3 subdivisions)
{
	return CreateBox(name, size.x, size.y, size.z, subdivisions.x, subdivisions.y, subdivisions.z);
}