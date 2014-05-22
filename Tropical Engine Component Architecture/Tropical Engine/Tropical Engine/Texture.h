#pragma once
#include <QtCore\qstring.h>
#include <GL/glew.h>
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

