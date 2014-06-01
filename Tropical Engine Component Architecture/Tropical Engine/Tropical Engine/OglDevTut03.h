#pragma once
#include <GL\glew.h>

class Level;
class Shader;

class OglDevTut03
{
private:
	GLuint VBO;
	Shader* simple;
	
public:
	static Level* level;

	void Initialize();
	void Draw();

	void InitializeLevel();
};