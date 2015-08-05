#include "Model/AbstractModelImporter.h"


AbstractModelImporter::AbstractModelImporter()
{
}


AbstractModelImporter::~AbstractModelImporter()
{
}

QList<QString> AbstractModelImporter::getSupportedExtensions()
{
	return supportedExtensions;
}