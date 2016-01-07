#pragma once
#include <QtCore/qlist.h>

#include "../Model.h"

namespace TropicalEngine
{

	/**
	  * Abstract class for importing models.
	  */
	class AbstractModelImporter
	{
	public:
		/**
		  * \brief Abstract method for importing models from a file.
		  *
		  * @param name Name of the model to be set after importing.
		  * @param fileUrl Path to the model file.
		  * @return Loaded Model.
		  */
		virtual Model* Load(QString name, QString fileUrl) = 0;

		/**
		  * \brief Gets list of file formats supported by given ModelImporter.
		  *
		  * @return List of file formats supported by given ModelImporter.
		  */
		QList<QString> getSupportedExtensions();

	protected:

		/**
		  * \brief List of file formats supported by given ModelImporter.
		  */
		QList<QString> supportedExtensions;
	};

}