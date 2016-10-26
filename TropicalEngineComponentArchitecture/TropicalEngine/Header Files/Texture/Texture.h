#pragma once
#include <GL/glew.h>

#include <glm.hpp>

#include <QtCore/qvector.h>
#include <QtCore/qstring.h>

#include <Utills/Exception.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	// TODO: Figure out which methods from this class are not needed anymore and which aren't finished.
	#pragma region documentation
	/**
	  * \brief Class for containing low level Texture Data before it is sent to GPU.
	  */
	#pragma endregion
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

		#pragma region documentation
		/**
		  * \brief Destructor freeing data memory from the CPU side, but not from the GPU.
		  */
		#pragma endregion
		~TextureData()
		{
			free(internalData);
		}

		#pragma region documentation
		/**
		  * \brief Named constructor for TextureData class.
		  *
		  * @param data Pointer for raw memory representing texture data.
		  * @param size Size of texture in pixels in X and Y dimension.
		  * @param cellSize Memory size of one pixels in bytes.
		  * @param typename Name of type used for pixel data.
		  *
		  * @return Created TextureData.
		  */
		#pragma endregion
		static TextureData* create(void* data, glm::ivec2 size, uint cellSize, QString typeName)
		{
			TextureData* textureData = new TextureData();
			textureData->cellSize = cellSize;
			textureData->internalData = (char*)malloc(cellSize * size.x * size.y);
			textureData->size = size;
			memcpy(textureData->internalData, data, cellSize * size.x * size.y);
			return textureData;
		}

		#pragma region documentation
		/**
		  * \brief Named constructor for TextureData class.
		  *
		  * @tparam T Type used for storing pixel data.
		  * @param data Pointer for typed memory representing texture data.
		  * @param size Size of texture in pixels in X and Y dimension.
		  * @param typename Name of type used for pixel data.
		  *
		  * @return Created TextureData.
		  */
		#pragma endregion
		template <typename T>
		static TextureData* create(T* data, glm::ivec2 size, QString typeName);

		#pragma region documentation
		/**
		  * \brief Gets name of type used for storing pixel data.
		  *
		  * @return Name of type used for storing pixel data.
		  */
		#pragma endregion
		QString getTypeName()
		{
			return typeName;
		}

		#pragma region documentation
		/**
		  * \brief Gets memory size used by single pixel of texture.
		  *
		  * @return Memory size used by single pixel in bytes.
		  */
		#pragma endregion
		glm::uint getCellSize()
		{
			return cellSize;
		}

		#pragma region documentation
		/**
		  * \brief Gets dimensions of the texture in pixels.
		  *
		  * @return Dimensions of the texture in pixels.
		  */
		#pragma endregion
		glm::ivec2 getSize()
		{
			return size;
		}

		#pragma region documentation
		/**
		  * \brief Gets width of texture in pixels.
		  *
		  * @return Width of texture in pixels.
		  */
		#pragma endregion
		int getWidth()
		{
			return size.x;
		}

		#pragma region documentation
		/**
		  * \brief Gets height of texture in pixels.
		  *
		  * @return Height of texture in pixels.
		  */
		#pragma endregion
		int getHeight()
		{
			return size.y;
		}

		#pragma region documentation
		/**
		  * \brief Gets pointer single pixel at given coordinates.
		  *
		  * @tparam T type we want to retrieve pixel in.
		  * @param x Position of pixel in X dimension.
		  * @param y Position of pixel in Y dimension.
		  * @param typeName Optional parameter used to check if type T is the same as internal type actualy used by texture.
		  *
		  * @return Pointer to pixel data.
		  */
		#pragma endregion
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

		#pragma region documentation
		/**
		  * \brief Gets pointer to single pixel at given coordinates.
		  *
		  * @tparam T type we want to retrieve pixel in.
		  * @param position Position of pixel.
		  * @param typeName Optional parameter used to check if type T is the same as internal type actualy used by texture.
		  *
		  * @return Pointer to pixel data.
		  */
		#pragma endregion
		template <typename T>
		T* getPixel(glm::ivec2 position, QString typeName = nullptr)
		{
			return getPixel<T>(position.x, position.y, typeName);
		}

		#pragma region documentation
		/**
		  * \brief Gets untyped pointer to the single pixel at given coordinates.
		  *
		  * @param x Position of pixel in X dimension.
		  * @param y Position of pixel in Y dimension.
		  *
		  * @return Untyped pointer to pixel data.
		  */
		#pragma endregion
		void* getRawPixel(int x, int y)
		{
			return (void*)(&internalData[(y * size.x + x) * cellSize]);
		}

		#pragma region documentation
		/**
		  * \brief Gets untyped pointer to the single pixel at given coordinates.
		  *
		  * @param position Position of pixel.
		  *
		  * @return Untyped pointer to pixel data.
		  */
		#pragma endregion
		void* getRawPixel(glm::ivec2 position)
		{
			return (void*)(&internalData[(position.y * size.x + position.x) * cellSize]);
		}

		#pragma region documentation
		/**
		  * \brief Gets pointer to single pixel at given coordinates.
		  *
		  * @tparam T type we want to retrieve pixel in.
		  * @tparam Lambda Lambda funtion type
		  * @param position Position of pixel.
		  * @param interpolationLambda function used for getting pixel values for positions which are not defined by integers.
		  *
		  * @return Pointer to pixel data.
		  */
		#pragma endregion
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

		#pragma region documentation
		/**
		  * \brief Gets pointer to single pixel at given coordinates.
		  *
		  * @tparam T type we want to retrieve pixel in.
		  * @tparam Lambda Lambda funtion type
		  * @param position Position of pixel.
		  * @param interpolationLambda function used for getting pixel values for positions which are not defined by integers.
		  *
		  * @return Pointer to pixel data.
		  */
		#pragma endregion
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

		// TODO: Figure out what to do with this method.
		template <typename Lambda>
		void* getRawPixel(glm::vec2 position, Lambda interpolationLambda)
		{
			return getRawPixel(position.x, position.y);
		}

		#pragma region documentation
		/**
		  * \brief Sets value of the pixel at given position.
		  *
		  * @tparam T Type used to store pixel information.
		  * @param x Position of pixel in X dimension.
		  * @param y Position of pixel in Y dimension.
		  * @param value New value for the pixel.
		  * @param typeName Optional parameter used to check if type T is the same as internal type actualy used by texture.
		  */
		#pragma endregion
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

		#pragma region documentation
		/**
		  * \brief Sets value of the pixel at given position.
		  *
		  * @tparam T Type used to store pixel information.
		  * @param position Position of pixel.
		  * @param value New value for the pixel.
		  * @param typeName Optional parameter used to check if type T is the same as internal type actualy used by texture.
		  */
		#pragma endregion
		template <typename T>
		void setPixel(glm::ivec2 position, T value, QString typeName = nullptr)
		{
			setPixel<T>(position.x, position.y, value, typeName);
		}

		#pragma region documentation
		/**
		  * \brief Gets pointer to the raw texture data.
		  *
		  * @return untyped pointer to the raw texture memory.
		  */
		#pragma endregion
		void* rawData()
		{
			return internalData;
		}

		#pragma region documentation
		/**
		  * \brief Gets type pointer to the texture data.
		  *
		  * @tparam T Type used for storing pixel information.
		  * @param typeName Optional parameter used to check if type T is the same as internal type actualy used by texture.
		  */
		#pragma endregion
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

	#pragma region documentation
	/**
	  * \brief Named constructor for TextureData class.
	  *
	  * @tparam T Type of data used for storing information about pixel.
	  * @param data Pointer for raw memory representing texture data.
	  * @param size Size of texture in pixels in X and Y dimension.
	  * @param typename Name of type used for pixel data.
	  *
	  * @return Created TextureData.
	  */
	#pragma endregion
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

	// TODO: Figure out how to document macros.
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

		#pragma region documentation
		/**
		  * \brief Sets wrapping modes for Texture.
		  *
		  * @param wrappingS Horizontal texture wrapping.
		  * @param wrappingT Vertical texture wrapping.
		  */
#		pragma endregion
		void setWrapping(int wrappingS = GL_REPEAT, int wrappingT = GL_REPEAT);

		#pragma region documentation
		/**
		  * \brief Sets filtering modes for Texture.
		  *
		  * @param minFilter Min filter type.
		  * @param magFilter Magnifying filter type.
		  */
		#pragma endregion
		void setFiltering(int minFilter = GL_LINEAR_MIPMAP_LINEAR, int magFilter = GL_LINEAR);

		// TODO: Create flexible interface for changing texture parameters.
		#pragma region documentation
		/**
		  * \brief Sets wrapping modes for Texture.
		  *
		  * @param wrappingS Horizontal texture wrapping.
		  * @param wrappingT Vertical texture wrapping.
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