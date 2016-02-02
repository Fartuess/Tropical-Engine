#include <Texture/TextureImporter/AbstractTextureImporter.h>

namespace TropicalEngine
{

	QList<QString> AbstractTextureImporter::getSupportedExtensions()
	{
		return supportedExtensions;
	}

	Texture* AbstractTextureImporter::spawnTexture(QString name)
	{
		return new Texture(name);
	}
}
