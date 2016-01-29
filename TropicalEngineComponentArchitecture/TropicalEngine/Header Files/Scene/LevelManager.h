#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Level.h"

namespace TropicalEngine
{

	// TODO: Currently LevelManager class is doing nothing. Figure out if it should be deleted. 
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