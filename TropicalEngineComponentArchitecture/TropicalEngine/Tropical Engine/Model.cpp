#include <QtCore\qvector.h>
#include "Model.h"
#include "ModelManager.h"


Model::Model(QString name) : meshes()
{
	ModelManager::Instance().Load(this, name);
}

Model::Model(QString name, QString fileUrl) : meshes()
{
	///TODO: implement it.
	
}


Model::~Model(void)
{
	///TODO: implement it.
}

MeshEntry::MeshEntry()
{
	///TODO: implement it.
}

MeshEntry::~MeshEntry()
{
	///TODO: implement it.
}