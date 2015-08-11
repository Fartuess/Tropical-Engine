#include <Model/ModelBuilder.h>

#include "Model/FbxModelImporter.h"

#include <QtCore/qdebug.h>


FbxModelImporter::FbxModelImporter()
{
	SdkManager = FbxManager::Create();
	IOSettings = FbxIOSettings::Create(SdkManager, IOSROOT);
	Converter = new FbxGeometryConverter(SdkManager);

	supportedExtensions << "fbx";

	ModelBuilder::AddImporter(this);
}


FbxModelImporter::~FbxModelImporter()
{
}

Model* FbxModelImporter::Load(QString name, QString fileUrl)
{
	/// TODO: Multiple submeshes values by their node matrix values.

	/// TODO: Clean memory!

	Model* model = new Model(name);

	FbxImporter* Importer = FbxImporter::Create(SdkManager, "");

	if (Importer->Initialize(fileUrl.toStdString().c_str(), -1, SdkManager->GetIOSettings()))
	{
		FbxScene* scene = FbxScene::Create(SdkManager, "Importing Scene");
		Importer->Import(scene);
		Converter->Triangulate(scene, true);
		Converter->SplitMeshesPerMaterial(scene, true);

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
			FbxMesh* mesh = it->GetMesh();
			if (mesh != NULL)
			{
				meshes.append(mesh);
			}
		}
		
		for (FbxMesh* mesh : meshes)
		{

			mesh->SplitPoints(FbxLayerElement::eUV);
			mesh->SplitPoints(FbxLayerElement::eNormal);
		
			MeshEntry* Mesh = new MeshEntry();
			Mesh->NumVertex = mesh->GetControlPointsCount();
		
			QVector<glm::vec4>* vertices = new QVector<glm::vec4>();	///TODO: should make pos vec3 instead of vec4 and make them vec4 in shaders to save memory?
			QVector<glm::vec3>* normals = new QVector<glm::vec3>();
			QVector<glm::vec3>* tangents = new QVector<glm::vec3>();
			QVector<glm::vec3>* bitangents = new QVector<glm::vec3>();
			QVector<glm::vec2>* texCoords = new QVector<glm::vec2>();

			vertices->reserve(Mesh->NumVertex);
			normals->reserve(Mesh->NumVertex);
			tangents->reserve(Mesh->NumVertex);
			bitangents->reserve(Mesh->NumVertex);
			texCoords->reserve(Mesh->NumVertex);

			FbxLayerElementArrayTemplate<FbxVector4> fbxPositions = FbxLayerElementArrayTemplate<FbxVector4>(EFbxType::eFbxDouble4);
			FbxLayerElementArrayTemplate<FbxVector4> fbxNormals = FbxLayerElementArrayTemplate<FbxVector4>(EFbxType::eFbxDouble4);
			FbxLayerElementArrayTemplate<FbxVector4> fbxTangents = FbxLayerElementArrayTemplate<FbxVector4>(EFbxType::eFbxDouble4);
			FbxLayerElementArrayTemplate<FbxVector4> fbxBitangents = FbxLayerElementArrayTemplate<FbxVector4>(EFbxType::eFbxDouble4);
			FbxLayerElementArrayTemplate<FbxVector2> fbxTexCoords = FbxLayerElementArrayTemplate<FbxVector2>(EFbxType::eFbxDouble2);

			FbxLayerElementArrayTemplate<FbxVector4> fbxNormals_t = mesh->GetLayer(0)->GetNormals()->GetDirectArray();
			FbxLayerElementArrayTemplate<FbxVector4> fbxTangents_t = mesh->GetLayer(0)->GetTangents()->GetDirectArray();
			FbxLayerElementArrayTemplate<FbxVector4> fbxBitangents_t = mesh->GetLayer(0)->GetBinormals()->GetDirectArray();
			FbxLayerElementArrayTemplate<FbxVector2> fbxTexCoords_t = mesh->GetLayer(0)->GetUVs()->GetDirectArray();

			int polycount = mesh->GetPolygonCount();
			for (int i = 0; i < polycount; i++)
			{
				fbxPositions.Add(mesh->GetControlPointAt(mesh->GetPolygonVertex(i, 0)));
				fbxPositions.Add(mesh->GetControlPointAt(mesh->GetPolygonVertex(i, 1)));
				fbxPositions.Add(mesh->GetControlPointAt(mesh->GetPolygonVertex(i, 2)));

				fbxNormals.Add(fbxNormals_t[mesh->GetPolygonVertex(i, 0)]);
				fbxNormals.Add(fbxNormals_t[mesh->GetPolygonVertex(i, 1)]);
				fbxNormals.Add(fbxNormals_t[mesh->GetPolygonVertex(i, 2)]);

				fbxTangents.Add(fbxTangents_t[mesh->GetPolygonVertex(i, 0)]);
				fbxTangents.Add(fbxTangents_t[mesh->GetPolygonVertex(i, 1)]);
				fbxTangents.Add(fbxTangents_t[mesh->GetPolygonVertex(i, 2)]);

				fbxBitangents.Add(fbxBitangents_t[mesh->GetPolygonVertex(i, 0)]);
				fbxBitangents.Add(fbxBitangents_t[mesh->GetPolygonVertex(i, 1)]);
				fbxBitangents.Add(fbxBitangents_t[mesh->GetPolygonVertex(i, 2)]);

				fbxTexCoords.Add(fbxTexCoords_t[mesh->GetPolygonVertex(i, 0)]);
				fbxTexCoords.Add(fbxTexCoords_t[mesh->GetPolygonVertex(i, 1)]);
				fbxTexCoords.Add(fbxTexCoords_t[mesh->GetPolygonVertex(i, 2)]);
			}

			

			for (int i = 0; i < Mesh->NumVertex; i++)
			{
				//glm::vec4 position = glm::vec4(mesh->GetControlPointAt(i)[0], mesh->GetControlPointAt(i)[1], mesh->GetControlPointAt(i)[2], 1.0f);
				glm::vec4 position = glm::vec4(fbxPositions[i][0], fbxPositions[i][1], fbxPositions[i][2], 1.0);
				vertices->push_back(position);

				glm::vec3 normal = glm::vec3(fbxNormals[i][0], fbxNormals[i][1], fbxNormals[i][2]);
				normals->push_back(normal);

				glm::vec3 tangent = glm::vec3(fbxTangents[i][0], fbxTangents[i][1], fbxTangents[i][2]);
				tangents->push_back(tangent);

				glm::vec3 bitangent = glm::vec3(fbxBitangents[i][0], fbxBitangents[i][1], fbxBitangents[i][2]);
				bitangents->push_back(bitangent);

				glm::vec2 texCoord = glm::vec2(fbxTexCoords[i][0], fbxTexCoords[i][1]);
				texCoords->push_back(texCoord);
			}

			glGenBuffers(1, &Mesh->vertexVBO);
			glBindBuffer(GL_ARRAY_BUFFER, Mesh->vertexVBO);

			glBufferData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices->size()
				+ sizeof(glm::vec3) * vertices->size()
				+ sizeof(glm::vec3) * vertices->size()
				+ sizeof(glm::vec3) * vertices->size()
				+ sizeof(glm::vec2) * vertices->size(), 0, GL_STATIC_DRAW);

			glBufferSubData(GL_ARRAY_BUFFER,
				0,
				sizeof(glm::vec4) * vertices->size(), vertices->data());
			glBufferSubData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices->size(),
				sizeof(glm::vec3) * vertices->size(), normals->data());
			glBufferSubData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
				sizeof(glm::vec3) * vertices->size(), tangents->data());
			glBufferSubData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
				sizeof(glm::vec3) * vertices->size(), bitangents->data());
			glBufferSubData(GL_ARRAY_BUFFER,
				sizeof(glm::vec4) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size() + sizeof(glm::vec3) * vertices->size(),
				sizeof(glm::vec2) * vertices->size(), texCoords->data());

			glEnableVertexAttribArray(0);
			glBindVertexArray(0);

			model->meshes.append(*Mesh);
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
