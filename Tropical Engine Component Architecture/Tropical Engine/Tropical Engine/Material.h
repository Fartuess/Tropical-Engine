#pragma once
class Shader;

class Material
{
private:
	Shader* shader;
public:
	Material(Shader* shader, void* params, QString name);	//temp declaration
	~Material(void);

	Shader* getShader();
};

