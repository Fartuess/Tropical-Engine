#pragma once
#include <fbxsdk.h>

#include <Utills/Singleton.h>

#include "AbstractLevelImporter.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for loading levels using FBX SDK.
	  */
	#pragma endregion
	class FbxLevelImporter : public AbstractLevelImporter, public Singleton<FbxLevelImporter>
	{
	public:
		#pragma region documentation
		/**
		  * \brief Constructor for importer.
		  */
		#pragma endregion
		FbxLevelImporter();
		#pragma region documentation
		/**
		  * \brief Destructor for importer.
		  */
		#pragma endregion
		~FbxLevelImporter();

		#pragma region documentation
		/**
		  * \brief Loads Level from a file.
		  *
		  * @param name Name for the Level.
		  * @param fileUrl Path to the file to load Level from.
		  *
		  * @return Pointer to loaded Level.
		  */
		#pragma endregion
		Level* Load(QString name, QString fileUrl) override;

	private:
		FbxManager* SdkManager;
		FbxIOSettings* IOSettings;
		FbxGeometryConverter* Converter;
	};

}