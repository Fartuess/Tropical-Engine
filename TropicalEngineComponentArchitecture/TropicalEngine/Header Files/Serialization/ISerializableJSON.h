#pragma once
#include <Serialization/ISerializableToJSON.h>
#include <Serialization/IDeserializableFromJSON.h>

class ISerializableJSON : public ISerializableToJSON, public IDeserializableFromJSON {};
