#pragma once
#include <QtCore\qstring.h>
#include <GL/glew.h>
#include <QtGui\qpixmap.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Texture : public ISerializableToXML, public ISerializableToJSON
{
private:
	QString fileUrl;
	//GLenum textureTarget;	//what for?
	GLuint textureLocation;
	//QPixmap textureData;	///TODO: figure out if it shpuld be stored in main memory.
public:
	Texture(QString fileUrl);
	~Texture(void);

	static Texture nullTexture;

	void Load();

	void ActivateTexture(GLuint location);

	QString toXML() override;
	QJsonObject toJSON() override;
};

