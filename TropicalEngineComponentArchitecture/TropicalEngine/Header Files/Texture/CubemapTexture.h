#pragma once
#include <Texture/Texture.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class representing set of 6 TextureData objects for every face of cubemap.
	  */
	#pragma endregion
	class CubemapTextureData
	{
	public:
		TextureData *top, *bottom, *front, *back, *left, *right;
	};

	#pragma region documentation
	/**
	  * \brief class for Cubemap Texture.
	  */
	#pragma endregion
	class CubemapTexture : public Texture
	{
	public:
		TYPENAME(CubemapTexture)

		#pragma region documentation
		/**
		  * \brief CubemapTexture constructor.
		  *
		  * @param fileUrlTop Filepath to top face texture.
		  * @param fileUrlBottom Filepath to bottom face texture.
		  * @param fileUrlFront Filepath to front face texture.
		  * @param fileUrlBack Filepath to back face texture.
		  * @param fileUrlLeft Filepath to left face texture.
		  * @param fileUrlRight Filepath to right face texture.
		  * @param name Name of Cubemap Texture.
		  */
		#pragma endregion
		CubemapTexture(QString fileUrlTop, QString fileUrlBottom, QString fileUrlFront, QString fileUrlBack, QString fileUrlLeft, QString fileUrlRight, QString name);
		// TODO: Remove or finish implementing it.
		CubemapTexture(QString fileUrl, QString name);
		#pragma region documentation
		/**
		  * \brief CubemapTexture destructor.
		  */
		#pragma endregion
		~CubemapTexture();

		#pragma region documentation
		/**
		  * \brief Initialize the CubemapTexture.
		  *
		  * @param wrappingS Horizontal wrapping type.
		  * @param wrappingT Vertical wrapping type.
		  */
		#pragma endregion
		void Create(int wrappingS = GL_CLAMP_TO_EDGE, int wrappingT = GL_CLAMP_TO_EDGE) override;
		#pragma region documentation
		/**
		  * \brief Activates texture unit at gpu.
		  */
		#pragma endregion
		void ActivateTexture(GLuint location) override;

		#pragma region documentation
		/**
		  * \brief Serializes CubemapTexture to JSON.
		  *
		  * @return Serialized JSON.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes JSON into CubemapTexture.
		  *
		  * @return Deserialized Object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		QString fileUrlTop;
		QString fileUrlBottom;
		QString fileUrlFront;
		QString fileUrlBack;
		QString fileUrlLeft;
		QString fileUrlRight;

		enum CubemapType
		{
			Cubic,
			Panoramic
		} type;

		CubemapTextureData* CreateFromCube();
		CubemapTextureData* CreateFromPanorama();
	};

}