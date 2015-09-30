#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>

#include <Serialization/ISerializableJSON.h>

/**
  * Class for Texture.
  */
class Texture : public ISerializableJSON
{
public:
	/**
	  * \brief Constructor for Texture class.
	  *
	  * @param fileUrl path to file texture will be loaded from.
	  * @param name Name to be set for Texture.
	  */
	Texture(QString fileUrl, QString name = "");

	/**
	  * \brief Default destructor.
	  */
	~Texture(void);

	/**
	  * \brief Texture to be used if needed texture can't be found.
	  */
	static Texture nullTexture;

	/**
	  * \brief Gets name of the Texture.
	  *
	  * @return Name of the Texture.
	  */
	QString getName();

	/**
	  * \brief Sets name of the Texture.
	  *
	  * @param name Name to be set.
	  */
	void setName(QString name);

	/**
	  * \brief Loads the texture.
	  */
	void Load();

	/**
	  * \brief Sets this texture as the Active one in OpenGL context.
	  *
	  * @param location I DON'T REMEMBER EXACTLY. IT IS MAINLY FOR TEXTUREMANAGER.
	  */
	void ActivateTexture(GLuint location);

	QString getTypeName() override;

	/**
	  * \brief Serializes Texture to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes Texture from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return Texture object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	QString fileUrl;	///TODO: Figure out how to implement changing paths.
	QString name;
	//GLenum textureTarget;	//what for?
	GLuint textureLocation;
	//QPixmap textureData;	///TODO: figure out if it shpuld be stored in main memory.
};

