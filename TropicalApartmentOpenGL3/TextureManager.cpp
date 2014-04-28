#pragma once

#include "Textures_header.h"

using namespace std;
typedef pair <std::string, Texture*> tElement;

	/*TextureManager::TextureManager()
	{
		Load("default", new Texture("GenericTiles.tga"));
	}*/

map<std::string, Texture*> TextureManager::textures;

	void TextureManager::Load(std::string name, Texture* texture)
	{
		
		textures.insert(tElement (name, texture));
	}