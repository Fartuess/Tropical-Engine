#pragma once
#include <GL/glew.h>

#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>

#include <Serialization/ISerializableJSON.h>

class Texture : public ISerializableJSON
{
public:
	Texture(QString fileUrl, QString name = "");
	~Texture(void);

	static Texture nullTexture;

	QString getName();
	void setName(QString name);

	void Load();

	void ActivateTexture(GLuint location);

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	QString fileUrl;	///TODO: Figure out how to implement changing paths.
	QString name;
	//GLenum textureTarget;	//what for?
	GLuint textureLocation;
	//QPixmap textureData;	///TODO: figure out if it shpuld be stored in main memory.
};

