#pragma once
#include <GL\glew.h>
#include <glm.hpp>

class Level;
class Shader;

class OglDevTut03
{
private:
	GLuint VBO;
	GLuint cameraLocation;
	Shader* simple;
public:
	static glm::vec2 cameraPosition;
	
public:
	static Level* level;

	void Initialize();
	void Draw();

	void InitializeLevel();
};