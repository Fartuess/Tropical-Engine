#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include <Utills/Singleton.h>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);

	int getTextureIterator();
	void incrementTextureIterator();
	void resetTextureIterator();

	Texture* const getTexture(QString name);
	Texture* operator[](QString name)	{ return textures[name]; };
	Texture* const operator[](QString name)	const	{ return textures[name]; };

	Texture* Load(QString name, QString fileUrl);
private:
	QMap<QString, Texture*> textures;
	int textureIterator;	//for iterating over GL_TEXTUREs

	void FlushTexture(QString name, bool forced = false);
};

