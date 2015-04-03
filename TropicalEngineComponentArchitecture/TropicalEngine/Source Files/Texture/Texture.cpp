#include <gl\glew.h>
#include <QtCore\qfile.h>
#include "Texture\Texture.h"
#include "Texture\TextureManager.h"
#include "Shader\MaterialManager.h"

#include "TropicalEngineApplication.h"

#include <QtCore\qdebug.h>

Texture::Texture(QString fileUrl)
{
	this->fileUrl = fileUrl;
	Load();	//maybe not always should be loaded into GPU when it is load
}


Texture::~Texture(void)
{
	for (Material* material : TropicalEngineApplication::instance()->materialManager->materials)
	{
		///TODO: set texture parameters equal to this to value typical for
		//unneccessary if caled from TextureManager
	}
}

void Texture::Load()
{
	QImage textureData;
	if (fileUrl.endsWith(".tga", Qt::CaseInsensitive))
	{
		textureData = QImage(fileUrl).mirrored(false, true);
	}
	else
	{
		textureData = QImage(fileUrl);
	}

	textureData = textureData.convertToFormat(QImage::Format_RGBA8888);

	//glActiveTexture(GL_TEXTURE0 + TropicalEngineApplication::instance()->textureManager->getTextureIterator());

	glGenTextures(1, &textureLocation);
    glBindTexture(GL_TEXTURE_2D, textureLocation);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width(), textureData.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.bits());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::ActivateTexture(GLuint location)
{
	glActiveTexture(GL_TEXTURE0 + TropicalEngineApplication::instance()->textureManager->getTextureIterator());
	glBindTexture(GL_TEXTURE_2D, textureLocation);
	glUniform1i(location, TropicalEngineApplication::instance()->textureManager->getTextureIterator());
	//int t = TropicalEngineApplication::instance()->textureManager->getTextureIterator();
	TropicalEngineApplication::instance()->textureManager->incrementTextureIterator();
}

QString Texture::toXML()
{
	return QString(getIndent() + "<Texture filepath = \"" + fileUrl + "\"/>\n");
}

QJsonObject Texture::toJSON()
{
	return QJsonObject();
}