#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include <Utills/Singleton.h>

#include "Texture.h"

namespace TropicalEngine
{

	/**
	  * Class for managing textures.
	  */
	class TextureManager
	{
	public:
		/**
		  * \brief Default constructor.
		  */
		TextureManager(void);

		/**
		  * \brief Default destructor.
		  */
		~TextureManager(void);

		int getTextureIterator();
		void incrementTextureIterator();
		void resetTextureIterator();

		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		Texture* const getTexture(QString name);

		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		Texture* operator[](QString name)	{ return textures[name]; };

		/**
		  * \brief Gets Texture by name.
		  *
		  * @param name Name of Texture to look for.
		  * @return Found Texture.
		  */
		Texture* const operator[](QString name)	const	{ return textures[name]; };

		/**
		  * \brief Loads Texture from a file.
		  *
		  * @param name Name to be set for loaded Texture.
		  * @param fileUrl Path to file.
		  */
		Texture* Load(QString name, QString fileUrl);
	private:
		QHash<QString, Texture*> textures;
		int textureIterator;	//for iterating over GL_TEXTUREs

		void FlushTexture(QString name, bool forced = false);
	};

}