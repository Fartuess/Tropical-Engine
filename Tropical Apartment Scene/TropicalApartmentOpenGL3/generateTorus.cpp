#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>

GLUSshape* ModelGenerator::generateTorus(float radius, float segmentRadius, int subdivisionsAxis, int subdivisionsHeight)
{
	GLUSshape* Torus = new GLUSshape();

	Torus->numberVertices = subdivisionsAxis * subdivisionsHeight;
	Torus->numberIndices = subdivisionsAxis * subdivisionsHeight;

	vector<float>* vertices = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* texCoords = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();

	Torus->vertices = (GLUSfloat*) malloc(4 * Torus->numberVertices * sizeof(GLUSfloat));
    Torus->normals = (GLUSfloat*) malloc(3 * Torus->numberVertices * sizeof(GLUSfloat));
	Torus->texCoords = (GLUSfloat*) malloc(2 * Torus->numberVertices * sizeof(GLUSfloat));
    Torus->indices = (GLUSuint*) malloc(Torus->numberIndices * sizeof(GLUSuint));

	Torus->vertices = vertices->data();
	Torus->normals = normals->data();
	Torus->texCoords = texCoords->data();
	Torus->indices = indices->data();
	
	Torus->mode = GL_TRIANGLES;
	return Torus;
}