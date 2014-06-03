#pragma once
#include <GL\glew.h>
#include <QtCore\qstring.h>
#include "Material.h"

//class Material;

class Shader
{
public:
	Material defaultMaterial;
public:	//temporarily
	GLuint shaderProgram;
private:
	GLuint vertexLocation;
	GLuint normalLocation;
	GLuint tangentLocation;
	GLuint bitangentLocation;
	GLuint texcoordLocation;

	GLuint modelMatrixLocation;
	GLuint normalMatrixLocation;
	GLuint cameraMatrixLocation;
public:
	static Shader* nullShader;

	Shader(QString vertexShader, QString fragmentShader, QString name);
	~Shader(void);

	GLuint getShaderProgram();
	GLuint getVertexLocation();
	GLuint getNormalLocation();
	GLuint getTangentLocation();
	GLuint getBitangentLocation();
	GLuint getTexcoordLocation();

	GLuint getModelMatrixLocation();
	GLuint getNormalMatrixLocation();
	GLuint getCameraMatrixLocation();
private:
	void AddShader(QString shaderFile, GLenum shaderType);
};