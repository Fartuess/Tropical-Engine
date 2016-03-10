#include <QtGui/qimage.h>

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

		TextureData* textureData = LoadData(fileUrl);

		newTexture->Create(GL_REPEAT, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, textureData->internalFormat, textureData->getWidth(), textureData->getHeight(), 0, textureData->format, textureData->type, textureData->rawData());
		glGenerateMipmap(GL_TEXTURE_2D);

		return newTexture;
	}

	TextureData* QtTextureImporter::LoadData(QString fileUrl, bool flipY)
	{
		QImage image;
		if (fileUrl.endsWith(".tga", Qt::CaseInsensitive) && !flipY)
		{
			image = QImage(fileUrl).mirrored(false, true);
		}
		else
		{
			image = QImage(fileUrl).mirrored(false, false);
		}

		image = image.convertToFormat(QImage::Format_RGBA8888);

		// QRgb in format RGBA8888 is same as glm::u8vec4
		TextureData* textureData = newTextureData(glm::u8vec4, (glm::u8vec4*)image.bits(), glm::ivec2(image.width(), image.height()));
		textureData->internalFormat = GL_RGBA;
		textureData->format = GL_RGBA;
		textureData->type = GL_UNSIGNED_BYTE;

		return textureData;
	}

}