#include <glm.hpp>
#include <gtc/constants.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/SphereModelBuilder.h>

SphereModelBuilder::SphereModelBuilder()
{
	modelType = "Sphere";

	parameters["radius"] = new float(1.0f);

	parameters["subdivisions axis"] = new uint(20);
	parameters["subdivisions height"] = new uint(20);
}


SphereModelBuilder::~SphereModelBuilder()
{
}

void SphereModelBuilder::resetParameters()
{
	AbstractModelBuilder::resetParameters();

	*((float*)(parameters["radius"])) = 1.0f;

	*((uint*)(parameters["subdivisions axis"])) = 20;
	*((uint*)(parameters["subdivisions height"])) = 20;
}

Model* SphereModelBuilder::Build()
{
	QString& name = *((QString*)(parameters["name"]));
	float& radius = *((float*)(parameters["radius"]));
	int subdivisionsAxis = *((uint*)(parameters["subdivisions axis"]));
	int subdivisionsHeight = *((uint*)(parameters["subdivisions height"]));

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
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)i / subdivisionsHeight
				));

			vertices.push_back(glm::vec4(
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)i / subdivisionsHeight)
				));

			vertices.push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				((float)(i + 1) / subdivisionsHeight)
				));

			vertices.push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf(j * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf(j * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)(i + 1) / subdivisionsHeight
				));

			vertices.push_back(glm::vec4(
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf(i * (glm::pi<float>() / subdivisionsHeight)),
				sinf(i * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)i / subdivisionsHeight
				));

			vertices.push_back(glm::vec4(
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				radius * cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				radius * sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				1.0f
				));

			normals.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)
				));

			bitangents.push_back(glm::vec3(
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * cosf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis)),
				-cosf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>())),
				-sinf((float(i + 1) / subdivisionsHeight + 0.5f) * (glm::pi<float>()) * sinf((j + 1) * 2 * glm::pi<float>() / subdivisionsAxis))
				));

			tangents.push_back(glm::vec3(
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * cosf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>()),
				cosf((i + 1) * (glm::pi<float>() / subdivisionsHeight)),
				sinf((i + 1) * (glm::pi<float>() / subdivisionsHeight)) * sinf((float(j + 1) / subdivisionsAxis + 0.25f) * 2 * glm::pi<float>())
				));

			texCoords.push_back(glm::vec2(
				(float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis),
				(float)(i + 1) / subdivisionsHeight
				));
		}
	}

	Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}