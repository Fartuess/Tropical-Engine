#pragma once
#include <gl\glew.h>
#include <glm.hpp>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec2 texCoord;

	Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec3& bitangent, const glm::vec2& texCoord)
	{
		this->position = position;
		this->normal = normal;
		this->tangent = tangent;
		this->bitangent = bitangent;
		this->texCoord = texCoord;
	}

	Vertex()
	{
		this->position = glm::vec3(0.0f, 0.0f, 0.0f);
		this->normal = glm::vec3(0.0f, 0.0f, 1.0f);
		this->tangent = glm::vec3(0.0f, 1.0f, 0.0f);
		this->bitangent = glm::vec3(1.0f, 0.0f, 0.0f);
		this->texCoord = glm::vec2(0.0f, 0.0f);
	}
};

class Model
{
private:
	//GLuint numberVerticies;
	//
	//GLuint vertexVBO;
	//GLuint normalVBO;
	//GLuint tangentVBO;
	//GLuint bitangentVBO;
	//GLuint texcoordVBO;
public:
	Model();
	Model(QString fileUrl);
	~Model(void);

	struct MeshEntry {
        MeshEntry();

        ~MeshEntry();

        //void Init(const std::vector<Vertex>& Vertices,
        //          const std::vector<unsigned int>& Indices);

        GLuint VertexBuffer;
        GLuint IndexBuffer;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

	QVector<MeshEntry> meshes;
	uint materialCount;
};

