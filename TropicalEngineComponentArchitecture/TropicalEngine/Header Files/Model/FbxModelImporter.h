#pragma once

#include <fbxsdk.h>

#include "Utills/Singleton.h"

#include <Model/AbstractModelImporter.h>

class FbxModelImporter : public AbstractModelImporter, public Singleton<FbxModelImporter>
{
public:
	FbxModelImporter();
	~FbxModelImporter();

	/*
	 * Requires splitted vertices on normals and uvs to work.
	 */
	virtual Model* Load(QString name, QString fileUrl) override;

private:
	FbxManager* SdkManager;
	FbxIOSettings* IOSettings;
};

