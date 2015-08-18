#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>
#include <Serialization/IDeserializableFromJSON.h>

class Asset : public ISerializableJSON
{
public:
	QString name;
	QString type;

	///TODO: Figure out how to do it.
	ISerializableJSON* asset;

	Asset(QString name, QString type, ISerializableJSON* asset);
	//Asset(QString name, QString type, QJsonObject JSON);
	~Asset();
	//static Asset InitializeType();

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	Asset();
//	static Asset templateObject;
};

