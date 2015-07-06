#pragma once
#include <GL/glew.h>
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

class Shader;

class ShaderManager
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

	ShaderManager(void);
	~ShaderManager(void);

	Shader* getCurrentShader();
	void setCurrentShader(Shader* shader);

	void Load(Shader* shader, QString name);
	void Load(QString vertexShader, QString fragmentShader, QString name);

	void UseShader(QString name);
	void UseShader(Shader* shader);

private:
	QMap<QString, Shader*> shaders;
	Shader* currentShader;	//shader currently enabled on GPU

	void FlushShader(QString name);
};

