#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Utills/Singleton.h>

#include "AbstractModelImporter.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for loading models using Open Asset Importer. This class is singleton.
	  */
	#pragma endregion
	class AssimpModelImporter : public AbstractModelImporter, public Singleton<AssimpModelImporter>
	{
	public:
		#pragma region documentation
		/**
		  * \brief AssimpModelImporter constructor.
		  */
		#pragma endregion
		AssimpModelImporter();
		#pragma region documentation
		/**
		* \brief AssimpModelImporter destructor.
		*/
		#pragma endregion
		~AssimpModelImporter();

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

	private:
		Assimp::Importer Importer;
	};

}