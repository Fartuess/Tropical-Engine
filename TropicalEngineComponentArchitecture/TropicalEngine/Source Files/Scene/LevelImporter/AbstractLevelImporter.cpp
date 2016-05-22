#include <Scene/LevelImporter/AbstractLevelImporter.h>

namespace TropicalEngine
{

	QList<QString> AbstractLevelImporter::getSupportedExtensions()
	{
		return supportedExtensions;
	}

}