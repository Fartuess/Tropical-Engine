#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>

GLUSshape* ModelGenerator::generateCube(float sizeX, float sizeY, float sizeZ, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	GLUSshape* Cube = new GLUSshape();

	Cube->numberVertices = subdivisionsX * subdivisionsY * 6 * 6;
	Cube->numberIndices = (subdivisionsY - 1) * subdivisionsX * 2
		+ subdivisionsY * (subdivisionsX - 1) * 2
		+ (subdivisionsZ - 1) * subdivisionsY * 2
		+ subdivisionsZ * (subdivisionsY - 1) * 2
		+ (subdivisionsZ - 1) * subdivisionsX * 2
		+ subdivisionsZ * (subdivisionsX - 1) * 2;

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();

	vector<unsigned int>* indices = new vector<unsigned int>();

	Cube->vertices = (GLUSfloat*) malloc(4 * Cube->numberVertices * sizeof(GLUSfloat));
    Cube->normals = (GLUSfloat*) malloc(3 * Cube->numberVertices * sizeof(GLUSfloat));
    Cube->tangents = (GLUSfloat*) malloc(3 * Cube->numberVertices * sizeof(GLUSfloat));
	Cube->bitangents = (GLUSfloat*) malloc(3 * Cube->numberVertices * sizeof(GLUSfloat));
    Cube->texCoords = (GLUSfloat*) malloc(2 * Cube->numberVertices * sizeof(GLUSfloat));
    Cube->indices = (GLUSuint*) malloc(Cube->numberIndices * sizeof(GLUSuint));

	/*
	//VBO generation	Maybe should be done totally differently
	{
		//front
		for(int j = 0; j < subdivisionsY + 1; j++)
		{
			for(int i = 0; i < subdivisionsX + 1; i++)
			{
				vertices->push_back(-0.5f * sizeX + i * sizeX / subdivisionsX);
				vertices->push_back(-0.5f * sizeY + j * sizeY / subdivisionsY);
				vertices->push_back(0.5f * sizeZ);
				vertices->push_back(0.0f);

				normals->push_back(0.0f);
				normals->push_back(0.0f);
				normals->push_back(1.0f);

				texCoords->push_back(i * sizeX / subdivisionsX);
				texCoords->push_back(j * sizeY / subdivisionsY);
			}
		}
		//middle
		for(int z = 1; z < subdivisionsZ - 1; z++)
		{
			//top line
			for(int x = 0; x < subdivisionsX + 1; x++)
			{
				vertices->push_back(-0.5f * sizeX + x * sizeX / subdivisionsX);
				vertices->push_back(0.5f * sizeY);
				vertices->push_back(0.5f * sizeZ - z * sizeZ / subdivisionsZ);
				vertices->push_back(0.0f);

				normals->push_back(0.0f);
				normals->push_back(0.0f);
				normals->push_back(1.0f);

				texCoords->push_back(x * sizeX / subdivisionsX);
				texCoords->push_back(z * sizeY / subdivisionsY);
			}
			//middle
			for(;;)
			{

			}
			//bottom line
			for(;;)
			{

			}
		}
		//back
		for(int j = 0; j < subdivisionsY + 1; j++)
		{
			for(int i = 0; i < subdivisionsX + 1; i++)
			{
				vertices->push_back(-0.5f * sizeX + i * sizeX / subdivisionsX);
				vertices->push_back(-0.5f * sizeY + j * sizeY / subdivisionsY);
				vertices->push_back(-0.5f * sizeZ);
				vertices->push_back(0.0f);

				normals->push_back(0.0f);
				normals->push_back(0.0f);
				normals->push_back(1.0f);

				texCoords->push_back(i * sizeX / subdivisionsX);
				texCoords->push_back(j * sizeY / subdivisionsY);
			}
		}
	}
	*/

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
	

	Cube->vertices = vertices->data();
	Cube->normals = normals->data();
	Cube->tangents = tangents->data();
	Cube->bitangents = bitangents->data();
	Cube->texCoords = texCoords->data();
	Cube->indices = indices->data();
	
	Cube->mode = GL_TRIANGLES;
	return Cube;
}

GLUSshape* ModelGenerator::generateCube(Vec3 size, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	return generateCube(size.x, size.y, size.y, subdivisionsX, subdivisionsY, subdivisionsZ);
}

GLUSshape* ModelGenerator::generateCube(Vec3 size, Vec3 subdivisions)
{
	return generateCube(size.x, size.y, size.y, subdivisions.x, subdivisions.y, subdivisions.z);
}