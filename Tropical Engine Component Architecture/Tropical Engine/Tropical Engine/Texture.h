#pragma once
#include <QtCore\qstring.h>
#include <GL/glew.h>

//enum textureFormat
//{
//	tex_RGB,
//	tex_RGBA,
//	tex_Grayscale,
//	tex_Null
//};

//typedef struct tgaImage
//{
//	ushort width;
//	ushort height;
//	uchar* data;
//	textureFormat format;
//};

class Texture
{
private:
	QString filename;
	GLenum textureTarget;
	GLuint textureObject;
public:
	Texture(QString fileUrl);
	~Texture(void);

	static Texture nullTexture;

	void Load(QString filUrl);
};

