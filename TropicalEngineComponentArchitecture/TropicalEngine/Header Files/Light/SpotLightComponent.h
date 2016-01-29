#pragma once
#include "LightComponent.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Component enlighting Scene with spot light.
	  */
	#pragma endregion
	class SpotLightComponent : public LightComponent
	{
	public:
		TYPENAME(SpotLightComponent)

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
		  * @param outerConeRadius Outer cone radius of light.
		  * @param innerConeRadius Inner cone of light.
		  * @param isCastingShadows Decides if this light should cast shadows.
		  */
		#pragma endregion
		SpotLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f,
			float outerConeRadius = 45.0f, float innerConeRadius = 0.0f, bool isCastingShadows = false);
		#pragma region documentation
		/**
		  * \brief Destructor of SpotLightComponent.
		  */
		#pragma endregion
		~SpotLightComponent(void);

		#pragma region documentation
		/**
		  * \brief Initialized type in global typemap.
		  */
		#pragma endregion
		static SpotLightComponent InitializeType();

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

		#pragma region documentation
		/**
		  * \brief Gets attenuation of the light.
		  *
		  * @return Attenuation of the light.
		  */
		#pragma endregion
		float getAttenuation();
		#pragma region documentation
		/**
		  * \brief Sets attenuation of the light.
		  *
		  * @param attenuation Attenuation to be set for light.
		  */
		#pragma endregion
		void setAttenuation(float attenuation);

		#pragma region documentation
		/**
		  * \brief Gets OuterConeRadius of the light.
		  *
		  * @return OuterConeRadius of the light.
		  */
		#pragma endregion
		float getOuterConeRadius();
		#pragma region documentation
		/**
		  * \brief Sets OuterConeRadius of the light.
		  *
		  * @param outerConeRadius OuterConeRadius to be set for light.
		  */
		#pragma endregion
		void setOuterConeRadius(float outerConeRadius);
		#pragma region documentation
		/**
		  * \brief Gets InnerConeRadius of the light.
		  *
		  * @return InnerConeRadius of the light.
		  */
		#pragma endregion
		float getInnerConeRadius();
		#pragma region documentation
		/**
		  * \brief Sets InnerConeRadius of the light.
		  *
		  * @param innerConeRadius InnerConeRadius to be set for light.
		  */
		#pragma endregion
		void setInnerConeRadius(float innerConeRadius);

		virtual void Evaluate() override;
		virtual void DrawShadows() override;

		#pragma region documentation
		/**
		  * \brief Serializes SpotLightComponent to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;

		#pragma region documentation
		/**
		  * \brief Deserializes SpotLightComponent from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return SpotLightComponent object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create PointLightComponent instance while serializing.
		  */
		#pragma endregion
		SpotLightComponent();

		void InitializeComponentType() override;

	private:
		float radius;
		float outerConeRadius;
		float innerConeRadius;

		class RenderTexture* shadowmap = nullptr;

		static SpotLightComponent templateObject;
	};

}