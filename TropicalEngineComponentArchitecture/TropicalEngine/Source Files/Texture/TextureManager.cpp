#include <QtCore/qdebug.h>
#include <QtGui/qimagereader.h>

#include <Texture/TextureManager.h>
#include <Texture/TextureImporter/AbstractTextureImporter.h>

#include <Shader/MaterialManager.h>

namespace TropicalEngine
{
	QHash<QString, AbstractTextureImporter*> TextureManager::supportedExtensions = QHash<QString, AbstractTextureImporter*>();

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
		for (Material* material : MaterialManager::instance().materials)
		{
			// TODO: set all textures to null texture;
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
		Texture* newTexture = supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl);
		textures.insert(name, newTexture);

		return newTexture;
	}

	Texture* TextureManager::Load(QString name, QString fileUrl, Texture* targetTexture)
	{
		Texture* newTexture = supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl, targetTexture);
		textures.insert(name, targetTexture);

		return newTexture;
	}

	void TextureManager::AddImporter(class AbstractTextureImporter* importer)
	{
		for (QString extensionName : importer->getSupportedExtensions())
		{
			supportedExtensions[extensionName] = importer;
		}
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
			for (Material* material : MaterialManager::instance().materials)
			{
				// TODO: if material uses texture isUsed return;
			}
			delete TextureManager::textures[name];
		}
	}

}