#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qpair.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableJSON.h>

#include "Asset.h"

class Package : public ISerializableJSON
{
public:
	Package(QString name);
	~Package(void);

	static Package InitializeType();

	QString getName();
	void setName(QString name);

	Asset* const getAsset(QString name);
	void addAsset(Asset* asset);
	Package& operator<<(Asset* asset);

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	QMap<QString, Asset*> assets;
	QString name;

	static Package templateObject;
};

