#include <Texture/TextureImporter/QtTextureImporter.h>

#include <Texture/TextureManager.h>

namespace TropicalEngine
{

	QtTextureImporter::QtTextureImporter()
	{
		// TODO: Add DDS format. Needs including apropriate Qt plugin to the project.
		supportedExtensions << "tga" << "png" << "jpg" << "bmp";

		TextureManager::AddImporter(this);
	}


	QtTextureImporter::~QtTextureImporter()
	{
	}

	Texture* QtTextureImporter::Load(QString name, QString fileUrl, Texture* textureTarget)
	{
		Texture* newTexture;
		if (textureTarget != nullptr)
		{
			newTexture = textureTarget;
		}
		else
		{
			newTexture = spawnTexture(name);
		}

		QImage textureData;
		if (fileUrl.endsWith(".tga", Qt::CaseInsensitive))
		{
			textureData = QImage(fileUrl).mirrored(false, true);
		}
		else
		{
			textureData = QImage(fileUrl);
		}

		textureData = textureData.convertToFormat(QImage::Format_RGBA8888);

		newTexture->Create();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width(), textureData.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.bits());
		glGenerateMipmap(GL_TEXTURE_2D);

		return newTexture;
	}

}