#pragma once
#include <GL\glew.h>
#include <QtCore\qstring.h>
#include "Material.h"

//class Material;

class Shader
{
public:


	Material defaultMaterial;
private:
	GLuint shaderProgram;
	GLuint vertexLocation;
	GLuint normalLocation;
	GLuint tangentLocation;
	GLuint bitangentLocation;
	GLuint texcoordLocation;
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
private:
	void AddShader(QString shaderFile, GLenum shaderType);
};