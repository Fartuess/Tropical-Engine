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

Model* ModelBuilder::CreatePlane(QString name, float sizeX, float sizeY, int subdivisionsX, int subdivisionsY)
{
	MeshEntry* Plane = new MeshEntry();

	Plane->NumVertex = subdivisionsX * subdivisionsY * 6;

	QVector<GLfloat>* vertices = new QVector<GLfloat>();
	QVector<GLfloat>* normals = new QVector<GLfloat>();
	QVector<GLfloat>* tangents = new QVector<GLfloat>();
	QVector<GLfloat>* bitangents = new QVector<GLfloat>();
	QVector<GLfloat>* texCoords = new QVector<GLfloat>();

	vertices->reserve(4 * Plane->NumVertex);
	normals->reserve(3 * Plane->NumVertex);
    tangents->reserve(3 * Plane->NumVertex);
	bitangents->reserve(3 * Plane->NumVertex);
    texCoords->reserve(2 * Plane->NumVertex);

	for(int j = -1; j < subdivisionsY - 1; j++)
	{
		for(int i = -1; i < subdivisionsX - 1; i++)
		{
			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back(j * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back(i * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);

			vertices->push_back((-0.5f + i + 1) * sizeX / subdivisionsX);vertices->push_back(0.0f);vertices->push_back((-0.5f + j + 1) * sizeY / subdivisionsY);vertices->push_back(1.0f);
			normals->push_back(0.0f);normals->push_back(1.0f);normals->push_back(0.0f);
			tangents->push_back(1.0f);tangents->push_back(0.0f);tangents->push_back(0.0f);
			bitangents->push_back(0.0f);bitangents->push_back(0.0f);bitangents->push_back(1.0f);
			texCoords->push_back((i + 1) * sizeX / subdivisionsX);texCoords->push_back((j + 1) * sizeY / subdivisionsY);
		}
	}

	glGenVertexArrays(1, &Plane->VAO);
	glBindVertexArray(Plane->VAO);

	glGenBuffers(1, &Plane->vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices->data()), vertices->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals->data()), normals->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->tangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->tangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tangents->data()), tangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->bitangentVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->bitangentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bitangents->data()), bitangents->data(), GL_STATIC_DRAW);

	glGenBuffers(1, &Plane->texcoordVBO);
	glBindBuffer(GL_ARRAY_BUFFER, Plane->texcoordVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords->data()), texCoords->data(), GL_STATIC_DRAW);
	

	Model* model = new Model();
	model->meshes.append(*Plane);
	return model;
}

Model* ModelBuilder::CreateBox(QString name, float sizeX, float sizeY, float sizeZ, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CreateBox(QString name, glm::vec3 size, int subdivisionsX, int subdivisionsY, int subdivisionsZ)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CreateBox(QString name, glm::vec3 size, glm::vec3 subdivisions)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CreateCylinder(QString name, float radius, float height, int subdivisiomsAxis, int subdivisionsHeight)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CreateCone(QString name, float radius, float height, int subdivisionsAxis, int subdivisionsHeight)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CreateSphere(QString name, float radius, int subdivisionsAxis, int subdivisionsHeight)
{
	///TODO: implement it.
	return nullptr;
}

Model* ModelBuilder::CrateTorus(QString name, float radius, float segmentRadius, int subdivisionsAxis, int subdivisionsHeight)
{
	///TODO: implement it.
	return nullptr;
}
