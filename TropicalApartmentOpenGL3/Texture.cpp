//#include "Texture.h"
#pragma once
#include "Textures_header.h"

	Texture::Texture(char* textureFile)
	{
		// Texture set up.

		glusLoadTgaImage(textureFile, &image);

		glGenTextures(1, &_texture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _texture);

		glTexImage2D(GL_TEXTURE_2D, 0, image.format, image.width, image.height, 0, image.format, GL_UNSIGNED_BYTE, image.data);

		// Mipmap generation is now included in OpenGL 3 and above
		glGenerateMipmap(GL_TEXTURE_2D);

		// Trilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glBindTexture(GL_TEXTURE_2D, 0);//??
	}