#pragma once
#include <GL/glew.h>
#include <glm.hpp>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>

#include <Serialization/ISerializableJSON.h>

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

	GLuint NumVertex;
    //GLuint NumIndices;
    GLuint MaterialIndex;	//what for?

	//GLuint VBOs[2];

	///TODO: Make finalization supporting flexible sets of arrays.
	void Finalize(	QVector<glm::vec4>& vertices,
					QVector<glm::vec3>& normals,
					QVector<glm::vec3>& tangents,
					QVector<glm::vec3>& bitangents,
					QVector<glm::vec2>& texCoords);
private:
	bool isFinalized = false;
};

class Model : public ISerializableJSON
{
public:
	QString getName();
	void setName(QString name);

	Model(QString name);
	Model(QString name, QString fileUrl);
	~Model(void);

	QVector<MeshEntry> meshes;
	GLuint materialCount;

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	QString name;
	QString fileUrl;
};

