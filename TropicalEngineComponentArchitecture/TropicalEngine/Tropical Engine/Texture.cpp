#include <gl\glew.h>
#include <QtCore\qfile.h>
#include "Texture.h"
#include "TextureManager.h"
#include "MaterialManager.h"

#include "TropicalEngineApplication.h"

Texture::Texture(QString fileUrl)
{
	///TODO: implement it.
	//QFile* textureFile;
	//QDataStream* textureStream;
	//uchar type;	//??
	//uchar bitsPerPixel;	//??
	//uint elementsRead;	//??
	//tgaImage* texture;	//should it be promoted to class field?
	//
	//if(fileUrl == nullptr)
	//	return;
	//
	//texture->width = 0;
	//texture->height = 0;
	//texture->data = 0;
	//texture->format = textureFormat::tex_Null;
	//
	//textureStream = new QDataStream(textureFile);

	this->filename = fileUrl;
	Load(filename);
}


Texture::~Texture(void)
{
	foreach(Material* material, TropicalEngineApplication::instance()->materialManager->materials)
	{
		///TODO: set texture parameters equal to this to value typical for
		//unneccessary if caled from TextureManager
	}
}

void Texture::Load(QString fileUrl)
{
	//Magick::Image* image;
	//Magick::Blob imageData;
	//
	//try {
    //    image = new Magick::Image(filename.toUtf8().constData());
    //    image->write(&imageData, "RGBA");
    //}
    //catch (Magick::Error& Error) {
	//	//fprintf("Error loading texture '%s': %s", fileUrl.toLocal8Bit().data(), Error.what());
	//	printf("Error loading texture: %s", Error.what());
    //    return;// false;
    //}
	//
    //glGenTextures(1, &textureObject);
    //glBindTexture(textureTarget, textureObject);
    //glTexImage2D(textureTarget, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.data());
	//glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//
	//delete image;

	textureData = QPixmap(fileUrl);
}

void Texture::ActivateTexture(GLuint location)
{
	glActiveTexture(GL_TEXTURE0 + TropicalEngineApplication::instance()->textureManager->getTextureIterator());
	glBindTexture(GL_TEXTURE_2D, textureLocation);
	glUniform1i(location, TropicalEngineApplication::instance()->textureManager->getTextureIterator());
	TropicalEngineApplication::instance()->textureManager->incrementTextureIterator();
}

QString Texture::toXML()
{
	return QString(getIndent() + "<Texture filepath = \"" + filename + "\"/>\n");
}