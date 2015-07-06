#pragma once
#include "Scene/Level.h"
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

class LevelManager
{
public:
	friend class Level;

	LevelManager(void);
	~LevelManager(void);

	void LoadLevel(QString fileUrl, QString name);

private:
	QMap<QString, Level> levels;

	void FlushLevel(QString name);
};

