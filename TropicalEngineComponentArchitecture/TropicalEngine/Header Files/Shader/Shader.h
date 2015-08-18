#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableToJSON.h>

#include "Material.h"

class Shader : public ISerializableToJSON
{
public:
	Material* defaultMaterial;

	//temporarily public
	GLuint shaderProgram;
	QMap<QString, GLuint> subprograms;	///TODO: Value is shader type from now. Not it's address in GPU?

	//temporarily public
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

	static Shader* nullShader;

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

	void Use();

	QString getTypeName() override;
	QJsonObject toJSON() override;

private:
	QString name;

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

	QMap<QString, QPair<GLenum, GLuint>>* materialParameters;
	Material* currentMaterial;

	QString PreprocessShaderFile(QString shaderFile);
	void AddShader(QString shaderFile, GLenum shaderType);
};