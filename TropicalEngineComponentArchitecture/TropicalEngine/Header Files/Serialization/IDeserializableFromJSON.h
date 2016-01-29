#pragma once
#include <QtCore/qjsonobject.h>

#include <Utills/INamedType.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Interface for deserializing objects from JSON.
	  */
	#pragma endregion
	class IDeserializableFromJSON : virtual public INamedType
	{
	public:
		#pragma region documentation
		/**
		  * \brief Creates object from JSON.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Created object.
		  */
		#pragma endregion
		virtual IDeserializableFromJSON* fromJSON(QJsonObject JSON) = 0;
	};

}