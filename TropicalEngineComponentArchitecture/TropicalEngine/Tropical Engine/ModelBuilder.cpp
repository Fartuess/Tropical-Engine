#include <gl\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <QtCore\qvector.h>
#include <QtCore\qstring.h>
#include "Model.h"
#include "ModelBuilder.h"

ModelBuilder::ModelBuilder(void)
{
}


ModelBuilder::~ModelBuilder(void)
{
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


	return nullptr;
}

Model* ModelBuilder::CreateTorus(QString name, float radius, float segmentRadius, int subdivisionsAxis, int subdivisionsHeight)
{
	///TODO: implement it.
	return nullptr;
}
