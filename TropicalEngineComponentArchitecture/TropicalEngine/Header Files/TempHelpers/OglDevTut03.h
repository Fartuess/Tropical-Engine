#pragma once
#include <GL/glew.h>
#include <glm.hpp>

#include <QtCore/qobject.h>
#include <QtCore/qtime>

class OglDevTut03 : public QObject	///TODO: Get rid of this class.
{
	Q_OBJECT
public:
	static class Level* level;

	void InitializeLevel();

public slots:
	void Initialize();	//Not used anymore
	void Draw();		//Not used anymore

private:
	int deltaTime;
	QTime deltaTimer;
};