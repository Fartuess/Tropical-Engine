#include <Model/ModelBuilder.h>

#include "Model/FbxModelImporter.h"

#include <QtCore/qdebug.h>


FbxModelImporter::FbxModelImporter()
{
	SdkManager = FbxManager::Create();
	IOSettings = FbxIOSettings::Create(SdkManager, IOSROOT);

	supportedExtensions << "fbx";

	ModelBuilder::AddImporter(this);
}


FbxModelImporter::~FbxModelImporter()
{
}

Model* FbxModelImporter::Load(QString name, QString fileUrl)
{
	/// TODO: Implement it!

	/// TODO: Clean memory!

	Model* model = new Model(name);

	FbxImporter* Importer = FbxImporter::Create(SdkManager, "");

	if (Importer->Initialize(fileUrl.toStdString().c_str(), -1, SdkManager->GetIOSettings()))
	{
		FbxScene* scene = FbxScene::Create(SdkManager, "Importing Scene");
		Importer->Import(scene);

		//QList<FbxNode*> objects;
		QList<FbxNode*> helper;
		QList<FbxMesh*> meshes;

		helper.append(scene->GetRootNode());

		while (!helper.isEmpty())
		{
			FbxNode* it = helper.takeFirst();

			for (int i = 0; i < it->GetChildCount(); i++)
			{
				helper.append(it->GetChild(i));
			}

			meshes.append(it->GetMesh());

			for (FbxMesh* mesh : meshes)
			{
				/// TODO: Finish implementation.

				MeshEntry* Mesh = new MeshEntry();

				//Mesh->NumVertex = mesh->getPo

				QVector<glm::vec4>* vertices = new QVector<glm::vec4>();	///TODO: should make pos vec3 instead of vec4 and make them vec4 in shaders to save memory?
				QVector<glm::vec3>* normals = new QVector<glm::vec3>();
				QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
				QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
				QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();
			}
		}


	}
	else
	{
		qDebug() << "Call to FbxImporter::Initialize() failed. Error returned: " + QString(Importer->GetStatus().GetErrorString());
		return nullptr;
	}

	Importer->Destroy();

	return model;
}
