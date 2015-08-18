#pragma once
#include <QtCore/qmap.h>
#include <QtCore/qstring.h>

#include "Asset.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	static void addAssetType(QString name, ISerializableJSON* typeHandle);
	static ISerializableJSON* getTypeHandle(QString name);
	static ISerializableJSON& createAsset(QJsonObject JSON);
	//void addAsset();

private:
	static QMap<QString, ISerializableJSON*> assetTypes;
	//QMap<QString, Asset> assets;
};

