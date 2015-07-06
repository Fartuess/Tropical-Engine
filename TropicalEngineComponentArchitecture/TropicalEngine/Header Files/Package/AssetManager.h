#pragma once

#include <QtCore/qmap.h>
#include <QtCore/qstring.h>

#include "Package/Asset.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	static void addAssetType(QString name, IDeserializableFromJSON* typeHandle);
	static IDeserializableFromJSON* getTypeHandle(QString name);

private:
	static QMap<QString, IDeserializableFromJSON*> assetTypes;
	QMap<QString, Asset> assets;
};

