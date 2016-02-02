#pragma once
#include <Texture/TextureImporter/AbstractTextureImporter.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	class QtTextureImporter : public AbstractTextureImporter, public Singleton<QtTextureImporter>
	{
	public:
		QtTextureImporter();
		~QtTextureImporter();

		virtual Texture* Load(QString name, QString fileUrl, Texture* textureTarget = nullptr) override;
	};

}