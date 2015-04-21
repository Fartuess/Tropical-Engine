#pragma once
#include <GL\glew.h>
#include <QtCore\qstring.h>
#include <QtCore\qvector.h>
#include <QtCore\qmap.h>
#include "Shader\Material.h"
#include "Serialization/ISerializableToXML.h"

class Shader : public ISerializableToXML, public ISerializableToJSON
{
private:
	QString name;
public:
	Material* defaultMaterial;
public:	//temporarily
	GLuint shaderProgram;
	QMap<QString, GLuint> subprograms;	///TODO: Value is shader type from now. Not it's address in GPU?
private:
	GLuint vertexLocation;
	GLuint normalLocation;
	GLuint tangentLocation;
	GLuint bitangentLocation;
	GLuint texcoordLocation;

	GLuint modelMatrixLocation;
	GLuint normalMatrixLocation;
	GLuint cameraPositionLocation;
	GLuint cameraMatrixLocation;
	GLuint projectionMatrixLocation;
public:	//temporarily
	GLuint dirLightVectorLocation;
	GLuint dirLightColorLocation;
	GLuint dirLightBrightnessLocation;
	GLuint dirLightAmbientLocation;

	QVector<GLuint> pointLightPositionLocations;
	QVector<GLuint> pointLightColorLocations;
	QVector<GLuint> pointLightBrightnessLocations;
	QVector<GLuint> pointLightRadiusLocations;
	QVector<GLuint> pointLightAttenuationLocations;

	GLuint drawingMode;

public:
	static Shader* nullShader;
private:
	QMap<QString, QPair<GLenum, GLuint>>* materialParameters;
	Material* currentMaterial;
public:
	Shader(QString vertexShader, QString fragmentShader, QString name);
	Shader(QMap<QString, GLuint> subshaders, QString name);
	~Shader(void);

	void setUpLightParameters();
	void setUpMaterialParameters();

	QString getName();
	void setName(QString name);

	GLuint getShaderProgram();
	GLuint getVertexLocation();
	GLuint getNormalLocation();
	GLuint getTangentLocation();
	GLuint getBitangentLocation();
	GLuint getTexcoordLocation();

	GLuint getModelMatrixLocation();
	GLuint getNormalMatrixLocation();
	GLuint getCameraPositionLocation();
	GLuint getCameraMatrixLocation();
	GLuint getProjectionMatrixLocation();

	GLenum getParameterType(QString name);
	GLuint getParameterLocation(QString name);
	const QMap<QString, QPair<GLenum, GLuint>>& getMaterialParameters();

	Material* getCurrentMaterial();
private:
	QString PreprocessShaderFile(QString shaderFile);
	void AddShader(QString shaderFile, GLenum shaderType);
public:
	void Use();

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
};