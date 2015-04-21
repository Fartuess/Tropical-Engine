#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

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

	void Finalize();
};

class Model : public ISerializableToXML, public ISerializableToJSON
{
private:
	QString name;
public:
	QString getName();
	void setName(QString name);
private:
	QString fileUrl;
public:
	Model(QString name);
	Model(QString name, QString fileUrl);
	~Model(void);

	QVector<MeshEntry> meshes;
	GLuint materialCount;

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
};

