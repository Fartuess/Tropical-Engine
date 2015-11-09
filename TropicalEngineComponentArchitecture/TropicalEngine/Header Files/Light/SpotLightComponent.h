#pragma once
#include "LightComponent.h"

class SpotLightComponent : public LightComponent
{
public:
	TYPENAME("SpotLight Component")

	/**
	  * \brief Attenuation exponent of the light.
	  */
	float attenuation;
	
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
	SpotLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f,
		float outerConeRadius = 45.0f, float innerConeRadius = 0.0f, bool isCastingShadows = false);

	/**
	  * \brief Destructor of SpotLightComponent.
	  */
	~SpotLightComponent(void);

	/**
	  * \brief Initialized type in global typemap.
	  */
	static SpotLightComponent InitializeType();

	/**
	  * \brief Gets radius of the light.
	  *
	  * @return Radius of the light.
	  */
	float getRadius();

	/**
	  * \brief Sets radius of the light.
	  *
	  * @param radius Radius to be set for light.
	  */
	void setRadius(float radius);

	/**
	  * \brief Gets attenuation of the light.
	  *
	  * @return Attenuation of the light.
	  */
	float getAttenuation();

	/**
	  * \brief Sets attenuation of the light.
	  *
	  * @param attenuation Attenuation to be set for light.
	  */
	void setAttenuation(float attenuation);

	/**
	  * \brief Gets OuterConeRadius of the light.
	  *
	  * @return OuterConeRadius of the light.
	  */
	float getOuterConeRadius();

	/**
	  * \brief Sets OuterConeRadius of the light.
	  *
	  * @param outerConeRadius OuterConeRadius to be set for light.
	  */
	void setOuterConeRadius(float outerConeRadius);

	/**
	  * \brief Gets InnerConeRadius of the light.
	  *
	  * @return InnerConeRadius of the light.
	  */
	float getInnerConeRadius();

	/**
	  * \brief Sets InnerConeRadius of the light.
	  *
	  * @param innerConeRadius InnerConeRadius to be set for light.
	  */
	void setInnerConeRadius(float innerConeRadius);

	virtual void Evaluate() override;
	virtual void DrawShadows() override;

	/**
	  * \brief Serializes SpotLightComponent to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes SpotLightComponent from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return SpotLightComponent object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:

	/**
	  * \brief Simple Constructor used to create PointLightComponent instance while serializing.
	  */
	SpotLightComponent();

	void InitializeComponentType() override;

private:
	float radius;
	float outerConeRadius;
	float innerConeRadius;

	class RenderTexture* shadowmap = nullptr;

	static SpotLightComponent templateObject;
};

