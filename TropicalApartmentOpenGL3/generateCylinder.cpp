#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLUSshape*  ModelGenerator::generateCylinder(float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	GLUSshape* Cylinder = new GLUSshape();

	Cylinder->numberVertices = subdivisionsAxis * subdivisionsHeight * 12;
	Cylinder->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();

	Cylinder->vertices = (GLUSfloat*) malloc(4 * Cylinder->numberVertices * sizeof(GLUSfloat));
    Cylinder->normals = (GLUSfloat*) malloc(3 * Cylinder->numberVertices * sizeof(GLUSfloat));
	Cylinder->tangents = (GLUSfloat*) malloc(3 * Cylinder->numberVertices * sizeof(GLUSfloat));
	Cylinder->bitangents = (GLUSfloat*) malloc(3 * Cylinder->numberVertices * sizeof(GLUSfloat));
	Cylinder->texCoords = (GLUSfloat*) malloc(2 * Cylinder->numberVertices * sizeof(GLUSfloat));
    Cylinder->indices = (GLUSuint*) malloc(Cylinder->numberIndices * sizeof(GLUSuint));

	for(int i = -1; i < subdivisionsHeight - 1; i++)	//Tangents bitangents fix for sides
	{
		for(int j = -1; j < subdivisionsAxis - 1; j++)
		{
			//Side

			vertices->push_back(radius * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)));
			normals->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)));
			normals->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));

			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));

			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));

			vertices->push_back(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(radius * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
			normals->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));
			normals->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)));normals->push_back(0.0f);normals->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)));

			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			tangents->push_back(0.0f);tangents->push_back(1.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf((j + 1) * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf((j + 1) * (2 / subdivisionsAxis)));
			bitangents->push_back(sinf(j * (2 / subdivisionsAxis)));bitangents->push_back(0.0f);bitangents->push_back(cosf(j * (2 / subdivisionsAxis)));

			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));
			texCoords->push_back((float)((j + 1) * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)i / subdivisionsHeight));
			texCoords->push_back((float)(j * 2 * M_PI * radius / subdivisionsAxis));texCoords->push_back(((float)(i + 1) / subdivisionsHeight));

			//Top
			vertices->push_back(radius * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * 0.5f);
			vertices->push_back(radius * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(0.0f);vertices->push_back(height * 0.5f);
			vertices->push_back(0.0f);vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * 0.5f);
			vertices->push_back(radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);

			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);

			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);

			texCoords->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(0.5f);texCoords->push_back(0.5f);
			texCoords->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);

			//Bottom
			vertices->push_back(radius * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * (-0.5f));
			vertices->push_back(radius * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(radius * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * (-0.5f));
			vertices->push_back(radius * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
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

			texCoords->push_back(cosf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf(j * (2 * M_PI / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(cosf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);texCoords->push_back(sinf((j + 1) * (2 * M_PI / subdivisionsAxis)) + 0.5f);
			texCoords->push_back(0.5f);texCoords->push_back(0.5f);
		}
	}

	Cylinder->vertices = vertices->data();
	Cylinder->normals = normals->data();
	Cylinder->tangents = tangents->data();
	Cylinder->bitangents = bitangents->data();
	Cylinder->texCoords = texCoords->data();
	Cylinder->indices = indices->data();

	//glusCalculateTangentSpacef(Cylinder);
	
	Cylinder->mode = GL_TRIANGLES;
	return Cylinder;
}