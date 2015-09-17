#include <glm.hpp>
#include <gtc/constants.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/ConeModelBuilder.h>

ConeModelBuilder::ConeModelBuilder()
{
	modelType = "Cone";

	parameters["radius"] = new float(1.0f);
	parameters["height"] = new float(2.0f);

	parameters["subdivisions axis"] = new uint(20);
	parameters["subdivisions height"] = new uint(1);
}


ConeModelBuilder::~ConeModelBuilder()
{
}

void ConeModelBuilder::resetParameters()
{
	AbstractModelBuilder::resetParameters();

	*((float*)(parameters["radius"])) = 1.0f;
	*((float*)(parameters["height"])) = 2.0f;

	*((uint*)(parameters["subdivisions axis"])) = 20;
	*((uint*)(parameters["subdivisions height"])) = 1;
}

Model* ConeModelBuilder::Build()
{
	QString& name = *((QString*)(parameters["name"]));
	float& radius = *((float*)(parameters["radius"]));
	float& height = *((float*)(parameters["height"]));
	int subdivisionsAxis = *((uint*)(parameters["subdivisions axis"]));
	int subdivisionsHeight = *((uint*)(parameters["subdivisions height"]));

	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = (subdivisionsAxis * subdivisionsHeight * 6) + (subdivisionsAxis * 3);

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
		float h = radius * (1 - ((float)(i) / subdivisionsHeight));
		float h2 = radius * (1 - ((float)(i + 1) / subdivisionsHeight));
		//one loop
		for (int j = 0; j < subdivisionsAxis; j++)
		{
			vertices.push_back(glm::vec4(
				h * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i) / subdivisionsHeight),
				h * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));
			vertices.push_back(glm::vec4(
				h2 * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i + 1) / subdivisionsHeight),
				h2 * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));
			vertices.push_back(glm::vec4(
				h * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i) / subdivisionsHeight),
				h * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));

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
				h2 * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i + 1) / subdivisionsHeight),
				h2 * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));
			vertices.push_back(glm::vec4(
				h * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i) / subdivisionsHeight),
				h * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));
			vertices.push_back(glm::vec4(
				h2 * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				height * ((-0.5f + i + 1) / subdivisionsHeight),
				h2 * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
				1.0f));

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

	for (int j = 0; j < subdivisionsAxis; j++)
	{
		//Bottom
		vertices.push_back(glm::vec4(
			radius * cosf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
			height * (-0.5f),
			radius * sinf(j * (2 * glm::pi<float>() / subdivisionsAxis)),
			1.0f));
		vertices.push_back(glm::vec4(
			radius * cosf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
			height * (-0.5f),
			radius * sinf((j + 1) * (2 * glm::pi<float>() / subdivisionsAxis)),
			1.0f));
		vertices.push_back(glm::vec4(
			0.0f,
			height * (-0.5f),
			0.0f,
			1.0f));

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
	model->meshes.append(*Mesh);
	return model;
}