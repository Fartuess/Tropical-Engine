#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Level.h"

namespace TropicalEngine
{

	class LevelManager
	{
	public:
		friend class Level;

		LevelManager(void);
		~LevelManager(void);

		void LoadLevel(QString fileUrl, QString name);

	private:
		QHash<QString, Level> levels;

		void FlushLevel(QString name);
	};

}