#pragma once
#include <QtCore/qstring.h>
#include <GL/glew.h>
#include <QtGui/qpixmap.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Texture : public ISerializableToXML, public ISerializableToJSON
{
public:
	Texture(QString fileUrl);
	~Texture(void);

	static Texture nullTexture;

	QString getName();
	void setName(QString name);

	void Load();

	void ActivateTexture(GLuint location);

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;

private:
	QString fileUrl;	///TODO: Figure out how to implement changing paths.
	QString name;
	//GLenum textureTarget;	//what for?
	GLuint textureLocation;
	//QPixmap textureData;	///TODO: figure out if it shpuld be stored in main memory.
};

