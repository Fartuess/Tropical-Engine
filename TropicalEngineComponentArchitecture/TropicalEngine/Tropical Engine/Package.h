#pragma once
#include <QtCore\qstring.h>
#include <QtCore\qpair.h>
#include <QtCore\qmap.h>
#include "ISerializableToXML.h"

enum class AssetType
	{
		Entity,
		Shader,
		Material,
		Texture,
		Model
	};

class Package : public ISerializableToXML
{
	class Asset : public ISerializableToXML
	{
	public:
		AssetType type;
		void* asset_ptr;

		Asset(AssetType type, void* asset_ptr);

		QString toXML() override;
	};

private:
	QMap<QString, Asset> assets;
	QString name;
public:
	Package(QString name);
	~Package(void);

	QString getName();
	void setName(QString name);

	QString toXML() override;
};

