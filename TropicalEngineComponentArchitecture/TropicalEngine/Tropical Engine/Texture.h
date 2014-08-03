#pragma once
#include <QtCore\qstring.h>
#include <GL/glew.h>
#include <QtGui\qpixmap.h>
#include "ISerializableToXML.h"

class Texture : public ISerializableToXML
{
private:
	QString filename;
	GLenum textureTarget;	//what for?
	GLuint textureLocation;
	QPixmap textureData;
public:
	Texture(QString fileUrl);
	~Texture(void);

	static Texture nullTexture;

	void Load(QString fileUrl);

	void ActivateTexture(GLuint location);

	QString toXML() override;
};

