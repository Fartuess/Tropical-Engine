#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for Texture.
	  */
	#pragma endregion
	class Texture : public ISerializableJSON
	{
	public:
		TYPENAME(Texture)

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
		  * \brief Loads the texture.
		  */
		#pragma endregion
		void Load();

		#pragma region documentation
		/**
		  * \brief Sets this texture as the Active one in OpenGL context.
		  *
		  * @param location I DON'T REMEMBER EXACTLY. IT IS MAINLY FOR TEXTUREMANAGER.
		  */
		#pragma endregion
		void ActivateTexture(GLuint location);

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
		  * \brief Initialization of RenderTexture.
		  */
		#pragma endregion
		virtual void Create();
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

		GLuint textureLocation;

	};

}