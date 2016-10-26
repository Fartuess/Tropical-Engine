#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Level.h"

namespace TropicalEngine
{
	#pragma region documentation
	/**
	  * \brief Class for managing Levels.
	  */
	#pragma endregion
	class LevelManager
	{
	public:
		friend class Level;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		LevelManager(void);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~LevelManager(void);

		#pragma region documentation
		/**
		  * \brief Loads level from a file.
		  *
		  * @param fileUrl Path to the file to load.
		  * @param name Name of the Level to set.
		  *
		  * @return Pointer to loaded Level.
		  */
		#pragma endregion
		Level* LoadLevel(QString fileUrl, QString name);

		#pragma region documentation
		/**
		  * \brief Registers LevelImporter.
		  *
		  * @param importer Importer to register.
		  */
		#pragma endregion
		static void AddImporter(class AbstractLevelImporter* importer);

	private:
		QHash<QString, Level*> levels;

		static QHash<QString, class AbstractLevelImporter*> supportedExtensions;

		void FlushLevel(QString name);
	};

}