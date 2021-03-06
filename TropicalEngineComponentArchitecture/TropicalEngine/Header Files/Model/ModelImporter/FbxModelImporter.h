#pragma once
#include <fbxsdk.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	* \brief Class for loading models using FBX SDK. This class is singleton.
	*/
	#pragma endregion
	class FbxModelImporter : public AbstractModelImporter, public Singleton<FbxModelImporter>
	{
	public:
		#pragma region documentation
		/**
		  * \brief FbxModelImporter constructor.
		  */
		#pragma endregion
		FbxModelImporter();
		#pragma region documentation
		/**
		  * \brief FbxModelImporter destructor.
		  */
		#pragma endregion
		~FbxModelImporter();

		#pragma region documentation
		/**
		* \brief Imports models from a file.
		*
		* @param name Name of the model to be set after importing.
		* @param fileUrl Path to the model file.
		* @return Loaded Model.
		*/
		#pragma endregion
		Model* Load(QString name, QString fileUrl) override;

		#pragma region documentation
		/**
		  * \brief Import Model from FbxMesh object.
		  *
		  * @param name Name for Model.
		  * @param mesh Pointer to FbxMesh to create model from.
		  *
		  * @return Pointer to created Model.
		  */
		#pragma endregion
		Model* Load(QString name, class FbxMesh* mesh);

	private:
		FbxManager* SdkManager;
		FbxIOSettings* IOSettings;
		FbxGeometryConverter* Converter;
	};

}