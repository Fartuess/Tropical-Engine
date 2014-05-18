#include "ModelGeneration_header.h"
#include <vector>
#include <GL\glus.h>

GLUSshape* ModelGenerator::generateTriangle()
{
	GLUSshape* Triangle = new GLUSshape();

	Triangle->numberVertices = 3;
	Triangle->numberIndices = 3;

	
	float verticies_l[] = {	0.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 1.0f, 0.0f, 1.0f};
	float normals_l[] = {	0.0f, 1.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
							0.0f, 1.0f, 0.0f};
	float tangents_l[] = {	1.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 0.0f,
							1.0f, 0.0f, 0.0f};
	float bitangents_l[] = {0.0f, 0.0f, 1.0f,
							0.0f, 0.0f, 1.0f,
							0.0f, 0.0f, 1.0f};
	float texCoords_l[] = {	0.0f, 0.0f,
							1.0f, 0.0f,
							1.0f, 1.0f};
	unsigned int indices_l[] = {0, 1, 2};
	


	vector<float>* verticies = new vector<float>();
	vector<float>* normals = new vector<float>();
	vector<float>* tangents = new vector<float>();
	vector<float>* bitangents = new vector<float>();
	vector<float>* texCoords = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();

	Triangle->vertices = (GLUSfloat*) malloc(4 * Triangle->numberVertices * sizeof(GLUSfloat));
    Triangle->normals = (GLUSfloat*) malloc(3 * Triangle->numberVertices * sizeof(GLUSfloat));
    Triangle->tangents = (GLUSfloat*) malloc(3 * Triangle->numberVertices * sizeof(GLUSfloat));
	Triangle->bitangents = (GLUSfloat*) malloc(3 * Triangle->numberVertices * sizeof(GLUSfloat));
    Triangle->texCoords = (GLUSfloat*) malloc(2 * Triangle->numberVertices * sizeof(GLUSfloat));
    Triangle->indices = (GLUSuint*) malloc(Triangle->numberIndices * sizeof(GLUSuint));

	{
		verticies->assign(verticies_l, verticies_l + 12);
		normals->assign(normals_l, normals_l + 9);
		tangents->assign(tangents_l, tangents_l + 9);
		bitangents->assign(bitangents_l, bitangents_l + 9);
		texCoords->assign(texCoords_l, texCoords_l + 9);
		indices->assign(indices_l, indices_l + 3);
	}

	Triangle->vertices = verticies->data();
	Triangle->normals = normals->data();
	Triangle->tangents = tangents->data();
	Triangle->bitangents = bitangents->data();
	Triangle->texCoords = texCoords->data();
	Triangle->indices = indices->data();

	GLUSint stride = 4 + 3 + 3 + 3 + 2;
	Triangle->allAttributes = (GLUSfloat*) malloc(stride * Triangle->numberVertices * sizeof(GLUSfloat));

	//is it even required?
	for (int i = 0; i < Triangle->numberVertices; i++)
    {
        Triangle->allAttributes[i * stride + 0] = Triangle->vertices[i * 4 + 0];
        Triangle->allAttributes[i * stride + 1] = Triangle->vertices[i * 4 + 1];
        Triangle->allAttributes[i * stride + 2] = Triangle->vertices[i * 4 + 2];
        Triangle->allAttributes[i * stride + 3] = Triangle->vertices[i * 4 + 3];

        Triangle->allAttributes[i * stride + 4] = Triangle->normals[i * 3 + 0];
        Triangle->allAttributes[i * stride + 5] = Triangle->normals[i * 3 + 1];
        Triangle->allAttributes[i * stride + 6] = Triangle->normals[i * 3 + 2];

        Triangle->allAttributes[i * stride + 7] = Triangle->tangents[i * 3 + 0];
        Triangle->allAttributes[i * stride + 8] = Triangle->tangents[i * 3 + 1];
        Triangle->allAttributes[i * stride + 9] = Triangle->tangents[i * 3 + 2];
		
        Triangle->allAttributes[i * stride + 10] = Triangle->bitangents[i * 3 + 0];
        Triangle->allAttributes[i * stride + 11] = Triangle->bitangents[i * 3 + 1];
        Triangle->allAttributes[i * stride + 12] = Triangle->bitangents[i * 3 + 2];

        Triangle->allAttributes[i * stride + 13] = Triangle->texCoords[i * 2 + 0];
        Triangle->allAttributes[i * stride + 14] = Triangle->texCoords[i * 2 + 1];
    }

	Triangle->mode = GL_TRIANGLES;
	return Triangle;
}