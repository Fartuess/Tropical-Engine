#include <QtCore\qvector.h>
#include "Model\Model.h"
#include "Model\ModelManager.h"

#include "TropicalEngineApplication.h"

Model::Model(QString name) : meshes()
{
	this->name = name;
	TropicalEngineApplication::instance()->modelManager->Load(this, name);
}

Model::Model(QString name, QString fileUrl) : meshes()
{
	///TODO: implement it.
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

void MeshEntry::Finalize()
{
	///TODO: implement it, so it's not required in every model builder?
	//glGenBuffers(1, &vertexVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size(), 0, GL_STATIC_DRAW); 
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * vertices->size(), vertices->data());
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * vertices->size(), sizeof(glm::vec3) * vertices->size(), normals->data());
}

QString Model::toXML()
{
	///TODO: implement it.
	//remember that there are two kinds of models - loaded from a file and generated
	return QString();
}

QJsonObject Model::toJSON()
{
	///TODO: Add support of generated models serialization;
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	JSON["url"] = fileUrl;

	return JSON;
}