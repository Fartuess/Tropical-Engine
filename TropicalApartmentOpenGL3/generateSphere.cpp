#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLUSshape* ModelGenerator::generateSphere(float radius, int subdivisionsAxis, int subdivisionsHeight)
{
	GLUSshape* Sphere = new GLUSshape();

	Sphere->numberVertices = subdivisionsAxis * subdivisionsHeight * 6;
	Sphere->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();

	Sphere->vertices = (GLUSfloat*) malloc(4 * Sphere->numberVertices * sizeof(GLUSfloat));
    Sphere->normals = (GLUSfloat*) malloc(3 * Sphere->numberVertices * sizeof(GLUSfloat));
	Sphere->tangents = (GLUSfloat*) malloc(3 * Sphere->numberVertices * sizeof(GLUSfloat));
	Sphere->bitangents = (GLUSfloat*) malloc(3 * Sphere->numberVertices * sizeof(GLUSfloat));
	Sphere->texCoords = (GLUSfloat*) malloc(2 * Sphere->numberVertices * sizeof(GLUSfloat));
    Sphere->indices = (GLUSuint*) malloc(Sphere->numberIndices * sizeof(GLUSuint));

	for(int i = 0; i < subdivisionsHeight; i++)
	{
		for(int j = 0; j < subdivisionsAxis; j++)
		{
			//
			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			//
			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(j * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf(j * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf((i + 1) * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf(((i + 1) + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf((i + 1) * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf((i + 1) * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			vertices->push_back(radius * cosf(i * (M_PI / subdivisionsHeight)));
			vertices->push_back(1.0f);

			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis));
			normals->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			normals->push_back(1.0f);

			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * cosf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(sinf((i + 0.5f) * (M_PI / subdivisionsHeight) * sinf((j + 1) * 2 * M_PI / subdivisionsAxis)));
			tangents->push_back(cosf((i + 0.5f) * (M_PI / subdivisionsHeight)));
			tangents->push_back(1.0f);

			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * cosf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(sinf(i * (M_PI / subdivisionsHeight)) * sinf(((j + 1) + 0.25f) * 2 * M_PI / subdivisionsAxis));
			bitangents->push_back(cosf(i * (M_PI / subdivisionsHeight)));
			bitangents->push_back(1.0f);

			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
		}
	}

	Sphere->vertices = vertices->data();
	Sphere->normals = normals->data();
	Sphere->tangents = tangents->data();
	Sphere->bitangents = bitangents->data();
	Sphere->texCoords = texCoords->data();
	Sphere->indices = indices->data();
	
	Sphere->mode = GL_TRIANGLES;
	return Sphere;
}