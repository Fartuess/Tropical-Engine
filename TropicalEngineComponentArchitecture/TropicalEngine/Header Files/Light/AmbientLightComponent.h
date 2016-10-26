#pragma once

#include "LightComponent.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Component enlighting Scene with ambient light.
	  */
	#pragma endregion
	class AmbientLightComponent : public LightComponent
	{
	public:
		TYPENAME(AmbientLightComponent)

		#pragma region documentation
		/**
		  * \brief Constructor for AmbientLightComponent.
		  *
		  * @param owner Entity object the light will be attached to.
		  * @param color Color of the light.
		  * @param brightness Brightness of the light.
		  */
		#pragma endregion
		AmbientLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f);
		#pragma region documentation
		/**
		  * \brief Destructor for AmbientLightComponent.
		  */
		#pragma endregion
		~AmbientLightComponent();

		static AmbientLightComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Serializes Component to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes DirectionalLightComponent from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return DirectionalLightComponent object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create AmbientLightComponent instance while serializing.
		  */
		#pragma endregion
		AmbientLightComponent();

		#pragma region documentation
		/**
		  * \brief Initialized type in global typemap.
		  */
		#pragma endregion
		void InitializeComponentType() override;

	private:
		static AmbientLightComponent templateObject;
	};

}

