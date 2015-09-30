#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

/**
  * Asset class.
  */
class Asset : public ISerializableJSON
{
public:

	/**
	  * \brief Name of the asset.
	  */
	QString name;

	/**
	  * \brief Name of type of this asset.
	  */
	QString type;

	/**
	  * \brief Resource of this asset.
	  */
	ISerializableJSON* asset;

	/**
	  * \brief Constructor of Asset.
	  *
	  * @param name Name of new Asset.
	  * @param asset Resource to be stored in Asset.
	  */
	Asset(QString name, ISerializableJSON* asset);
	//Asset(QString name, QString type, QJsonObject JSON);

	/**
	  * \brief Default destructor.
	  */
	~Asset();
	//static Asset InitializeType();

	QString getTypeName() override;

	/**
	  * \brief Serializes Asset to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes Asset from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return Asset object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	Asset();
//	static Asset templateObject;
};

