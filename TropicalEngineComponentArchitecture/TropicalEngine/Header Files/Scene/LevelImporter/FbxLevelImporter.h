#pragma once
#include <fbxsdk.h>

#include <Utills/Singleton.h>

#include "AbstractLevelImporter.h"

namespace TropicalEngine
{

	class FbxLevelImporter : public AbstractLevelImporter, public Singleton<FbxLevelImporter>
	{
	public:
		FbxLevelImporter();
		~FbxLevelImporter();

		Level* Load(QString name, QString fileUrl) override;

	private:
		FbxManager* SdkManager;
		FbxIOSettings* IOSettings;
		FbxGeometryConverter* Converter;
	};

}