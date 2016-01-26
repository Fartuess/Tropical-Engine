#include <glm.hpp>

#include <Model/Model.h>
#include <Model/ModelBuilder/PlaneModelBuilder.h>

#include <Utills/Directions.h>

namespace TropicalEngine
{

	PlaneModelBuilder::PlaneModelBuilder()
	{
		modelType = "Plane";

		parameters["size X"] = 1.0f;
		parameters["size Y"] = 1.0f;

		parameters["subdivisions X"] = 1;
		parameters["subdivisions Y"] = 1;

		parameters["plane"] = PlaneDirections::XZ;
		parameters["inversed"] = false;

		parameters["centered"] = true;
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

		parameters["plane"] = PlaneDirections::XZ;
		parameters["inversed"] = false;

		parameters["centered"] = true;
	}

	Model* PlaneModelBuilder::Build()
	{
		QString& name = parameters["name"].value<QString>();
		float width = parameters["size X"].value<float>();
		float height = parameters["size Y"].value<float>();
		uint subdivisionsWidth = parameters["subdivisions X"].value<uint>();
		uint subdivisionsHeight = parameters["subdivisions Y"].value<uint>();
		PlaneDirections plane = (PlaneDirections)parameters["plane"].value<int>();
		int isInversed = parameters["inversed"].value<bool>();
		int inversed = -2 * ((int)isInversed) + 1;
		bool isCentered = parameters["centered"].value<bool>();

		MeshEntry* Mesh = new MeshEntry();

		Mesh->NumVertex = subdivisionsWidth * subdivisionsHeight * 6;

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

		int i = 0;
		int j = 0;
		int zero = 0;

		float centerOffset = -0.5f * (float)isCentered;

		float sizeX;
		float sizeY;
		float sizeZ;

		uint subdivisionsX;
		uint subdivisionsY;
		uint subdivisionsZ;

		int* idX;
		int* idY;
		int* idZ;

		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		switch (plane)
		{
			case PlaneDirections::XY:
				sizeX = width;
				sizeY = height;
				sizeZ = 0.0f;

				subdivisionsX = subdivisionsWidth;
				subdivisionsY = subdivisionsHeight;
				subdivisionsZ = 1;

				idX = &i;
				idY = &j;
				idZ = &zero;

				normal = glm::vec3(0.0f, 1.0f, -1.0f);
				tangent = glm::vec3(1.0f, 0.0f, 0.0f);
				bitangent = glm::vec3(0.0f, -1.0f, 0.0f);
				break;
			case PlaneDirections::XZ:
				sizeX = width;
				sizeY = 0.0f;
				sizeZ = height;

				subdivisionsX = subdivisionsWidth;
				subdivisionsY = 1;
				subdivisionsZ = subdivisionsHeight;

				idX = &i;
				idY = &zero;
				idZ = &j;

				normal = glm::vec3(0.0f, 1.0f, 0.0f);
				tangent = glm::vec3(1.0f, 0.0f, 0.0f);
				bitangent = glm::vec3(0.0f, 0.0f, -1.0f);
				break;
			case PlaneDirections::YZ:
				sizeX = 0.0f;
				sizeY = height;
				sizeZ = width;

				subdivisionsX = 1;
				subdivisionsY = subdivisionsHeight;
				subdivisionsZ = subdivisionsWidth;

				idX = &zero;
				idY = &j;
				idZ = &i;

				normal = glm::vec3(1.0f, 0.0f, 0.0f);
				tangent = glm::vec3(0.0f, 0.0f, 1.0f);
				bitangent = glm::vec3(0.0f, -1.0f, 0.0f);
				break;
		}

		for (j = 0; j < subdivisionsHeight; j++)
		{
			for (i = 0; i < subdivisionsWidth; i++)
			{
				int _i = i;
				int _j = j;

				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				j++;
				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				i++;
				j--;
				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				i--;
				j++;
				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				i++;
				vertices.push_back(glm::vec4(
					centerOffset * sizeX + (*idX * sizeX / subdivisionsX),
					centerOffset * sizeY + (*idY * sizeY / subdivisionsY),
					centerOffset * sizeZ + (*idZ * sizeZ / subdivisionsZ),
					1.0f
					));

				i = _i;
				j = _j;

				for (int k = 0; k < 6; k++)
				{
					normals.push_back(normal * (float)inversed);
					tangents.push_back(tangent);
					bitangents.push_back(bitangent);
				}

				texCoords.push_back(glm::vec2(i * width / subdivisionsWidth, j * height / subdivisionsHeight));
				texCoords.push_back(glm::vec2(i * width / subdivisionsWidth, (j + 1) * height / subdivisionsHeight));
				texCoords.push_back(glm::vec2((i + 1) * width / subdivisionsWidth, j * height / subdivisionsHeight));
				texCoords.push_back(glm::vec2((i + 1) * width / subdivisionsWidth, j * height / subdivisionsHeight));
				texCoords.push_back(glm::vec2(i * width / subdivisionsWidth, (j + 1) * height / subdivisionsHeight));
				texCoords.push_back(glm::vec2((i + 1) * width / subdivisionsWidth, (j + 1) * height / subdivisionsHeight));
			}
		}

		//quick and dirty solution, should not be an issue until this builder will be used for stuff like terrain.
		if (isInversed)
		{
			QVector<glm::vec4> vertices2 = vertices;
			QVector<glm::vec2> texcoords2 = texCoords;

			vertices.clear();
			texCoords.clear();

			for (glm::vec4 vert : vertices2)
			{
				vertices.push_front(vert);
			}
			for (glm::vec2 texCoord : texcoords2)
			{
				texCoords.push_front(texCoord);
			}
		}

		Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

		Model* model = new Model(name);
		model->meshes.append(Mesh);
		return model;
	}

}