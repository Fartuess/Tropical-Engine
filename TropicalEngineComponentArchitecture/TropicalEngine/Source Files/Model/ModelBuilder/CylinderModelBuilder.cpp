#include <glm.hpp>
#include <gtc/constants.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/CylinderModelBuilder.h>

namespace TropicalEngine
{

	CylinderModelBuilder::CylinderModelBuilder()
	{
		modelType = "Cylinder";

		parameters["radius"] = 1.0f;
		parameters["height"] = 2.0f;

		parameters["subdivisions axis"] = 20;
		parameters["subdivisions height"] = 1;

		parameters["backfacing"] = false;
	}

	CylinderModelBuilder::~CylinderModelBuilder()
	{
	}

	void CylinderModelBuilder::resetParameters()
	{
		AbstractModelBuilder::resetParameters();

		parameters["radius"] = 1.0f;
		parameters["height"] = 2.0f;

		parameters["subdivisions axis"] = 20;
		parameters["subdivisions height"] = 1;

		parameters["backfacing"] = false;
	}

	Model* CylinderModelBuilder::Build()
	{
		QString& name = parameters["name"].value<QString>();
		float radius = parameters["radius"].value<float>();
		float height = parameters["height"].value<float>();
		int subdivisionsAxis = parameters["subdivisions axis"].value<uint>();
		int subdivisionsHeight = parameters["subdivisions height"].value<uint>();
		bool isBackfacing = parameters["backfacing"].value<bool>();

		MeshEntry* Mesh = new MeshEntry();

		Mesh->NumVertex = (subdivisionsAxis * subdivisionsHeight * 6) + (subdivisionsAxis * 6);
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

		for (int i = 0; i < subdivisionsHeight; i++)	//Tangents bitangents fix for sides
		{
			for (int j = 0; j < subdivisionsAxis; j++)
			{
				//Side
				vertices.push_back(glm::vec4(
					radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + ((i * height) / subdivisionsHeight),
					radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));
				vertices.push_back(glm::vec4(
					radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
					radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));
				vertices.push_back(glm::vec4(
					radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + ((i * height) / subdivisionsHeight),
					radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));

				normals.push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
				normals.push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
				normals.push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));

				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

				tangents.push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
				tangents.push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));
				tangents.push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));

				texCoords.push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));
				texCoords.push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
				texCoords.push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));

				vertices.push_back(glm::vec4(
					radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
					radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));
				vertices.push_back(glm::vec4(
					radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + ((i * height) / subdivisionsHeight),
					radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));
				vertices.push_back(glm::vec4(
					radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					-0.5f * height + (((i + 1) * height) / subdivisionsHeight),
					radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
					1.0f
					));

				normals.push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
				normals.push_back(glm::vec3(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
				normals.push_back(glm::vec3(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis))));

				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
				bitangents.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

				tangents.push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
				tangents.push_back(glm::vec3(sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis))));
				tangents.push_back(glm::vec3(sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)), 0.0f, cosf(j * (2 * glm::pi<float>() / subdivisionsAxis))));

				texCoords.push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
				texCoords.push_back(glm::vec2((float)((j + 1) * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)i / subdivisionsHeight)));
				texCoords.push_back(glm::vec2((float)(j * 2 * glm::pi<float>() * radius / subdivisionsAxis), ((float)(i + 1) / subdivisionsHeight)));
			}
		}

		for (int j = -1; j < subdivisionsAxis - 1; j++)
		{
			//Top
			vertices.push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * 0.5f,
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
				));
			vertices.push_back(glm::vec4(
				0.0f,
				height * 0.5f,
				0.0f,
				1.0f
				));
			vertices.push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * 0.5f,
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
				));

			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

			texCoords.push_back(glm::vec2(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords.push_back(glm::vec2(0.5f, 0.5f));
			texCoords.push_back(glm::vec2(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));

			//Bottom
			vertices.push_back(glm::vec4(
				radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * (-0.5f),
				radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
				));
			vertices.push_back(glm::vec4(
				radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * (-0.5f),
				radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f
				));
			vertices.push_back(glm::vec4(
				0.0f,
				height * (-0.5f),
				0.0f,
				1.0f
				));

			normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
			normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
			bitangents.push_back(glm::vec3(0.0f, 0.0f, -1.0f));

			texCoords.push_back(glm::vec2(cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords.push_back(glm::vec2(cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f, sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)) + 0.5f));
			texCoords.push_back(glm::vec2(0.5f, 0.5f));
		}

		Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

		Model* model = new Model(name);
		model->meshes.append(Mesh);
		return model;
	}

}