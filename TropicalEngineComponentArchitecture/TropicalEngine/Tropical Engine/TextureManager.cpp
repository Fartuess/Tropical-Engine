#include "TextureManager.h"
#include "MaterialManager.h"

#include "TropicalEngineApplication.h"

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
	foreach(Material* material, TropicalEngineApplication::instance()->materialManager->materials)
	{
		///TODO: set all textures to null texture;
	}
}

void TextureManager::Load(QString name, QString fileUrl)
{
	textures.insert(name, new Texture(fileUrl));
}

void TextureManager::FlushTexture(QString name, bool forced)
{
	if(!textures.contains(name))
		return;
	if(forced)
	{
		delete TextureManager::textures[name];
	}
	else
	{
		foreach(Material* material, TropicalEngineApplication::instance()->materialManager->materials)
		{
			///TODO: if material uses texture isUsed return;
		}
		delete TextureManager::textures[name];
	}
}
