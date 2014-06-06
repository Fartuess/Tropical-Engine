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

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();

	//vector<unsigned int>* indices = new vector<unsigned int>();

	vertices->reserve(4 * Cube->NumVertex);
	normals->reserve(3 * Cube->NumVertex);
    tangents->reserve(3 * Cube->NumVertex);
	bitangents->reserve(3 * Cube->NumVertex);
    texCoords->reserve(2 * Cube->NumVertex);

	for(int j = -1; j < subdivisionsZ - 1; j++)	//Top Face
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);
		}
	}

	for(int j = -1; j < subdivisionsZ - 1; j++)	//Bottom Face
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);
			
			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(-0.5f * sizeY);vertices->push_back((-0.5f + j + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(-1.0f);normals->push_back(0.0f);
			tangents->push_back(-1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(-1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeZ / subdivisionsZ);
		}
	}
	
	for(int j = - 1; j < subdivisionsY - 1; j++)	//Front Face
	{
		for(int i = - 1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(1.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			bitangents->push_back(1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Back Face
	{
		for(int i = - 1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);
			
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(-0.5f * sizeZ);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(0.0f);normals->push_back(-1.0f);
			tangents->push_back(0.0f);tangents->push_back(-1.0f);tangents->push_back(0.0f);
			bitangents->push_back(-1.0f);bitangents->push_back(0.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Left Face
	{
		for(int i = - 1; i < subdivisionsZ - 1; i++)
		{
			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);
			
			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back(-0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(-1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(-1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(-1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}

	for(int j = - 1; j < subdivisionsY - 1; j++)	//Right Face
	{
		for(int i = - 1; i < subdivisionsZ - 1; i++)
		{
			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);
			
			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back(i * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back(0.5f * sizeX);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back((-0.5f + i + 1) * sizeZ / subdivisionsZ);vertices->push_back(1.0f);
			normals->push_back(1.0f);normals->push_back(0.0f);normals->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(0.0f);tangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(1.0f);bitangents->push_back(0.0f);
			texCoords->push_back((i + 1) * sizeZ / subdivisionsZ);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}
	
	glGenVertexArrays(1, &Cube->VAO);
	glBindVertexArray(Cube->VAO);

	glGenBuffers(1, &Cube->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cube->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cube->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cube->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Cube->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Cube->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

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