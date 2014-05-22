#pragma once
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Level;

class SceneManager:
	public Singleton<SceneManager>
{
private:
	QMap<QString, Level*> levels;
public:
	SceneManager(void);
	~SceneManager(void);

	void LoadLevel(QString fileUrl);
	void LoadLevel(QString fileUrl, QString name);
	void LoadLevel(Level* level, QString name);
	void UnloadLevel(QString name);
};