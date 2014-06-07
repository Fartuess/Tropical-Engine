#pragma once
#include "singleton.h"
#include <GL\glew.h>
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Shader;

class ShaderManager// :
	//public Singleton<ShaderManager>
{
public:
	struct shaderProgram
	{
		GLuint program;

		GLuint computeShader;
		GLuint vertexShader;
		GLuint controlTessalationShader;
		GLuint evaluationTessalationShader;
		GLuint geometryShader;
		GLuint fragmentShader;
	};
private:
	QMap<QString, Shader*> shaders;
public:
	ShaderManager(void);
	~ShaderManager(void);
private:
	void FlushShader(QString name);
public:
	void Load(Shader* shader, QString name);
	void Load(QString vertexShader, QString fragmentShader, QString name);

	void UseShader(QString name);
	void UseShader(Shader* shader);
};

