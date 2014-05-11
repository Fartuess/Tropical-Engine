#pragma once
//#include "_Shader.h"
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Shader;

class ShaderManager :
	public Singleton<ShaderManager>
{
private:
	QMap<QString, Shader*> shaders;

	ShaderManager(void);
public:
	~ShaderManager(void);
private:
	void FlushShader(QString name);
public:
	void Load(Shader* shader, QString name);
	void Load(QString vertexShader, QString fragmentShader, QString name);
};

