#include <QtCore/qdebug.h>

#include <Model/ModelBuilder.h>
#include <Model/ModelImporter/AssimpModelImporter.h>

namespace TropicalEngine
{

	AssimpModelImporter::AssimpModelImporter()
	{
		supportedExtensions << "obj" << "dae";	// There are more formats supported by Open Asset Importer.

		ModelBuilder::AddImporter(this);
	}


	AssimpModelImporter::~AssimpModelImporter()
	{
	}

	Model* AssimpModelImporter::Load(QString name, QString fileUrl)
	{
		Model* model = new Model(name, fileUrl);
		const aiScene* pScene = Importer.ReadFile(fileUrl.toLocal8Bit().data(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);

		if (pScene != NULL)
		{
			for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
			{
				aiMesh* paiMesh = pScene->mMeshes[i];
				MeshEntry* Mesh = new MeshEntry();

				Mesh->NumVertex = paiMesh->mNumVertices;

				QVector<glm::vec4> vertices = QVector<glm::vec4>();	// TODO: should make pos vec3 instead of vec4 and make them vec4 in shaders to save memory?
				QVector<glm::vec3> normals = QVector<glm::vec3>();
				QVector<glm::vec3> tangents = QVector<glm::vec3>();
				QVector<glm::vec3> bitangents = QVector<glm::vec3>();
				QVector<glm::vec2> texCoords = QVector<glm::vec2>();

				vertices.reserve(Mesh->NumVertex);
				normals.reserve(Mesh->NumVertex);
				tangents.reserve(Mesh->NumVertex);
				bitangents.reserve(Mesh->NumVertex);
				texCoords.reserve(Mesh->NumVertex);

				aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
				for (unsigned int i = 0; i < Mesh->NumVertex; i++)
				{
					aiVector3D pPos = paiMesh->mVertices[i];
					aiVector3D pNormal = paiMesh->mNormals[i];
					aiVector3D pTangent = paiMesh->mTangents[i];
					aiVector3D pBitangent = paiMesh->mBitangents[i];
					aiVector3D pTexCoord = paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : Zero3D;

					vertices.push_back(glm::vec4(pPos.x, pPos.y, pPos.z, 1.0f));
					normals.push_back(glm::vec3(pNormal.x, pNormal.y, pNormal.z));
					tangents.push_back(glm::vec3(pTangent.x, pTangent.y, pTangent.z));
					bitangents.push_back(glm::vec3(pBitangent.x, pBitangent.y, pBitangent.z));
					texCoords.push_back(glm::vec2(pTexCoord.x, pTexCoord.y));
				}

				Mesh->Finalize(vertices, normals, tangents, bitangents, texCoords);

				model->meshes.append(Mesh);
			}
			Importer.FreeScene();
		}
		else
		{
			qDebug() << "Error parsing '%s': '%s'" << fileUrl << QString(Importer.GetErrorString());
			return nullptr;
		}

		return model;
	}

}