#pragma once
#include <glm.hpp>

class Shader;

class Material
{
	struct MaterialProperties
	{
	    glm::vec4 ambientColor;
	    glm::vec4 diffuseColor;
	    glm::vec4 specularColor;
	    GLfloat specularExponent;
	};

private:
	Shader* shader;
public:
	MaterialProperties properties;

	Material(Shader* shader, void* params, QString name);	//temp declaration
	~Material(void);

	Shader* getShader();
};

