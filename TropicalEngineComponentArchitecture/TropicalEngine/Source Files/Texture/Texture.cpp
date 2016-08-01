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

	void Texture::setWrapping(int wrappingS, int wrappingT)
	{
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingT);
	}

	void Texture::setFiltering(int minFilter, int magFilter)
	{
		glBindTexture(GL_TEXTURE_2D, textureLocation);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
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