#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>

//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec3 normal;
//	glm::vec3 tangent;
//	glm::vec3 bitangent;
//	glm::vec2 texCoord;
//
//	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec3& bitangent, const glm::vec2& texCoord)
//	{
//		this->position = position;
//		this->normal = normal;
//		this->tangent = tangent;
//		this->bitangent = bitangent;
//		this->texCoord = texCoord;
//	}
//
//	Vertex()
//	{
//		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
//		this->normal = glm::vec3(0.0f, 0.0f, 1.0f);
//		this->tangent = glm::vec3(0.0f, 1.0f, 0.0f);
//		this->bitangent = glm::vec3(1.0f, 0.0f, 0.0f);
//		this->texCoord = glm::vec2(0.0f, 0.0f);
//	}
//};

class MeshEntry
{
public:
    MeshEntry();

    ~MeshEntry();

	GLuint vertexVBO;
	GLuint normalVBO;
	GLuint tangentVBO;
	GLuint bitangentVBO;
	GLuint texcoordVBO;

	GLuint VAO;

	GLuint NumVertex;
    //GLuint NumIndices;
    GLuint MaterialIndex;

	//QVector<glm::vec3>* testVertices;
	GLuint VBOs[2];

};

class Model
{
private:
	//GLuint numberVerticies;
	//QString name;
public:
	Model(QString name);
	Model(QString name, QString fileUrl);
	~Model(void);

	QVector<MeshEntry> meshes;
	GLuint materialCount;
};

