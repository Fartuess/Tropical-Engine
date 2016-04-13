#include <gtc/constants.hpp>

#include <QtCore/qmath.h>
#include <ImfRgba.h>
#include <half.h>

#include <functional>

#include <Texture\CubemapTexture.h>
#include <Texture\TextureManager.h>

#include <Utills\MathUtills.h>

namespace TropicalEngine
{

	CubemapTexture::CubemapTexture(QString fileUrlTop, QString fileUrlBottom, QString fileUrlFront, QString fileUrlBack, QString fileUrlLeft, QString fileUrlRight, QString name)
		: Texture(name)
	{
		this->fileUrlTop = fileUrlTop;
		this->fileUrlBottom = fileUrlBottom;
		this->fileUrlFront = fileUrlFront;
		this->fileUrlBack = fileUrlBack;
		this->fileUrlLeft = fileUrlLeft;
		this->fileUrlRight = fileUrlRight;

		this->type = CubemapType::Cubic;

		TextureManager::instance().Load(name, this);
	}

	CubemapTexture::CubemapTexture(QString fileUrl, QString name)
		: Texture(name)
	{
		this->fileUrl = fileUrl;

		this->type = CubemapType::Panoramic;

		TextureManager::instance().Load(name, this);
	}

	CubemapTexture::~CubemapTexture()
	{
	}

	void CubemapTexture::Create(int wrappingS, int wrappingT)
	{
		// TODO: Very temporary solution. I think it creates a lot of junk on the GPU side.
		TextureData *textureTop, *textureBottom, *textureFront, *textureBack, *textureLeft, *textureRight;

		CubemapTextureData* cubemapData;
		
		switch (type)
		{
			case CubemapType::Cubic:
			{
				cubemapData = CreateFromCube();
				break;
			}
			case CubemapType::Panoramic:
			{
				cubemapData = CreateFromPanorama();
				break;
			}
		}

		textureTop = cubemapData->top;
		textureBottom = cubemapData->bottom;
		textureFront = cubemapData->front;
		textureBack = cubemapData->back;
		textureLeft = cubemapData->left;
		textureRight = cubemapData->right;

		glGenTextures(1, &textureLocation);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureLocation);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, textureTop->internalFormat, textureTop->getWidth(), textureTop->getHeight(), 0, textureTop->format, textureTop->type, textureTop->rawData());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, textureBottom->internalFormat, textureBottom->getWidth(), textureBottom->getHeight(), 0, textureBottom->format, textureBottom->type, textureBottom->rawData());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, textureFront->internalFormat, textureFront->getWidth(), textureFront->getHeight(), 0, textureFront->format, textureFront->type, textureFront->rawData());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, textureBack->internalFormat, textureBack->getWidth(), textureBack->getHeight(), 0, textureBack->format, textureBack->type, textureBack->rawData());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, textureLeft->internalFormat, textureLeft->getWidth(), textureLeft->getHeight(), 0, textureLeft->format, textureLeft->type, textureLeft->rawData());
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, textureRight->internalFormat, textureRight->getWidth(), textureRight->getHeight(), 0, textureRight->format, textureRight->type, textureRight->rawData());

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	CubemapTextureData* CubemapTexture::CreateFromCube()
	{
		CubemapTextureData* data = new CubemapTextureData();

		data->top = TextureManager::instance().LoadData(fileUrlTop, true);
		data->bottom = TextureManager::instance().LoadData(fileUrlBottom, true);
		data->front = TextureManager::instance().LoadData(fileUrlFront, true);
		data->back = TextureManager::instance().LoadData(fileUrlBack, true);
		data->left = TextureManager::instance().LoadData(fileUrlLeft, true);
		data->right = TextureManager::instance().LoadData(fileUrlRight, true);

		return data;
	}

	// TODO: REASURE MEMORY SAFETY! MEMORY LEAKS POSSIBLE!
	CubemapTextureData* CubemapTexture::CreateFromPanorama()
	{
		CubemapTextureData* data = new CubemapTextureData();

		// TODO: Implement it.
		TextureData* panoramicData = TextureManager::instance().LoadData(fileUrl, true);

		uint sizeX = panoramicData->getSize().x / 4;
		uint sizeY = panoramicData->getSize().y / 2;
		uint cellSize = panoramicData->getCellSize();

		char* panoramicRawData = (char*)panoramicData->rawData();

		std::function<void* (void*, void*, void*, void*, glm::vec2)> samplingFunction;

		// TODO: Create generic solution for multiple formats.
		if (panoramicData->getTypeName() == _STRINGIZE(glm::u8vec4))
		{
			samplingFunction = [&](void* topLeftValue, void* topRightValue, void* bottomLeftValue, void* bottomRightValue, glm::vec2 weight) -> void*
			{
				glm::u8vec4& topLeft = *(glm::u8vec4*)topLeftValue;
				glm::u8vec4& topRight = *(glm::u8vec4*)topRightValue;
				glm::u8vec4& BottomLeft = *(glm::u8vec4*)bottomLeftValue;
				glm::u8vec4& BottomRight = *(glm::u8vec4*)bottomRightValue;

				glm::u8vec4* result = new glm::u8vec4();

				result->r = (glm::u8)(((topLeft.r * (1.0f - weight.x)) + (topRight.r * weight.x)) * (1.0f - weight.y) +
					((BottomLeft.r * (1.0f - weight.x)) + (BottomRight.r * weight.x)) * weight.y);
				result->g = (glm::u8)(((topLeft.g * (1.0f - weight.x)) + (topRight.g * weight.x)) * (1.0f - weight.y) +
					((BottomLeft.g * (1.0f - weight.x)) + (BottomRight.g * weight.x)) * weight.y);
				result->b = (glm::u8)(((topLeft.b * (1.0f - weight.x)) + (topRight.b * weight.x)) * (1.0f - weight.y) +
					((BottomLeft.b * (1.0f - weight.x)) + (BottomRight.b * weight.x)) * weight.y);
				result->a = (glm::u8)(((topLeft.a * (1.0f - weight.x)) + (topRight.a * weight.x)) * (1.0f - weight.y) +
					((BottomLeft.a * (1.0f - weight.x)) + (BottomRight.a * weight.x)) * weight.y);

				return (void*)result;
			};
		}
		else if (panoramicData->getTypeName() == _STRINGIZE(Imf::Rgba))
		{
			samplingFunction = [&](void* topLeftValue, void* topRightValue, void* bottomLeftValue, void* bottomRightValue, glm::vec2 weight) -> void*
			{
				Imf::Rgba* topLeft = (Imf::Rgba*)topLeftValue;
				Imf::Rgba* topRight = (Imf::Rgba*)topRightValue;
				Imf::Rgba* BottomLeft = (Imf::Rgba*)bottomLeftValue;
				Imf::Rgba* BottomRight = (Imf::Rgba*)bottomRightValue;
				
				half weightX = half(weight.x);
				half weightY = half(weight.y);

				Imf::Rgba* result;
				if (weightX == 0.0f, weightY == 0.0f)
				{
					result = new Imf::Rgba(*topLeft);
				}
				else
				{
					result = new Imf::Rgba();

					result->r = half((((topLeft->r * (1.0f - weightX)) + (topRight->r * weightX)) * (1.0f - weightY) +
						((BottomLeft->r * (1.0f - weightX)) + (BottomRight->r * weightX)) * weightY));
					result->g = half((((topLeft->g * (1.0f - weightX)) + (topRight->g * weightX)) * (1.0f - weightY) +
						((BottomLeft->g * (1.0f - weightX)) + (BottomRight->g * weightX)) * weightY));
					result->b = half((((topLeft->b * (1.0f - weightX)) + (topRight->b * weightX)) * (1.0f - weightY) +
						((BottomLeft->b * (1.0f - weightX)) + (BottomRight->b * weightX)) * weightY));
					result->a = half((((topLeft->a * (1.0f - weightX)) + (topRight->a * weightX)) * (1.0f - weightY) +
						((BottomLeft->a * (1.0f - weightX)) + (BottomRight->a * weightX)) * weightY));
				}

				return (void*)result;
			};
		}
		else
		{
			samplingFunction = [&](void* topLeftValue, void* topRightValue, void* bottomLeftValue, void* bottomRightValue, glm::vec2 weight) -> void*
			{
				void* result = malloc(cellSize);

				if (weight.x < 0.5f)
				{
					if (weight.y < 0.5f)
					{
						memcpy(result, topLeftValue, cellSize);
					}
					else
					{
						memcpy(result, topRightValue, cellSize);
					}
				}
				else
				{
					if (weight.y < 0.5f)
					{
						memcpy(result, bottomLeftValue, cellSize);
					}
					else
					{
						memcpy(result, bottomRightValue, cellSize);
					}
				}

				return result;
			};
		}
		
		// Top Face
		char* topRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			//glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(-1.0 + double(2 * x) / sizeX, 1.0f, -1.0 + double(2 * y) / sizeY));
			//sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 1.0f, 2.0f) * glm::pi<float>());
			//sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			////sphericalPosition = (sphericalPosition + glm::vec3(1.0f)) / 2.0f;
			//memcpy(&topRawData[(sizeX * (sizeY - 1 - y) + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);

			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(-1.0 + double(2 * x) / sizeX, (-1.0 + double(2 * y) / sizeY) * -1.0f, 1.0f));
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 0.5f, 0.5f) * glm::pi<float>());
			sphericalPosition = ((sphericalPosition) + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			memcpy(&topRawData[(sizeX * y + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->top = TextureData::create(topRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->top->internalFormat = panoramicData->internalFormat;
		data->top->format = panoramicData->format;
		data->top->type = panoramicData->type;

		// Bottom Face
		char* bottomRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::normalize( glm::vec3(-1.0 + double(2 * x) / sizeX, (-1.0 + double(2 * y) / sizeY) * -1.0f, -1.0f)));
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 0.5f, 1.0f) * glm::pi<float>());
			sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			memcpy(&bottomRawData[(sizeX * y + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->bottom = TextureData::create(bottomRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->bottom->internalFormat = panoramicData->internalFormat;
		data->bottom->format = panoramicData->format;
		data->bottom->type = panoramicData->type;

		// Front Face
		char* frontRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(-1.0 + double(2 * x) / sizeX, (-1.0 + double(2 * y) / sizeY) * -1.0f, -1.0f));
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 0.5f, 1.0f) * glm::pi<float>());
			sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			//sphericalPosition = (sphericalPosition + glm::vec3(1.0f)) / 2.0f;
			memcpy(&frontRawData[(sizeX * y + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->front = TextureData::create(frontRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->front->internalFormat = panoramicData->internalFormat;
		data->front->format = panoramicData->format;
		data->front->type = panoramicData->type;

		// Back Face
		char* backRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(-1.0 + double(2 * x) / sizeX, (-1.0 + double(2 * y) / sizeY) * -1.0f, 1.0f));
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 1.0f, 2.0f) * glm::pi<float>());
			sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			//sphericalPosition = (sphericalPosition + glm::vec3(1.0f)) / 2.0f;
			memcpy(&backRawData[(sizeX * y + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->back = TextureData::create(backRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->back->internalFormat = panoramicData->internalFormat;
		data->back->format = panoramicData->format;
		data->back->type = panoramicData->type;

		// Left Face
		char* leftRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(-1.0f, -1.0 + double(2 * y) / sizeY, (-1.0 + double(2 * x) / sizeX)) * -1.0f);
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 1.0f, 2.0f) * glm::pi<float>());
			sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			//sphericalPosition = (sphericalPosition + glm::vec3(1.0f)) / 2.0f;
			memcpy(&leftRawData[(sizeX * y + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->left = TextureData::create(leftRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->left->internalFormat = panoramicData->internalFormat;
		data->left->format = panoramicData->format;
		data->left->type = panoramicData->type;

		// Right Face
		char* rightRawData = (char*)malloc(sizeX * sizeY * cellSize);
		for (int x = 0; x < sizeX; x++) for (int y = 0; y < sizeY; y++)
		{
			glm::vec3 sphericalPosition = math::cartesianToSpherical(glm::vec3(1.0f, -1.0 + double(2 * y) / sizeY, (-1.0 + double(2 * x) / sizeX)));
			sphericalPosition = sphericalPosition / (glm::vec3(1.0f, 1.0f, 2.0f) * glm::pi<float>());
			sphericalPosition = (sphericalPosition + 1.0f / 2.0f) * glm::vec3(1.0f, sizeX, sizeY);
			//sphericalPosition = (sphericalPosition + glm::vec3(1.0f)) / 2.0f;
			memcpy(&rightRawData[(sizeX * (sizeY - 1 - y) + x) * cellSize], panoramicData->getRawPixel(sphericalPosition.y, sphericalPosition.z, samplingFunction), cellSize);
		}
		data->right = TextureData::create(rightRawData, panoramicData->getSize() / glm::ivec2(4, 2), cellSize, panoramicData->getTypeName());
		data->right->internalFormat = panoramicData->internalFormat;
		data->right->format = panoramicData->format;
		data->right->type = panoramicData->type;

		return data;
	}

	void CubemapTexture::ActivateTexture(GLuint location)
	{
		glActiveTexture(GL_TEXTURE0 + TextureManager::instance().getTextureIterator());
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureLocation);
		glUniform1i(location, TextureManager::instance().getTextureIterator());
		TextureManager::instance().incrementTextureIterator();
	}

	QJsonObject CubemapTexture::toJSON()
	{
		// TODO: Implement it!
		return QJsonObject();
	}

	IDeserializableFromJSON* CubemapTexture::fromJSON(QJsonObject JSON)
	{
		// TODO: Implement it!
		return nullptr;
	}
}