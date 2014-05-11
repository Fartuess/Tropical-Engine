#pragma once
#include <QtCore\qstring.h>
#include "Material.h"

//class Material;

class Shader
{
public:
	Material defaultMaterial;

	static Shader* nullShader;

	Shader(QString vertexShader, QString fragmentShader, QString name);
	~Shader(void);
};