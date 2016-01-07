#pragma once
#include <Serialization/ISerializableToJSON.h>
#include <Serialization/IDeserializableFromJSON.h>

namespace TropicalEngine
{

	/**
	  * Interface for Serialzing and Deserializing JSON objects.
	  */
	class ISerializableJSON : public ISerializableToJSON, public IDeserializableFromJSON {};

}