#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qpair.h>
#include <QtCore/qmap.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"
#include "Serialization/IDeserializableFromJSON.h"
#include "Asset.h"

class Package : public ISerializableToXML, public ISerializableToJSON, public IDeserializableFromJSON
{
public:
	Package(QString name);
	~Package(void);

	static Package InitializeType();

	QString getName();
	void setName(QString name);

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON& fromJSON(QJsonObject JSON) override;

private:
	QMap<QString, Asset> assets;
	QString name;

	static Package templateObject;
};

