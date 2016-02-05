#pragma once
#include <Texture/TextureImporter/AbstractTextureImporter.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	class OpenExrTextureImporter : public AbstractTextureImporter, public Singleton<OpenExrTextureImporter>
	{
	public:
		OpenExrTextureImporter();
		~OpenExrTextureImporter();

		virtual Texture* Load(QString name, QString fileUrl, Texture* textureTarget = nullptr) override;
	};

}