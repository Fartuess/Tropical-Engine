#include <glm.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/BoxModelBuilder.h>

namespace TropicalEngine
{

	BoxModelBuilder::BoxModelBuilder()
	{
		modelType = "Box";

		parameters["size X"] = 1.0f;
		parameters["size Y"] = 1.0f;
		parameters["size Z"] = 1.0f;

		parameters["subdivisions X"] = 1;
		parameters["subdivisions Y"] = 1;
		parameters["subdivisions Z"] = 1;

		parameters["backfacing"] = false;
	}


	BoxModelBuilder::~BoxModelBuilder()
	{
	}

	void BoxModelBuilder::resetParameters()
	{
		AbstractModelBuilder::resetParameters();

		parameters["size X"] = 1.0f;
		parameters["size Y"] = 1.0f;
		parameters["size Z"] = 1.0f;

		parameters["subdivisions X"] = 1;
		parameters["subdivisions Y"] = 1;
		parameters["subdivisions Z"] = 1;

		parameters["backfacing"] = false;
	}

	Model* BoxModelBuilder::Build()
	{
		QString& name = parameters["name"].value<QString>();
		float sizeX = parameters["size X"].value<float>();
		float sizeY = parameters["size Y"].value<float>();
		float sizeZ = parameters["size Z"].value<float>();
		uint subdivisionsX = parameters["subdivisions X"].value<uint>();
		uint subdivisionsY = parameters["subdivisions Y"].value<uint>();
		uint subdivisionsZ = parameters["subdivisions Z"].value<uint>();
		bool isBackfacing = parameters["backfacing"].value<bool>();

		MeshEntry* Mesh = new MeshEntry();

		Mesh->NumVertex = subdivisionsX * subdivisionsY * 6 * 6;
		Mesh->isBackfacing = isBackfacing;

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

		for (int j = 0; j < subdivisionsZ; j++)	//Top Face
		{
			for (int i = 0; i < subdivisionsX; i++)
			{
				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i * sizeX / subdivisionsX), (j + 1) * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j * sizeZ / subdivisionsZ)));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));
			}
		}

		for (int j = 0; j < subdivisionsZ; j++)	//Bottom Face
		{
			for (int i = 0; i < subdivisionsX; i++)
			{
				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + (j * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY,
					-0.5f * sizeZ + ((j + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeZ / subdivisionsZ));
			}
		}

		for (int j = 0; j < subdivisionsY; j++)	//Front Face
		{
			for (int i = 0; i < subdivisionsX; i++)
			{
				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
			}
		}

		for (int j = 0; j < subdivisionsY; j++)	//Back Face
		{
			for (int i = 0; i < subdivisionsX; i++)
			{
				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + (i * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX + ((i + 1) * sizeX / subdivisionsX),
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ,
					1.0f
					));
				normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeX / subdivisionsX, (j + 1) * sizeY / subdivisionsY));
			}
		}

		for (int j = 0; j < subdivisionsY; j++)	//Left Face
		{
			for (int i = 0; i < subdivisionsZ; i++)
			{
				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					-0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));
			}
		}

		for (int j = 0; j < subdivisionsY; j++)	//Right Face
		{
			for (int i = 0; i < subdivisionsZ; i++)
			{
				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + (j * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, j * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + (i * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2(i * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));

				vertices.push_back(glm::vec4(
					0.5f * sizeX,
					-0.5f * sizeY + ((j + 1) * sizeY / subdivisionsY),
					-0.5f * sizeZ + ((i + 1) * sizeZ / subdivisionsZ),
					1.0f
					));
				normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				tangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				texCoords.push_back(glm::vec2((i + 1) * sizeZ / subdivisionsZ, (j + 1) * sizeY / subdivisionsY));
			}
		}

		Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

		Model* model = new Model(name);
		model->meshes.append(Mesh);
		return model;
	}

}