#pragma once
#include <Texture/Texture.h>

namespace TropicalEngine
{

	class CubemapTextureData
	{
	public:
		TextureData *top, *bottom, *front, *back, *left, *right;
	};

	class CubemapTexture : public Texture
	{
	public:
		TYPENAME(CubemapTexture)

		CubemapTexture(QString fileUrlTop, QString fileUrlBottom, QString fileUrlFront, QString fileUrlBack, QString fileUrlLeft, QString fileUrlRight, QString name);
		CubemapTexture(QString fileUrl, QString name);
		~CubemapTexture();

		void Create(int wrappingS = GL_CLAMP_TO_EDGE, int wrappingT = GL_CLAMP_TO_EDGE) override;
		void ActivateTexture(GLuint location) override;

		QJsonObject toJSON() override;
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