#pragma once
#include <fbxsdk.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

namespace TropicalEngine
{

	/**
	* Class for loading models using FBX SDK. This class is singleton.
	*/
	class FbxModelImporter : public AbstractModelImporter, public Singleton<FbxModelImporter>
	{
	public:

		FbxModelImporter();
		~FbxModelImporter();

		/**
		* \brief Imports models from a file.
		*
		* @param name Name of the model to be set after importing.
		* @param fileUrl Path to the model file.
		* @return Loaded Model.
		*/
		Model* Load(QString name, QString fileUrl) override;

	private:
		FbxManager* SdkManager;
		FbxIOSettings* IOSettings;
		FbxGeometryConverter* Converter;
	};

}