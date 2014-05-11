#include "Texture.h"
#include "MaterialManager.h"


Texture::Texture(QString fileUrl)
{
	///TODO: implement it.
}


Texture::~Texture(void)
{
	foreach(Material* material, MaterialManager::Instance().materials)
	{
		///TODO: set texture parameters equal to this to value typical for
		//unneccessary if caled from TextureManager
	}
}
