#pragma once
#include <QtCore/qlist.h>

#include "../Model.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Abstract class for importing models.
	  */
	#pragma endregion
	class AbstractModelImporter
	{
	public:
		#pragma region documentation
		/**
		  * \brief Abstract method for importing models from a file.
		  *
		  * @param name Name of the model to be set after importing.
		  * @param fileUrl Path to the model file.
		  * @return Loaded Model.
		  */
		#pragma endregion
		virtual Model* Load(QString name, QString fileUrl) = 0;

		#pragma region documentation
		/**
		  * \brief Gets list of file formats supported by given ModelImporter.
		  *
		  * @return List of file formats supported by given ModelImporter.
		  */
		#pragma endregion
		QList<QString> getSupportedExtensions();

	protected:
		#pragma region documentation
		/**
		  * \brief List of file formats supported by given ModelImporter.
		  */
		#pragma endregion
		QList<QString> supportedExtensions;
	};

}