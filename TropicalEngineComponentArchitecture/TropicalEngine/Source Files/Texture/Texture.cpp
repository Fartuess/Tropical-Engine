#include <gl/glew.h>

#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>

#include <Texture/Texture.h>
#include <Texture/TextureManager.h>
#include <Shader/MaterialManager.h>

namespace TropicalEngine
{

	Texture::Texture(QString name)
	{
		this->name = name;
	}

	Texture::Texture(QString fileUrl, QString name) : Texture(name)
	{
		this->fileUrl = fileUrl;
		//Load();	//maybe not always should be loaded into GPU when it is load
		TextureManager::instance().Load(name, fileUrl, this);
	}

	Texture::~Texture(void)
	{
		//for (Material* material : TropicalEngineApplication::instance()->materialManager->materials)
		//{
		//	// TODO: set texture parameters equal to this to value typical for
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
		// TODO: change keyname in Texture Managers.
		this->name = name;
	}

	// TODO: Remove this method.
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

		Create(GL_REPEAT, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width(), textureData.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.bits());
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::Create(int wrappingS, int wrappingT)
	{
		glGenTextures(1, &textureLocation);
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);

	}

	void Texture::ActivateTexture(GLuint location)
	{
		glActiveTexture(GL_TEXTURE0 + TextureManager::instance().getTextureIterator());
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glUniform1i(location, TextureManager::instance().getTextureIterator());
		//int t = TropicalEngineApplication::instance()->textureManager->getTextureIterator();
		TextureManager::instance().incrementTextureIterator();
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