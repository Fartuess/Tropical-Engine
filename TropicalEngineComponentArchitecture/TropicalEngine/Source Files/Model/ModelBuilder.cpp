#include <gl/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <QtCore/qvector.h>
#include <QtCore/qstring.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qdebug.h>

#include <Model/Model.h>
#include <Model/ModelBuilder.h>
#include <Model/AssimpModelImporter.h>
#include <Model/FbxModelImporter.h>

QMap<QString, AbstractModelImporter*> ModelBuilder::supportedExtensions = QMap<QString, AbstractModelImporter*>();

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
	/// TODO: there is case of unsupported type to be handled.
	/// TODO: try to initialize importers automatically in a way that they work like plugins.

	return supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl);
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

void ModelBuilder::AddImporter(AbstractModelImporter* importer)
{
	for (QString extensionName : importer->getSupportedExtensions())
	{
		supportedExtensions[extensionName] = importer;
	}
}