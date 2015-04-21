#pragma once

#include <QtCore/qstring.h>

#include "Serialization/ISerializableToJSON.h"
#include "Serialization/IDeserializableFromJSON.h"

class Asset : public ISerializableToJSON, public IDeserializableFromJSON
{
private:
	static Asset templateObject;
public:
	QString name;
	QString type;

	IDeserializableFromJSON* asset;

	Asset();
	~Asset();
	static Asset InitializeType();

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON& fromJSON(QJsonObject JSON) override;
};

