#include <QtCore/qdebug.h>
#include <QtGui/qimagereader.h>

#include <Texture/TextureManager.h>
#include <Shader/MaterialManager.h>

#include "TropicalEngineApplication.h"

TextureManager::TextureManager(void)
{
	textureIterator = 0;

	//foreach(QByteArray it, QImageReader::supportedImageFormats())
	//{
	//	qDebug() << QString(it);
	//}
}

TextureManager::~TextureManager(void)
{
	for (Material* material : TropicalEngineApplication::instance()->materialManager->materials)
	{
		///TODO: set all textures to null texture;
	}
}

int TextureManager::getTextureIterator()
{
	return textureIterator;
}

void TextureManager::incrementTextureIterator()
{
	textureIterator++;
}

void TextureManager::resetTextureIterator()
{
	textureIterator = 0;
}

Texture* const TextureManager::getTexture(QString name)
{
	return textures[name];
}

Texture* TextureManager::Load(QString name, QString fileUrl)
{
	Texture* newTexture = new Texture(fileUrl, name);
	textures.insert(name, newTexture);

	return newTexture;
}

void TextureManager::FlushTexture(QString name, bool forced)
{
	if (!textures.contains(name))
		return;
	if (forced)
	{
		delete TextureManager::textures[name];
	}
	else
	{
		for (Material* material : TropicalEngineApplication::instance()->materialManager->materials)
		{
			///TODO: if material uses texture isUsed return;
		}
		delete TextureManager::textures[name];
	}
}
