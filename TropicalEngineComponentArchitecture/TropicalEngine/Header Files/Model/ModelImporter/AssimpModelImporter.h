#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

/**
  * Class for loading models using Open Asset Importer. This class is singleton.
  */
class AssimpModelImporter : public AbstractModelImporter, public Singleton<AssimpModelImporter>
{
public:

	//friend class Singleton;

	/**
	* \brief Imports models from a file.
	*
	* @param name Name of the model to be set after importing.
	* @param fileUrl Path to the model file.
	* @return Loaded Model.
	*/
	Model* Load(QString name, QString fileUrl) override;

	AssimpModelImporter();
	~AssimpModelImporter();

private:
	Assimp::Importer Importer;
};

