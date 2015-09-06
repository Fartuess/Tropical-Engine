#include <QtCore/qvector.h>
#include <Model/Model.h>
#include <Model/ModelManager.h>
#include <Model/ModelBuilder.h>

#include "TropicalEngineApplication.h"

Model::Model(QString name) : meshes()
{
	this->name = name;
	TropicalEngineApplication::instance()->modelManager->Load(this, name);
}

Model::Model(QString name, QString fileUrl) : meshes()
{
	this->name = name;
	this->fileUrl = fileUrl;
	TropicalEngineApplication::instance()->modelManager->Load(this, name);
}

Model::~Model(void)
{
	///TODO: implement it.
}

QString Model::getName()
{
	return name;
}

void Model::setName(QString name)
{
	///TODO: implement changing keynames in Model Managers.
	this->name = name;
}

MeshEntry::MeshEntry()
{
	///TODO: implement it.
}

MeshEntry::~MeshEntry()
{
	///TODO: implement it.
}

void MeshEntry::Finalize(	QVector<glm::vec4>& vertices,
							QVector<glm::vec3>& normals,
							QVector<glm::vec3>& tangents,
							QVector<glm::vec3>& bitangents,
							QVector<glm::vec2>& texCoords)
{
	if (!isFinalized)
	{
		glGenBuffers(1, &this->vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexVBO);

		glBufferData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4) * vertices.size()
			+ sizeof(glm::vec3) * vertices.size()
			+ sizeof(glm::vec3) * vertices.size()
			+ sizeof(glm::vec3) * vertices.size()
			+ sizeof(glm::vec2) * vertices.size(), 0, GL_STATIC_DRAW);

		glBufferSubData(GL_ARRAY_BUFFER,
			0,
			sizeof(glm::vec4) * vertices.size(), vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4) * vertices.size(),
			sizeof(glm::vec3) * vertices.size(), normals.data());
		glBufferSubData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4) * vertices.size() + sizeof(glm::vec3) * vertices.size(),
			sizeof(glm::vec3) * vertices.size(), tangents.data());
		glBufferSubData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4) * vertices.size() + sizeof(glm::vec3) * vertices.size() + sizeof(glm::vec3) * vertices.size(),
			sizeof(glm::vec3) * vertices.size(), bitangents.data());
		glBufferSubData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4) * vertices.size() + sizeof(glm::vec3) * vertices.size() + sizeof(glm::vec3) * vertices.size() + sizeof(glm::vec3) * vertices.size(),
			sizeof(glm::vec2) * vertices.size(), texCoords.data());

		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		isFinalized = true;
	}

}

QString Model::GETTYPENAME("Model");

//QString Model::toXML()
//{
//	///TODO: implement it.
//	//remember that there are two kinds of models - loaded from a file and generated
//	return QString();
//}

QJsonObject Model::toJSON()
{
	///TODO: Add support of generated models serialization;
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	JSON["url"] = fileUrl;

	return JSON;
}

IDeserializableFromJSON* Model::fromJSON(QJsonObject JSON)
{
	QString name = JSON["name"].toString();
	QString fileUrl = JSON["url"].toString();

	return TropicalEngineApplication::instance()->modelBuilder->Load(name, fileUrl);
}