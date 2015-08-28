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

	QVector<glm::vec4> vertices = QVector<glm::vec4>();
	QVector<glm::vec3> normals = QVector<glm::vec3>();
	QVector<glm::vec3> tangents = QVector<glm::vec3>();
	QVector<glm::vec3> bitangents = QVector<glm::vec3>();
	QVector<glm::vec2> texCoords = QVector<glm::vec2>();

	vertices.reserve(Mesh->NumVertex);
	normals.reserve(Mesh->NumVertex);
    tangents.reserve(Mesh->NumVertex);
	bitangents.reserve(Mesh->NumVertex);
    texCoords.reserve(Mesh->NumVertex);

	for (int i = 0; i < subdivisionsHeight; i++)
	{
		for (int j = 0; j < subdivisionsAxis; j++)
		{
			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			vertices.push_back(glm::vec4(
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				segmentRadius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(radius + (segmentRadius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				1.0f
			));

			//normals
			normals.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			normals.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			//tangents
			bitangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			bitangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));
			
			//bitangents
			tangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents.push_back(glm::vec3(
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf((i + 1) * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			tangents.push_back(glm::vec3(
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * cosf(i * (2 * glm::pi<float>() / subdivisionsHeight)),
				sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
			));

			//texcoords
			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));

			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
			));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
			));
		}
	}

	Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}