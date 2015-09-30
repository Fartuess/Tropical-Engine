#pragma once
#include <Serialization/ISerializableToJSON.h>
#include <Serialization/IDeserializableFromJSON.h>

/**
  * Interface for Serialzing and Deserializing JSON objects.
  */
class ISerializableJSON : public ISerializableToJSON, public IDeserializableFromJSON {};
