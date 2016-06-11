#include <QtCore/qdebug.h>
#include <QtGui/qimagereader.h>

#include <Texture/TextureManager.h>
#include <Texture/TextureImporter/AbstractTextureImporter.h>
#include <Texture/CubemapTexture.h>

#include <Shader/MaterialManager.h>

namespace TropicalEngine
{
	QHash<QString, AbstractTextureImporter*> TextureManager::supportedExtensions = QHash<QString, AbstractTextureImporter*>();

	TextureManager::TextureManager(void)
	{
		textureIterator = 0;
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

	bool TextureManager::hasTexture(QString name)
	{
		return textures.contains(name);
	}

	Texture* const TextureManager::getTexture(QString name)
	{
		return textures[name];
	}

	TextureData* TextureManager::LoadData(QString fileUrl, bool flipY)
	{
		return supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->LoadData(fileUrl, flipY);
	}

	Texture* TextureManager::Load(QString name, QString fileUrl)
	{
		Texture* newTexture = new Texture(name);
		newTexture = supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl, newTexture);
		textures.insert(name, newTexture);

		return newTexture;
	}

	Texture* TextureManager::Load(QString name, QString fileUrl, Texture* targetTexture)
	{
		Texture* newTexture = supportedExtensions[fileUrl.section(".", -1, -1).toLower()]->Load(name, fileUrl, targetTexture);
		textures.insert(name, targetTexture);

		return newTexture;
	}

	CubemapTexture* TextureManager::Load(QString name, QString fileUrlTop, QString fileUrlBottom, QString fileUrlFront, QString fileUrlBack, QString fileUrlLeft, QString fileUrlRight)
	{
		CubemapTexture* newTexture = new CubemapTexture(fileUrlTop, fileUrlBottom, fileUrlFront, fileUrlBack, fileUrlLeft, fileUrlRight, name);
		textures.insert(name, newTexture);

		return newTexture;
	}

	CubemapTexture* TextureManager::Load(QString name, CubemapTexture* targetTexture)
	{
		CubemapTexture* newTexture = targetTexture;
		newTexture->Create();
		textures.insert(name, newTexture);

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