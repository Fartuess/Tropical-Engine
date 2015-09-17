#include <Model/ModelImporter/AbstractModelImporter.h>

QList<QString> AbstractModelImporter::getSupportedExtensions()
{
	return supportedExtensions;
}