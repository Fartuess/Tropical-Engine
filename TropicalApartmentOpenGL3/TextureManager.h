#pragma once
//#ifndef TextureManager_Included
//#define TextureManager_Included

#include "Textures_header.h"
#include <string>
#include <map>

using namespace std;

class TextureManager
{
public:
	static map<std::string, Texture*> textures;
	//static TextureManager();
	static void Load(std::string name, Texture* texture);	///Loads texture from given file
};

//#endif //TextureManager_Include