#pragma once
#include "_Texture.h"
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>
class TextureManager :
	public Singleton<TextureManager>
{
private:
	QMap<QString, Texture*> textures;
public:
	TextureManager(void);
	~TextureManager(void);

	void Load(QString name, QString fileUrl);
private:
	void FlushTexture(QString name, bool forced = false);
};

