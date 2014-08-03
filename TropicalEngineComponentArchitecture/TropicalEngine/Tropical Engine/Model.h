#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>
#include "ISerializableToXML.h"

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

class Model : public ISerializableToXML
{
public:
	QString name;	///TODO: should not be public. Should have getters and setters, because changing internal name doesn't change name in model manager
private:
	QString fileUrl;
public:
	Model(QString name);
	Model(QString name, QString fileUrl);
	~Model(void);

	QVector<MeshEntry> meshes;
	GLuint materialCount;

	QString toXML() override;
};

