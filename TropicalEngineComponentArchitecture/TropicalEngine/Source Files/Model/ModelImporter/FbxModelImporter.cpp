#include <QtCore/qdebug.h>

#include <Model/ModelBuilder.h>
#include <Model/ModelImporter/FbxModelImporter.h>


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
	/// TODO: Add support for instanced meshes

	/// TODO: Clean memory!

	Model* model = new Model(name, fileUrl);

	FbxImporter* Importer = FbxImporter::Create(SdkManager, "");

	if (Importer->Initialize(fileUrl.toStdString().c_str(), -1, SdkManager->GetIOSettings()))
	{
		FbxScene* scene = FbxScene::Create(SdkManager, "Importing Scene");
		Importer->Import(scene);
		Converter->Triangulate(scene, true);
		Converter->SplitMeshesPerMaterial(scene, true);

		QList<FbxNode*> helper;
		QMap<FbxNode*, FbxAMatrix> normalMatrices;
		QMap<FbxMesh*, FbxNode*> meshes; //Might break with instancing
		
		helper.append(scene->GetRootNode());
		
		while (!helper.isEmpty())
		{
			FbxNode* it = helper.takeFirst();

			for (int i = 0; i < it->GetChildCount(); i++)
			{
				helper.append(it->GetChild(i));
				
			}

			if (it->GetParent() == NULL)
			{
				normalMatrices[it] = FbxAMatrix(FbxVector4(0.0, 0.0, 0.0), it->EvaluateLocalRotation(), FbxVector4(1.0, 1.0, 1.0))
					* FbxAMatrix(FbxVector4(0.0, 0.0, 0.0), FbxVector4(0.0, 0.0, 0.0), it->EvaluateLocalScaling()).Transpose();
			}
			else
			{
				normalMatrices[it] = normalMatrices[it->GetParent()]
					* FbxAMatrix(FbxVector4(0.0, 0.0, 0.0), it->EvaluateLocalRotation(), FbxVector4(1.0, 1.0, 1.0))
					* FbxAMatrix(FbxVector4(0.0, 0.0, 0.0), FbxVector4(0.0, 0.0, 0.0), it->EvaluateLocalScaling()).Transpose();
			}

			FbxMesh* mesh = it->GetMesh();
			if (mesh != NULL)
			{
				meshes[mesh] = it;
			}
		}
		
		for (FbxMesh* mesh : meshes.keys())
		{
			mesh->SplitPoints(FbxLayerElement::eUV);
			mesh->SplitPoints(FbxLayerElement::eNormal);
		
			MeshEntry* Mesh = new MeshEntry();
			Mesh->NumVertex = mesh->GetControlPointsCount();
		
			QVector<glm::vec4> vertices = QVector<glm::vec4>();	///TODO: should make pos vec3 instead of vec4 and make them vec4 in shaders to save memory?
			QVector<glm::vec3> normals = QVector<glm::vec3>();
			QVector<glm::vec3> tangents = QVector<glm::vec3>();
			QVector<glm::vec3> bitangents = QVector<glm::vec3>();
			QVector<glm::vec2> texCoords = QVector<glm::vec2>();

			vertices.reserve(Mesh->NumVertex);
			normals.reserve(Mesh->NumVertex);
			tangents.reserve(Mesh->NumVertex);
			bitangents.reserve(Mesh->NumVertex);
			texCoords.reserve(Mesh->NumVertex);

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

			FbxAMatrix transformationMatrix = meshes[mesh]->EvaluateGlobalTransform();
			FbxAMatrix normalMatrix = normalMatrices[meshes[mesh]];
			for (int i = 0; i < Mesh->NumVertex; i++)
			{

				FbxVector4 positionHelper = transformationMatrix.MultT(fbxPositions[i]);
				FbxVector4 normalHelper = normalMatrix.MultT(fbxNormals[i]);
				FbxVector4 tangentHelper = normalMatrix.MultT(fbxTangents[i]);
				FbxVector4 bitangentHelper = normalMatrix.MultT(fbxBitangents[i]);

				glm::vec4 position = glm::vec4(positionHelper[0], positionHelper[1], positionHelper[2], 1.0);
				vertices.push_back(position);

				glm::vec3 normal = glm::vec3(normalHelper[0], normalHelper[1], normalHelper[2]);
				normals.push_back(normal);

				glm::vec3 tangent = glm::vec3(tangentHelper[0], tangentHelper[1], tangentHelper[2]);
				tangents.push_back(tangent);

				glm::vec3 bitangent = glm::vec3(bitangentHelper[0], bitangentHelper[1], bitangentHelper[2]);
				bitangents.push_back(bitangent);

				glm::vec2 texCoord = glm::vec2(fbxTexCoords[i][0], fbxTexCoords[i][1]);
				texCoords.push_back(texCoord);
			}

			Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

			model->meshes.append(Mesh);
		}

		/// TODO: Figure out why it crashes.
		//scene->Clear();


	}
	else
	{
		qDebug() << "Call to FbxImporter::Initialize() failed. Error returned: " + QString(Importer->GetStatus().GetErrorString());
		return nullptr;
	}

	Importer->Destroy();

	return model;
}
