#include <gl/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <QtCore/qvector.h>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include "Model/Model.h"
#include "Model/ModelBuilder.h"

#include <QtCore/qdebug.h>

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
    }
	return model;
}

///TODO: Figure out if it is still needed.
void ModelBuilder::CalculateTangentsBitangents(QVector<glm::vec4>& vertices, QVector<glm::vec3>& normals, QVector<glm::vec2>& texcoords, QVector<glm::vec3>& out_tangents, QVector<glm::vec3>& out_bitangents)
{
	for (unsigned int i=0; i<vertices.size(); i+=3 ){

		// Shortcuts for vertices
		glm::vec3 & v0 = glm::vec3(vertices[i+0]);
		glm::vec3 & v1 = glm::vec3(vertices[i+1]);
		glm::vec3 & v2 = glm::vec3(vertices[i+2]);

		// Shortcuts for UVs
		glm::vec2 & uv0 = texcoords[i+0];
		glm::vec2 & uv1 = texcoords[i+1];
		glm::vec2 & uv2 = texcoords[i+2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1-v0;
		glm::vec3 deltaPos2 = v2-v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1-uv0;
		glm::vec2 deltaUV2 = uv2-uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

		///TODO: look at comment below and finish implementation!
		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);

		// Same thing for binormals
		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);

	}

	// See "Going Further"
	for (unsigned int i=0; i<vertices.size(); i+=1 )
	{
		glm::vec3 & n = normals[i];
		glm::vec3 & t = out_tangents[i];
		glm::vec3 & b = out_bitangents[i];
		
		// Gram-Schmidt orthogonalize
		t = glm::normalize(t - n * glm::dot(n, t));
		
		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f){
			t = t * -1.0f;
		}

	}
}