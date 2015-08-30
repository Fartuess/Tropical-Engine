#pragma once

#include "LightComponent.h"

class PointLightComponent : public LightComponent
{
public:
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
	  * @param isCastingShadows Decides if this light should cast shadows.
	  */
	PointLightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f, bool isCastingShadows = false);
	
	/**
	  * \brief Destructor of PointLightComponent.
	  */
	~PointLightComponent(void);

	/**
	  * \brief Initialized type in global typemap.
	  */
	static PointLightComponent InitializeType();

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

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;

	/**
	  * \brief Serializes PointLightComponent to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes PointLightComponent from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return DirectionalLightComponent object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	/**
	  * \brief Simple Constructor used to create PointLightComponent instance while serializing.
	  */
	PointLightComponent();

	void InitializeComponentType() override;

private:
	float radius;

	static PointLightComponent templateObject;
};

