#include <QtCore/qvector.h>

#include <Model/Model.h>
#include <Model/ModelBuilder/TriangleModelBuilder.h>

TriangleModelBuilder::TriangleModelBuilder()
{
	modelType = "Triangle";
}


TriangleModelBuilder::~TriangleModelBuilder()
{
}

Model* TriangleModelBuilder::Build()
{

	QString name = parameters["name"].value<QString>();

	MeshEntry* Mesh = new MeshEntry();

	Mesh->NumVertex = 3;

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

	{
		vertices.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords.push_back(glm::vec2(0.0f, 0.0f));

		vertices.push_back(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords.push_back(glm::vec2(1.0f, 0.0f));

		vertices.push_back(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		tangents.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		bitangents.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		texCoords.push_back(glm::vec2(1.0f, 1.0f));
	}

	Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

	Model* model = new Model(name);
	model->meshes.push_back(*Mesh);
	return model;
}