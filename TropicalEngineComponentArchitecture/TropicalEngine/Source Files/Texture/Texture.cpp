#include <gl/glew.h>

#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>

#include <Texture/Texture.h>
#include <Texture/TextureManager.h>
#include <Shader/MaterialManager.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	Texture::Texture(QString name)
	{
		this->name = name;
	}

	Texture::Texture(QString fileUrl, QString name) : Texture(name)
	{
		this->fileUrl = fileUrl;
		Load();	//maybe not always should be loaded into GPU when it is load
	}

	Texture::~Texture(void)
	{
		//for (Material* material : TropicalEngineApplication::instance()->materialManager->materials)
		//{
		//	///TODO: set texture parameters equal to this to value typical for
		//	//unneccessary if caled from TextureManager
		//}
		if (textureLocation != 0)
		{
			glDeleteTextures(1, &textureLocation);
		}
	}

	QString Texture::getName()
	{
		return name;
	}

	void Texture::setName(QString name)
	{
		///TODO: change keyname in Texture Managers.
		this->name = name;
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

		Create();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width(), textureData.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.bits());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::Create()
	{
		glGenTextures(1, &textureLocation);
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

	void Texture::ActivateTexture(GLuint location)
	{
		glActiveTexture(GL_TEXTURE0 + TropicalEngineApplication::instance()->textureManager->getTextureIterator());
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glUniform1i(location, TropicalEngineApplication::instance()->textureManager->getTextureIterator());
		//int t = TropicalEngineApplication::instance()->textureManager->getTextureIterator();
		TropicalEngineApplication::instance()->textureManager->incrementTextureIterator();
	}

	//QString Texture::toXML()
	//{
	//	return QString(getIndent() + "<Texture filepath = \"" + fileUrl + "\"/>\n");
	//}

	QJsonObject Texture::toJSON()
	{
		QJsonObject JSON = QJsonObject();
		JSON["name"] = name;
		JSON["url"] = fileUrl;

		return JSON;
	}

	IDeserializableFromJSON* Texture::fromJSON(QJsonObject JSON)
	{
		QString name = JSON["name"].toString();
		QString fileUrl = JSON["url"].toString();

		Texture* texture = new Texture(fileUrl, name);

		return texture;
	}

}