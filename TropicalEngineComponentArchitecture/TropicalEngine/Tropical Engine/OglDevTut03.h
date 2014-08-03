#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qobject.h>
#include <QtCore\qtime>

class Level;
class Shader;
class Model;

class OglDevTut03 : public QObject
{
	Q_OBJECT
private:
	int deltaTime;
	QTime deltaTimer;
public:
	static Level* level;

	void InitializeLevel();

public slots:
	void Initialize();
	void Draw();
};