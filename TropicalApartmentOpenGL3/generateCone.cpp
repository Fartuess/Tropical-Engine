#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>
#define _USE_MATH_DEFINES
#include <math.h>

GLUSshape*  ModelGenerator::generateCone(float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	GLUSshape* Cone = new GLUSshape();

	Cone->numberVertices = subdivisionsAxis * subdivisionsHeight * 9;
	Cone->numberIndices = subdivisionsAxis * (subdivisionsHeight * 1);

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();

	Cone->vertices = (GLUSfloat*) malloc(4 * Cone->numberVertices * sizeof(GLUSfloat));
    Cone->normals = (GLUSfloat*) malloc(3 * Cone->numberVertices * sizeof(GLUSfloat));
	Cone->tangents = (GLUSfloat*) malloc(3 * Cone->numberVertices * sizeof(GLUSfloat));
	Cone->bitangents = (GLUSfloat*) malloc(3 * Cone->numberVertices * sizeof(GLUSfloat));
	Cone->texCoords = (GLUSfloat*) malloc(2 * Cone->numberVertices * sizeof(GLUSfloat));
    Cone->indices = (GLUSuint*) malloc(Cone->numberIndices * sizeof(GLUSuint));

	for(int i = -1; i < subdivisionsHeight - 1; i++)
	{
		float h = radius * (1 - ((float)(i + 1) / subdivisionsHeight));
		float h2 = radius * (1 - ((float)(i + 2) / subdivisionsHeight));
		//one loop
		for(int j = -1; j <subdivisionsAxis - 1; j++)
		{
			vertices->push_back(h * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h2 * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);

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

			vertices->push_back(h2 * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h * cosf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i) / subdivisionsHeight));
			vertices->push_back(h * sinf((j + 1) * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);
			vertices->push_back(h2 * cosf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(height * ((-0.5f + i + 1) / subdivisionsHeight));
			vertices->push_back(h2 * sinf(j * (2 * M_PI / subdivisionsAxis)));vertices->push_back(1.0f);

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

	Cone->vertices = vertices->data();
	Cone->normals = normals->data();
	Cone->tangents = tangents->data();
	Cone->bitangents = bitangents->data();
	Cone->texCoords = texCoords->data();
	Cone->indices = indices->data();
	
	Cone->mode = GL_TRIANGLES;
	return Cone;
}