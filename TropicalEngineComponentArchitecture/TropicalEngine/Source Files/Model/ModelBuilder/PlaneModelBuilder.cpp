#include <glm.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/PlaneModelBuilder.h>

PlaneModelBuilder::PlaneModelBuilder()
{
	modelType = "Plane";

	parameters["size X"] = 1.0f;
	parameters["size Y"] = 1.0f;

	parameters["subdivisions X"] = 1;
	parameters["subdivisions Y"] = 1;
}


PlaneModelBuilder::~PlaneModelBuilder()
{
}

void PlaneModelBuilder::resetParameters()
{
	AbstractModelBuilder::resetParameters();

	parameters["size X"] = 1.0f;
	parameters["size Y"] = 1.0f;

	parameters["subdivisions X"] = 1;
	parameters["subdivisions Y"] = 1;
}

Model* PlaneModelBuilder::Build()
{
	QString& name = parameters["name"].value<QString>();
	float sizeX = parameters["size X"].value<float>();
	float sizeY = parameters["size Y"].value<float>();
	uint subdivisionsX = parameters["subdivisions X"].value<uint>();
	uint subdivisionsY = parameters["subdivisions Y"].value<uint>();

	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = subdivisionsX * subdivisionsY * 6;

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

	for (int j = 0; j < subdivisionsY; j++)
	{
		for (int i = 0; i < subdivisionsX; i++)
		{
			vertices.push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices.push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices.push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices.push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + (j * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

			vertices.push_back(glm::vec4(
				-0.5f * sizeX + (i * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

			vertices.push_back(glm::vec4(
				-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
				0.0f,
				-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
				1.0f
				));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
		}
	}

	Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

	Model* model = new Model(name);
	model->meshes.append(Mesh);
	return model;
}