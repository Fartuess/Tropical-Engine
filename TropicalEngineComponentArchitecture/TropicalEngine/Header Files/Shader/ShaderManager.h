#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

class Shader;

class ShaderManager
{
public:

	friend class Shader;

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

	Shader* const getCurrentShader();
	void setCurrentShader(Shader* shader);
	Shader* const getShader(QString name);

	Shader* operator[](QString name)      { return shaders[name]; };
	const Shader* operator[](QString name) const { return shaders[name]; };

	Shader* Load(QString name, QString vertexShader, QString fragmentShader);

	void UseShader(QString name);
	void UseShader(Shader* shader);

protected:
	QMap<QString, Shader*> shaders;
	Shader* currentShader;	//shader currently enabled on GPU

	void Load(Shader* shader, QString name);
	void FlushShader(QString name);
};

