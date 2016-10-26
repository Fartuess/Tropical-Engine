#pragma once
#include <Texture/TextureImporter/AbstractTextureImporter.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for importing textures using Qt framework.
	  *
	  * Supports multiple formats including jpg, png, tga (without rle), bmp.
	  */
	#pragma endregion

	class QtTextureImporter : public AbstractTextureImporter, public Singleton<QtTextureImporter>
	{
	public:
		#pragma region documentation
		/**
		  * \brief Constructor. Registers this importer as importer for jpg, png, tga and bmp formats.
		  */
		#pragma endregion
		QtTextureImporter();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~QtTextureImporter();

		#pragma region documentation
		/**
		  * \brief Method for importing textures from a file.
		  *
		  * @param name Name of the texture to be set after importing.
		  * @param fileUrl Path to the texture file.
		  * @param textureTarget Texture object to load data to. If left default at nullptr loader will create new Texture object.
		  * @return Loaded Texture.
		  */
		#pragma endregion
		virtual Texture* Load(QString name, QString fileUrl, Texture* textureTarget = nullptr) override;

		#pragma region documentation
		/**
		  * \brief Method for creating TextureData from a file.
		  *
		  * @param fileUrl Path to the texture file.
		  * @param flipY Defines if resulted image should be flipped along the Y axis.
		  *
		  * @return TextureData object containing informations from the file.
		  */
		#pragma endregion
		virtual TextureData* LoadData(QString fileUrl, bool flipY = false) override;
	};

}