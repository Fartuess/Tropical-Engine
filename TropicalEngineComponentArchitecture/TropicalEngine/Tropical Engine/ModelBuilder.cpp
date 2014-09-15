#include <gl\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include <QtCore\qbytearray.h>
#include "Model.h"
#include "ModelBuilder.h"

#include <QtCore\qdebug.h>

ModelBuilder::ModelBuilder(void)
{
	///TODO: implement it?
}


ModelBuilder::~ModelBuilder(void)
{
	///TODO: implement it?
}

Model* ModelBuilder::Load(QString fileUrl)
{
	/////TODO: implement it.
	//Assimp::Importer importer;
	//
	//const aiScene* modelScene = importer.ReadFile(fileUrl.toUtf8().constData(), aiProcess_Triangulate);
	//
	//Model* model = new Model();
	//
	//model->meshes.resize(modelScene->mNumMeshes);
	//model->materialCount = modelScene->mNumMaterials;
	//
    //// Initialize the meshes in the scene one by one
    //for (unsigned int i = 0 ; i < model->meshes.size() ; i++)
	//{
    //    const aiMesh* paiMesh = modelScene->mMeshes[i];
	//
    //    //m_Entries[i].MaterialIndex = paiMesh->mMaterialIndex;
    //
	//	QVector<Vertex> vertices;
	//	QVector<unsigned int> indices;
	//
	//	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	//
	//	for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
	//	    const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
	//	    const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);
	//		const aiVector3D* pTangent   = &(paiMesh->mTangents[i]);
	//		const aiVector3D* pBitangent = &(paiMesh->mBitangents[i]);
	//	    const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
	//
	//	    Vertex vertex	(glm::vec3(pPos->x, pPos->y, pPos->z),
	//						glm::vec3(pNormal->x, pNormal->y, pNormal->z),
	//						glm::vec3(pTangent->x, pTangent->y, pTangent->z),
	//						glm::vec3(pBitangent->x, pBitangent->y, pBitangent->z),
	//						glm::vec2(pTexCoord->x, pTexCoord->y));
	//
	//	    vertices.push_back(vertex);
	//	}
	//
	//	for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
	//	    const aiFace& Face = paiMesh->mFaces[i];
	//	    assert(Face.mNumIndices == 3);
	//	    indices.push_back(Face.mIndices[0]);
	//	    indices.push_back(Face.mIndices[1]);
	//	    indices.push_back(Face.mIndices[2]);
	//	}
	//
	//	model->meshes[i].NumIndices = indices.size();
	//
	//	glGenBuffers(1, &model->meshes[i].VertexBuffer);
  	//	glBindBuffer(GL_ARRAY_BUFFER, model->meshes[i].VertexBuffer);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	//
	//	glGenBuffers(1, &model->meshes[i].IndexBuffer);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->meshes[i].IndexBuffer);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model->meshes[i].NumIndices, &indices[0], GL_STATIC_DRAW);
    //}
	//
	//return model;
	return nullptr;
}

Model* ModelBuilder::Load(QString name, QString fileUrl)
{
	///TODO: implement it.
	
	Assimp::Importer Importer;
	Model* model = new Model(name);
	const aiScene* pScene = Importer.ReadFile(fileUrl.toLocal8Bit().data(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (pScene)
	{
		for (unsigned int i = 0 ; i < pScene->mNumMeshes ; i++)
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
			for (unsigned int i = 0 ; i < Mesh->NumVertex ; i++)
			{
				const aiVector3D* pPos			= &(paiMesh->mVertices[i]);
				const aiVector3D* pNormal		= &(paiMesh->mNormals[i]);
				const aiVector3D* pTangent		= &(paiMesh->mTangents[i]);
				const aiVector3D* pBitangent	= &(paiMesh->mBitangents[i]);
				const aiVector3D* pTexCoord		= paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

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
        //printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }

	return model;
	
	//return nullptr;
}
