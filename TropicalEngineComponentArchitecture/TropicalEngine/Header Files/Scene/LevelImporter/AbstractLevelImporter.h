#pragma once
#include <QtCore/qlist.h>

#include "../Level.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Abstract class for importing levels.
	  */
	#pragma endregion
	class AbstractLevelImporter
	{
	public:
		#pragma region documentation
		/**
		  * \brief Loads Level from a file.
		  *
		  * @param name Name for the Level.
		  * @param fileUrl Path to the file to load Level from.
		  *
		  * @return Pointer to loaded Level.
		  */
		#pragma endregion
		virtual Level* Load(QString name, QString fileUrl) = 0;

		#pragma region documentation
		/**
		  * \brief Gets list of supported formats.
		  *
		  * @return List of supported formats.
		  */
		#pragma endregion
		QList<QString> getSupportedExtensions();

	protected:
		QList<QString> supportedExtensions;
	};

}