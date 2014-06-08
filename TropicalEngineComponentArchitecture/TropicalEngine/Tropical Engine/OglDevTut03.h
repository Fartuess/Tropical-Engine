#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qobject.h>

class Level;
class Shader;
class Model;

class OglDevTut03 : public QObject
{
	Q_OBJECT
private:
	GLuint VBO;
	GLuint cameraLocation;
	GLuint lightLocation;
	Shader* simple;

	Model* triangleModel;
public:
	static glm::vec2 cameraPosition;
	static glm::vec3 lightVector;
public:
	static Level* level;

	void InitializeLevel();

public slots:
	void Initialize();
	void Draw();
};