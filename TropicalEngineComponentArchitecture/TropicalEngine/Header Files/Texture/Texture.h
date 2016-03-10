#pragma once
#include <GL/glew.h>

#include <glm.hpp>

#include <QtCore/qvector.h>
#include <QtCore/qstring.h>

#include <Utills/Exception.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	class TextureData
	{
	protected:
		char* internalData;
		glm::ivec2 size;
		uint cellSize;

		QString typeName;


		TextureData()	{}
	public:
		GLuint internalFormat;
		GLuint format;
		GLuint type;

		~TextureData()
		{
			free(internalData);
		}

		static TextureData* create(void* data, glm::ivec2 size, uint cellSize, QString typeName)
		{
			TextureData* textureData = new TextureData();
			textureData->cellSize = cellSize;
			textureData->internalData = (char*)malloc(cellSize * size.x * size.y);
			textureData->size = size;
			memcpy(textureData->internalData, data, cellSize * size.x * size.y);
			return textureData;
		}

		template <typename T>
		static TextureData* create(T* data, glm::ivec2 size, QString typeName);

		QString getTypeName()
		{
			return typeName;
		}

		glm::uint getCellSize()
		{
			return cellSize;
		}

		glm::ivec2 getSize()
		{
			return size;
		}

		int getWidth()
		{
			return size.x;
		}

		int getHeight()
		{
			return size.y;
		}

		template <typename T>
		T* getPixel(int x, int y, QString typeName = nullptr)
		{
			if (typeName != nullptr)
			{
				if (this->typeName != typeName);
				{
					throw Exception<TextureData>("Types are not matching" ,this)
				}
			}
			return ((T*)internalData)[y * size.x + x];
		}

		template <typename T>
		T* getPixel(glm::ivec2 position, QString typeName = nullptr)
		{
			return getPixel<T>(position.x, position.y, typeName);
		}

		void* getRawPixel(int x, int y)
		{
			return (void*)(&internalData[(y * size.x + x) * cellSize]);
		}

		void* getRawPixel(glm::ivec2 position)
		{
			return (void*)(&internalData[(position.y * size.x + position.x) * cellSize]);
		}

		template <typename T, typename Lambda>
		T* getPixel(glm::vec2 position, Lambda interpolationLambda)
		{
			if (typeName != nullptr)
			{
				if (this->typeName != typeName);
				{
					throw Exception<TextureData>("Types are not matching", this)
				}
			}

			T* topLeftValue = getPixel<T>(qFloor(x), qFloor(y));
			T* topRightValue = getPixel<T>(qCeil(x), qFloor(y));
			T* bottomLeftValue = getPixel<T>(qFloor(x), qCeil(y));
			T* bottomRightValue = getPixel<T>(qCeil(x), qCeil(y));

			glm::vec2 weight = glm::vec2(x - qFloor(x), y - qFloor(y));

			T* newValue = interpolationLambda(topLeftValue, topRightValue, bottomLeftValue, bottomRightValue, weight);

			return newValue;
		}

		template <typename Lambda>
		void* getRawPixel(float x, float y, Lambda interpolationLambda)
		{
			void* topLeftValue = getRawPixel(qFloor(x), qFloor(y));
			void* topRightValue = getRawPixel(qCeil(x), qFloor(y));
			void* bottomLeftValue = getRawPixel(qFloor(x), qCeil(y));
			void* bottomRightValue = getRawPixel(qCeil(x), qCeil(y));

			glm::vec2 weight = glm::vec2(x - qFloor(x), y - qFloor(y));

			void* newValue = interpolationLambda(topLeftValue, topRightValue, bottomLeftValue, bottomRightValue, weight);

			return newValue;
		}

		template <typename Lambda>
		void* getRawPixel(glm::vec2 position, Lambda interpolationLambda)
		{
			return getRawPixel(position.x, position.y);
		}

		template <typename T>
		void setPixel(int x, int y, T value, QString typeName = nullptr)
		{
			if (typeName != nullptr)
			{
				if (this->typeName != typeName);
				{
					throw Exception<TextureData>("Types are not matching", this)
				}
			}
			((T*)internalData)[y * size.x + x] = value;
		}

		template <typename T>
		void setPixel(glm::ivec2 position, T value, QString typeName = nullptr)
		{
			setPixel<T>(position.x, position.y, value, typeName);
		}

		void* rawData()
		{
			return internalData;
		}

		template <typename T>
		T* data(QString typeName = nullptr)
		{
			if (typeName != nullptr)
			{
				if (this->typeName != typeName);
				{
					throw Exception<TextureData>("Types are not matching", this);
				}
			}
			return (T*)internalData;
		}
	};

	template <typename T>
	static TextureData* TextureData::create(T* data, glm::ivec2 size, QString typeName)
	{
		TextureData* textureData = new TextureData();
		textureData->typeName = typeName;
		textureData->cellSize = sizeof(T);
		textureData->internalData = (char*)malloc(textureData->cellSize * size.x * size.y);
		memcpy(textureData->internalData, data, textureData->cellSize * size.x * size.y);
		textureData->size = size;
		return textureData;
	}

	#define newTextureData(T, data, size) TextureData::create<T>(data, size, #T)

	#pragma region documentation
	/**
	  * \brief Class for Texture.
	  */
	#pragma endregion
	class Texture : public ISerializableJSON
	{
	public:
		TYPENAME(Texture)

		friend class AbstractTextureImporter;
		friend class TextureManager;

		#pragma region documentation
		/**
		  * \brief Constructor for Texture class.
		  *
		  * @param fileUrl path to file texture will be loaded from.
		  * @param name Name to be set for Texture.
		  */
		#pragma endregion
		Texture(QString fileUrl, QString name);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~Texture(void);

		#pragma region documentation
		/**
		  * \brief Texture to be used if needed texture can't be found.
		  */
		#pragma endregion
		static Texture nullTexture;

		#pragma region documentation
		/**
		  * \brief Gets name of the Texture.
		  *
		  * @return Name of the Texture.
		  */
		#pragma endregion
		QString getName();
		#pragma region documentation
		/**
		  * \brief Sets name of the Texture.
		  *
		  * @param name Name to be set.
		  */
		#pragma endregion
		void setName(QString name);

		// TODO: Create flexible interface for changing texture parameters.
		#pragma region documentation
		/**
		  * \brief Initialization of RenderTexture.
		  */
		#pragma endregion
		virtual void Create(int wrappingS = GL_REPEAT, int wrappingT = GL_REPEAT);

		#pragma region documentation
		/**
		  * \brief Sets this texture as the Active one in OpenGL context.
		  *
		  * @param location I DON'T REMEMBER EXACTLY. IT IS MAINLY FOR TEXTUREMANAGER.
		  */
		#pragma endregion
		virtual void ActivateTexture(GLuint location);

		#pragma region documentation
		/**
		  * \brief Serializes Texture to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes Texture from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Texture object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;
	protected:
		#pragma region documentation
		/**
		  * \brief Helper internal constructor.
		  *
		  * @param name Name for new Texture.
		  */
		#pragma endregion
		Texture(QString name);
		#pragma region documentation
		/**
		  * \brief Path to the file with Texture data.
		  */
		#pragma endregion
		QString fileUrl;	// TODO: Figure out how to implement changing paths.
		#pragma region documentation
		/**
		  * \brief Name of the Texture.
		  */
		#pragma endregion
		QString name;

		TextureData* textureData;

		GLuint textureLocation;

	};

}