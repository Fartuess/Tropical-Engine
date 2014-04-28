#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>

GLUSshape* ModelGenerator::generatePlane(float sizeX = 1.0f, float sizeY = 1.0f, int subdivisionsX = 1, int subdivisionsY = 1)
{
	GLUSshape* Plane = new GLUSshape();

	Plane->numberVertices = subdivisionsX * subdivisionsY * 6;
	Plane->numberIndices = ((subdivisionsX + 1) * subdivisionsY + subdivisionsX * (subdivisionsY + 1) + subdivisionsX * subdivisionsY) * 2;	// *2 for both triangles in quad

	//vector<Vec4>* vertices = new vector<Vec4>();

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();

	//vector<Vec3>* normals = new vector<Vec3>();
	//vector<Vec3>* tangents = new vector<Vec3>();
	//vector<Vec3>* bitangents = new vector<Vec3>();
	//vector<Vec2>* texCoords = new vector<Vec2>();

	vector<unsigned int>* indices = new vector<unsigned int>();

	Plane->vertices = (GLUSfloat*) malloc(4 * Plane->numberVertices * sizeof(GLUSfloat));
    Plane->normals = (GLUSfloat*) malloc(3 * Plane->numberVertices * sizeof(GLUSfloat));
    Plane->tangents = (GLUSfloat*) malloc(3 * Plane->numberVertices * sizeof(GLUSfloat));
	Plane->bitangents = (GLUSfloat*) malloc(3 * Plane->numberVertices * sizeof(GLUSfloat));
    Plane->texCoords = (GLUSfloat*) malloc(2 * Plane->numberVertices * sizeof(GLUSfloat));
    Plane->indices = (GLUSuint*) malloc(Plane->numberIndices * sizeof(GLUSuint));

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

	////vertices
	//for(int j = 0; j < subdivisionsY + 1; j++)
	//{
	//	for(int i = 0; i < subdivisionsX + 1; i++)
	//	{
	//		//vertices->push_back(*(new Vec4(-0.5f * sizeX + i * sizeX / subdivisionsX, 0,  -0.5f * sizeY + j * sizeY / subdivisionsY, 0)));
	//		vertices->push_back(-0.5f * sizeX + i * sizeX / subdivisionsX);
	//		vertices->push_back(0.0f);
	//		vertices->push_back(-0.5f * sizeY + j * sizeY / subdivisionsY);
	//		vertices->push_back(0.0f);
	//	}
	//}
	////normals
	//for(int j = 0; j < subdivisionsY + 1; j++)
	//{
	//	for(int i = 0; i < subdivisionsX + 1; i++)
	//	{
	//		normals->push_back(*(new Vec3(0.0f, 1.0f, 0.0f)));
	//	}
	//}
	////tangents
	//for(int j = 0; j < subdivisionsY + 1; j++)
	//{
	//	for(int i = 0; i < subdivisionsX + 1; i++)
	//	{
	//		tangents->push_back(*(new Vec3(1.0f, 0.0f, 0.0f)));
	//	}
	//}
	////bitangents
	//for(int j = 0; j < subdivisionsY + 1; j++)
	//{
	//	for(int i = 0; i < subdivisionsX + 1; i++)
	//	{
	//		tangents->push_back(*(new Vec3(0.0f, 0.0f, 1.0f)));
	//	}
	//}
	////texture coordinates
	//for(int j = 0; j < subdivisionsY + 1; j++)
	//{
	//	for(int i = 0; i < subdivisionsX + 1; i++)
	//	{
	//		texCoords->push_back(*(new Vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY)));
	//	}
	//}
	//indices
	for(int j = 1; j <= subdivisionsY; j++)
	{
		for(int i = 0; i <= subdivisionsX; i++)
		{
			//first triangle
			indices->push_back((j-1) * (subdivisionsX + 1) + i);
			indices->push_back((j-1) * (subdivisionsX + 1) + i + 1);
			indices->push_back((j) * (subdivisionsX + 1) + i);
			//second triangle
			indices->push_back((j-1) * (subdivisionsX + 1) + i + 1);
			indices->push_back((j) * (subdivisionsX + 1) + i + 1);
			indices->push_back((j) * (subdivisionsX + 1) + i);
		}
	}

	Plane->vertices = vertices->data();
	Plane->normals = normals->data();
	Plane->tangents = tangents->data();
	Plane->bitangents = bitangents->data();
	Plane->texCoords = texCoords->data();
	Plane->indices = indices->data();

	GLUSuint stride = 4 + 3 + 3 + 3 + 2;
	Plane->allAttributes = (GLUSfloat*) malloc(stride * Plane->numberVertices * sizeof(GLUSfloat));

	for (int i = 0; i < Plane->numberVertices; i++)
    {
        Plane->allAttributes[i * stride + 0] = Plane->vertices[i * 4 + 0];
        Plane->allAttributes[i * stride + 1] = Plane->vertices[i * 4 + 1];
        Plane->allAttributes[i * stride + 2] = Plane->vertices[i * 4 + 2];
        Plane->allAttributes[i * stride + 3] = Plane->vertices[i * 4 + 3];

        Plane->allAttributes[i * stride + 4] = Plane->normals[i * 3 + 0];
        Plane->allAttributes[i * stride + 5] = Plane->normals[i * 3 + 1];
        Plane->allAttributes[i * stride + 6] = Plane->normals[i * 3 + 2];

        Plane->allAttributes[i * stride + 7] = Plane->tangents[i * 3 + 0];
        Plane->allAttributes[i * stride + 8] = Plane->tangents[i * 3 + 1];
        Plane->allAttributes[i * stride + 9] = Plane->tangents[i * 3 + 2];

        Plane->allAttributes[i * stride + 10] = Plane->bitangents[i * 3 + 0];
        Plane->allAttributes[i * stride + 11] = Plane->bitangents[i * 3 + 1];
        Plane->allAttributes[i * stride + 12] = Plane->bitangents[i * 3 + 2];

        Plane->allAttributes[i * stride + 13] = Plane->texCoords[i * 2 + 0];
        Plane->allAttributes[i * stride + 14] = Plane->texCoords[i * 2 + 1];
    }

	Plane->mode = GL_TRIANGLES;
	return Plane;
}