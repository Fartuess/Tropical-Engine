#pragma once
#include <Serialization/ISerializableToJSON.h>
#include <Serialization/IDeserializableFromJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Interface for Serialzing and Deserializing JSON objects.
	  */
	#pragma endregion
	class ISerializableJSON : public ISerializableToJSON, public IDeserializableFromJSON {};

}