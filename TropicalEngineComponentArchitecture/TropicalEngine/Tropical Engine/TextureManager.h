#pragma once
#include "Texture.h"
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>
class TextureManager// :
	//public Singleton<TextureManager>
{
private:
	QMap<QString, Texture*> textures;
	int textureIterator;	//for iterating over GL_TEXTUREs
public:
	TextureManager(void);
	~TextureManager(void);

	int getTextureIterator();
	void incrementTextureIterator();
	void resetTextureIterator();

	void Load(QString name, QString fileUrl);
private:
	void FlushTexture(QString name, bool forced = false);
};

