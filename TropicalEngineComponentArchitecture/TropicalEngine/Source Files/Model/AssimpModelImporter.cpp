#include <Model/ModelBuilder.h>

#include "Model/AssimpModelImporter.h"

#include <QtCore/qdebug.h>


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
	Model* model = new Model(name);
	const aiScene* pScene = Importer.ReadFile(fileUrl.toLocal8Bit().data(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (pScene)
	{
		for (unsigned int i = 0; i < pScene->mNumMeshes; i++)
		{
			const aiMesh* paiMesh = pScene->mMeshes[i];
			MeshEntry* Mesh = new MeshEntry();

			Mesh->NumVertex = paiMesh->mNumVertices;

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

			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
			for (unsigned int i = 0; i < Mesh->NumVertex; i++)
			{
				const aiVector3D* pPos = &(paiMesh->mVertices[i]);
				const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
				const aiVector3D* pTangent = &(paiMesh->mTangents[i]);
				const aiVector3D* pBitangent = &(paiMesh->mBitangents[i]);
				const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

				vertices->push_back(glm::vec4(pPos->x, pPos->y, pPos->z, 1.0f));
				normals->push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
				tangents->push_back(glm::vec3(pTangent->x, pTangent->y, pTangent->z));
				bitangents->push_back(glm::vec3(pBitangent->x, pBitangent->y, pBitangent->z));
				texCoords->push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
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
		qDebug() << "Error parsing '%s': '%s'" << fileUrl << QString(Importer.GetErrorString());
		return nullptr;
	}

	//delete pScene;

	return model;
}