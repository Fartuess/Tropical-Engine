#pragma once
#include <QtCore\qstring.h>

class Texture
{
public:
	Texture(QString fileUrl);
	~Texture(void);

	static Texture nullTexture;
};

