#include <glm.hpp>
#include <gtc/constants.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/TorusModelBuilder.h>


TorusModelBuilder::TorusModelBuilder()
{
	modelType = "Torus";

	parameters["radius"] = new float(1.0f);
	parameters["section radius"] = new float(0.5f);

	parameters["subdivisions axis"] = new uint(20);
	parameters["subdivisions height"] = new uint(20);
}


TorusModelBuilder::~TorusModelBuilder()
{
}

void TorusModelBuilder::resetParameters()
{
	AbstractModelBuilder::resetParameters();

	*((float*)(parameters["radius"])) = 1.0f;
	*((float*)(parameters["section radius"])) = 0.5f;

	*((uint*)(parameters["subdivisions axis"])) = 20;
	*((uint*)(parameters["subdivisions height"])) = 20;
}

Model* TorusModelBuilder::Build()
{
	QString& name = *((QString*)(parameters["name"]));
	float& radius = *((float*)(parameters["radius"]));
	float& segmentRadius = *((float*)(parameters["section radius"]));
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
				sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), (cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))) * sinf(i * (2 * glm::pi<float>() / subdivisionsHeight))
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