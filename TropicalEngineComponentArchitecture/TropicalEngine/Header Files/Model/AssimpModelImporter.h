#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

class AssimpModelImporter : public AbstractModelImporter, public Singleton<AssimpModelImporter>
{
public:
	AssimpModelImporter();
	~AssimpModelImporter();

	virtual Model* Load(QString name, QString fileUrl) override;

private:
	Assimp::Importer Importer;
};

