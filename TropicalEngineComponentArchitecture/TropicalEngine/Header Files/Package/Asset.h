#pragma once

#include <QtCore/qstring.h>

#include "Serialization/ISerializableToJSON.h"
#include "Serialization/IDeserializableFromJSON.h"

class Asset : public ISerializableToJSON, public IDeserializableFromJSON
{
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

private:
	static Asset templateObject;
};

