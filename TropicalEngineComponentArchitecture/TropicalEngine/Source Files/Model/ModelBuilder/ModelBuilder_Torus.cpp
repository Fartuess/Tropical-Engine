#include <gl/glew.h>
#include <gtc/constants.hpp>

#include <QtCore/qvector.h>
#include <QtCore/qstring.h>

#include <Model/Model.h>
#include <Model/ModelBuilder.h>

Model* ModelBuilder::CreateTorus(QString name, float radius, float segmentRadius, int subdivisionsAxis, int subdivisionsHeight)
{
	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = subdivisionsAxis * subdivisionsHeight * 6;

	QVector<glm::vec4>* vertices = new QVector<glm::vec4>();
	QVector<glm::vec3>* normals = new QVector<glm::vec3>();
	QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
	QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
	QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();

	vertices->reserve(Mesh->NumVertex);
	normals->reserve(Mesh->NumVertex);
    tangents->reserve(Mesh->NumVertex);
	bitangents->reserve(Mesh->NumVertex);
    texCoords->reserve(Mesh->NumVertex);

	for (int i = 0; i < subdivisionsHeight; i++)
	{
		for (int j = 0; j < subdivisionsAxis; j++)
		{
			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices->push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			//normals
			normals->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			//tangents
			bitangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));
			
			//bitangents
			tangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents->push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents->push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			//texcoords
			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));

			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));
		}
	}

	glGenBuffers(1, &Mesh->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh->vertexVBO);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec3) * vertices->size()
		+ sizeof(glm::vec2) * vertices->size(), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER,
		0,
		sizeof(glm::vec4) * vertices->size(), vertices->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), normals->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), tangents->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec3) * vertices->size(), bitangents->data());
	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
		sizeof(glm::vec2) * vertices->size(), texCoords->data());

	glEnableVertexAttribArray(0); 
	glBindVertexArray(0);

	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}