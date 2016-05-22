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

		Level* LoadLevel(QString fileUrl, QString name);

		static void AddImporter(class AbstractLevelImporter* importer);

	private:
		QHash<QString, Level*> levels;

		static QHash<QString, class AbstractLevelImporter*> supportedExtensions;

		void FlushLevel(QString name);
	};

}