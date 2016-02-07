#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include <Utills/Singleton.h>

#include "Texture.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing textures.
	  */
	#pragma endregion
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		friend class Texture;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		TextureManager(void);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~TextureManager(void);

		int getTextureIterator();
		void incrementTextureIterator();
		void resetTextureIterator();

		#pragma region documentation
		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		#pragma endregion
		Texture* const getTexture(QString name);
		#pragma region documentation
		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		#pragma endregion
		Texture* operator[](QString name)	{ return textures[name]; };
		#pragma region documentation
		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		#pragma endregion
		Texture* const operator[](QString name)	const	{ return textures[name]; };
		#pragma region documentation
		/**
		  * \brief Loads Texture from a file.
		  *
		  * @param name Name to be set for loaded Texture.
		  * @param fileUrl Path to file.
		  */
		#pragma endregion
		Texture* Load(QString name, QString fileUrl);

		#pragma region documentation
		/**
		  * \brief Adds support of specific importer for TextureManager.
		  *
		  * @param importer Importer to support.
		  */
		#pragma endregion
		static void AddImporter(class AbstractTextureImporter* importer);
	private:
		QHash<QString, Texture*> textures;
		int textureIterator;	//for iterating over GL_TEXTUREs

		static QHash<QString, class AbstractTextureImporter*> supportedExtensions;

		void FlushTexture(QString name, bool forced = false);

		Texture* Load(QString name, QString fileUrl, Texture* textureTarget);
	};

}