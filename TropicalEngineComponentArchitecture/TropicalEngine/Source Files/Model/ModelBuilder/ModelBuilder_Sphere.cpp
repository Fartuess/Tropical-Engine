#include <gl/glew.h>
#include <gtc/constants.hpp>

#include <QtCore/qvector.h>
#include <QtCore/qstring.h>

#include <Model/Model.h>
#include <Model/ModelBuilder.h>

Model* ModelBuilder::CreateSphere(QString name, float radius, int subdivisionsAxis, int subdivisionsHeight)
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
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)i / subdivisionsHeight
				));

			vertices->push_back(glm::vec4(
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
				));

			vertices->push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			vertices->push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)(i + 1) / subdivisionsHeight
			));

			vertices->push_back(glm::vec4(
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)i / subdivisionsHeight
			));

			vertices->push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
			));

			normals->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
			));

			bitangents->push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
			));

			tangents->push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
			));

			texCoords->push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)(i + 1) / subdivisionsHeight
			));
		}
	}

	//glGenVertexArrays(1, &Sphere->VAO);
	//glBindVertexArray(Sphere->VAO);

	//glGenBuffers(1, &Sphere->vertexVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->vertexVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size(), vertices->data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//
	//glGenBuffers(1, &Sphere->normalVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->normalVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), normals->data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//glGenBuffers(2, Sphere->VBOs);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->VBOs[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size(), vertices->data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->VBOs[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), normals->data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);


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

	//glGenBuffers(1, &Sphere->tangentVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->tangentVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), tangents->data(), GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &Sphere->bitangentVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->bitangentVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices->size(), bitangents->data(), GL_STATIC_DRAW);
	//
	//glGenBuffers(1, &Sphere->texcoordVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, Sphere->texcoordVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices->size(), texCoords->data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0); 
	glBindVertexArray(0);

	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}