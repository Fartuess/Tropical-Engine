#pragma once
#include <fbxsdk.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

class FbxModelImporter : public AbstractModelImporter, public Singleton<FbxModelImporter>
{
public:
	FbxModelImporter();
	~FbxModelImporter();

	Model* Load(QString name, QString fileUrl) override;

private:
	FbxManager* SdkManager;
	FbxIOSettings* IOSettings;
	FbxGeometryConverter* Converter;
};

