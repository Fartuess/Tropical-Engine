#pragma once
//#ifndef Texture_Included
//#define Texture_Included

#include "Textures_header.h"
#include <GL/glus.h>

class Texture
{
public:

	GLuint _texture;
	GLUStgaimage image;

	Texture(char* textureFile);
};

//#endif //Texture_Included