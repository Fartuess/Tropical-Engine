#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <QtCore\qobject.h>
#include <QtCore\qtime>

class Level;
class Shader;
class Model;

class OglDevTut03 : public QObject	///TODO: Get rid of this class.
{
	Q_OBJECT
private:
	int deltaTime;
	QTime deltaTimer;
public:
	static Level* level;

	void InitializeLevel();

public slots:
	void Initialize();	//Not used anymore
	void Draw();		//Not used anymore
};