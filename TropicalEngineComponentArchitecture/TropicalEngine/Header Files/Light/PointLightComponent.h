#pragma once

#include "LightComponent.h"

namespace TropicalEngine
{

	// TODO: Finish documenting PointLightComponent class.
	#pragma region documentation
	/**
	  * \brief Component enlighting Scene with point light.
	  */
	#pragma endregion
	class PointLightComponent : public LightComponent
	{
	public:
		TYPENAME(PointLightComponent)

		#pragma region documentation
		/**
		  * \brief Attenuation exponent of the light.
		  */
		#pragma endregion
		float attenuation;

		#pragma region documentation
		/**
		  * \brief Constructor of PointLightComponent.
		  *
		  * @param owner Entity object the light will be attached to.
		  * @param color Color of the light.
		  * @param brightness Brightness of the light.
		  * @param radius Radius of the light.
		  * @param attenuation Attenuation exponent of the light.
		  * @param isCastingShadows Decides if this light should cast shadows.
		  */
		#pragma endregion
		PointLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f, bool isCastingShadows = false);
		#pragma region documentation
		/**
		  * \brief Destructor of PointLightComponent.
		  */
		#pragma endregion
		~PointLightComponent(void);

		#pragma region documentation
		/**
		  * \brief Initialized type in global typemap.
		  */
		#pragma endregion
		static PointLightComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Gets radius of the light.
		  *
		  * @return Radius of the light.
		  */
		#pragma endregion
		float getRadius();
		#pragma region documentation
		/**
		  * \brief Sets radius of the light.
		  *
		  * @param radius Radius to be set for light.
		  */
		#pragma endregion
		void setRadius(float radius);

		virtual void Evaluate() override;
		virtual void DrawShadows() override;

		#pragma region documentation
		/**
		  * \brief Serializes PointLightComponent to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes PointLightComponent from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return PointLightComponent object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create PointLightComponent instance while serializing.
		  */
		#pragma endregion
		PointLightComponent();

		void InitializeComponentType() override;

	private:
		float radius;

		static PointLightComponent templateObject;
	};

}