#pragma once
#include "Scene\Level.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class LevelManager
{
public:
	friend class Level;
private:
	QMap<QString, Level> levels;
public:
	LevelManager(void);
	~LevelManager(void);

	void LoadLevel(QString fileUrl, QString name);
private:
	void FlushLevel(QString name);
};

