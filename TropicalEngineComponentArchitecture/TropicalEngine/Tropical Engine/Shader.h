#pragma once
#include <GL\glew.h>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>
#include <QtCore\qmap.h>
#include "Material.h"
#include "ISerializableToXML.h"

class Shader : public ISerializableToXML
{
public:
	QString name;	///TODO: should not be public. Should have getters and setters, because changing internal name doesn't change name in shader manager
	Material* defaultMaterial;
public:	//temporarily
	GLuint shaderProgram;
	QVector<GLuint>* subprograms;	//is it needed?
private:
	GLuint vertexLocation;
	GLuint normalLocation;
	GLuint tangentLocation;
	GLuint bitangentLocation;
	GLuint texcoordLocation;

	GLuint modelMatrixLocation;
	GLuint normalMatrixLocation;
	GLuint cameraMatrixLocation;
public:	//temporarily
	GLuint dirLightVectorLocation;
	GLuint dirLightColorLocation;
	GLuint dirLightBrightnessLocation;
	GLuint dirLightAmbientLocation;
public:
	static Shader* nullShader;
private:
	QMap<QString, QPair<GLenum, GLuint>>* materialParameters;
	Material* currentMaterial;
public:
	Shader(QString vertexShader, QString fragmentShader, QString name);
	Shader(QMap<QString, GLuint> subshaders, QString name);
	~Shader(void);

	void setUpMaterialParameters();

	GLuint getShaderProgram();
	GLuint getVertexLocation();
	GLuint getNormalLocation();
	GLuint getTangentLocation();
	GLuint getBitangentLocation();
	GLuint getTexcoordLocation();

	GLuint getModelMatrixLocation();
	GLuint getNormalMatrixLocation();
	GLuint getCameraMatrixLocation();

	GLenum getParameterType(QString name);
	GLuint getParameterLocation(QString name);
	const QMap<QString, QPair<GLenum, GLuint>>& getMaterialParameters();

	Material* getCurrentMaterial();
private:
	void AddShader(QString shaderFile, GLenum shaderType);
public:
	void Use();

	QString toXML() override;
};