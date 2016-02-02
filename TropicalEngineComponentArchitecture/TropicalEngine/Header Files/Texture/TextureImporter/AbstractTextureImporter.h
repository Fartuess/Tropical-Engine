#pragma once

#include <QtCore/qlist.h>

#include "../Texture.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Abstract class for importing textures.
	  */
	#pragma endregion
	class AbstractTextureImporter
	{
	public:
		#pragma region documentation
		/**
		  * \brief Abstract method for importing textures from a file.
		  *
		  * @param name Name of the texture to be set after importing.
		  * @param fileUrl Path to the texture file.
		  * @param textureTarget Texture object to load data to. If left default at nullptr loader will create new Texture object.
		  * @return Loaded Texture.
		  */
		#pragma endregion
		virtual Texture* Load(QString name, QString fileUrl, Texture* textureTarget = nullptr) = 0;

		#pragma region documentation
		/**
		  * \brief Gets list of file formats supported by given TextureImporter.
		  *
		  * @return List of file formats supported by given TextureImporter.
		  */
		#pragma endregion
		QList<QString> getSupportedExtensions();

	protected:
		#pragma region documentation
		/**
		  * \brief List of file formats supported by given TextureImporter.
		  */
		#pragma endregion
		QList<QString> supportedExtensions;

		#pragma region documentation
		/**
		  * \brief Gives TextureImporters access to encapsulated constructor of Texture class;
		  */
		#pragma endregion
		Texture* spawnTexture(QString name);
	};

}