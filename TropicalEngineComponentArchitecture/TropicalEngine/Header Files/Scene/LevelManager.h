#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include "Level.h"

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

