#include <glm.hpp>

#include <ImfRgba.h>
#include <ImfRgbaFile.h>
#include <ImathBox.h>

#include <Texture/TextureImporter/OpenExrTextureImporter.h>

#include <Texture/TextureManager.h>

namespace TropicalEngine
{

	OpenExrTextureImporter::OpenExrTextureImporter()
	{
		supportedExtensions << "exr";

		TextureManager::AddImporter(this);
	}


	OpenExrTextureImporter::~OpenExrTextureImporter()
	{
	}

	Texture* OpenExrTextureImporter::Load(QString name, QString fileUrl, Texture* textureTarget)
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

		newTexture->Create(GL_REPEAT, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, textureData->internalFormat, textureData->getWidth(), textureData->getHeight(), 0, textureData->format, textureData->type, textureData->rawData());
		glGenerateMipmap(GL_TEXTURE_2D);

		return newTexture;
	}

	TextureData* OpenExrTextureImporter::LoadData(QString fileUrl, bool flipY)
	{
		Imf::Rgba* image;
		glm::ivec2 dimensions;
		try
		{
			Imf::RgbaInputFile inputFile(fileUrl.toStdString().c_str());

			Imath::Box2i window = inputFile.dataWindow();

			dimensions = glm::ivec2(window.max.x - window.min.x + 1, window.max.y - window.min.y + 1);

			Imf::Rgba* pixels = new Imf::Rgba[dimensions.x * dimensions.y];

			int dx = window.min.x;
			int dy = window.min.y;

			inputFile.setFrameBuffer(pixels - dx - dy * dimensions.x, 1, dimensions.x);
			inputFile.readPixels(window.min.y, window.max.y);

			if (!flipY)
			{
				// Flipping image manually. OpenEXR doesn't have code documentation.
				image = new Imf::Rgba[dimensions.x * dimensions.y];

				for (int y = 0; y < dimensions.y; y++) for (int x = 0; x < dimensions.x; x++)
				{
					image[(dimensions.x) * y + x] = pixels[(dimensions.x) * (dimensions.y - 1 - y) + x];
				}
			}
			else
			{
				image = pixels;
			}

			// TODO: Clean memory?
		}
		catch (Iex::BaseExc & e)
		{
			std::cerr << e.what() << std::endl;
		}

		TextureData* textureData = newTextureData(Imf::Rgba, (Imf::Rgba*)image, glm::ivec2(dimensions.x, dimensions.y));
		textureData->internalFormat = GL_RGBA16F;
		textureData->format = GL_RGBA;
		textureData->type = GL_HALF_FLOAT;

		return textureData;
	}
}