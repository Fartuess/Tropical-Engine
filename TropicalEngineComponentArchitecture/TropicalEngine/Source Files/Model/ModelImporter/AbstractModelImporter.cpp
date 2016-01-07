#include <Model/ModelImporter/AbstractModelImporter.h>

namespace TropicalEngine
{

	QList<QString> AbstractModelImporter::getSupportedExtensions()
	{
		return supportedExtensions;
	}

}