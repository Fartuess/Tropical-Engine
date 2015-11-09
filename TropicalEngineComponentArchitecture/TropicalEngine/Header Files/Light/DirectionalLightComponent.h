#pragma once
#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{
public:
	TYPENAME("DirectionalLight Component")

	/**
	* \brief Constructor of DirectionalLightComponent.
	*
	* @param owner Entity object the light will be attached to.
	* @param color Color of the light.
	* @param direction Direction vector defining angle of the light.
	* @param brightness Brightness of the light.
	* @param isCastingShadows Decides if this light should cast shadows.
	*/
	DirectionalLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f), float brightness = 1.0f, bool isCastingShadows = false);
	
	/**
	  * \brief Destructor for DirectionalLightComponent.
	  */
	~DirectionalLightComponent(void);

	static DirectionalLightComponent InitializeType();

	/**
	  * \brief Gets direction vector of the light.
	  *
	  * @return Direction vector of the light.
	  */
	glm::vec3 getDirection();

	/**
	  * \brief Sets direction vector of the light.
	  *
	  * @param direction Direction of the light.
	  */
	void setDirection(glm::vec3 direction);

	virtual void Evaluate() override;
	virtual void DrawShadows() override;

	/**
	  * \brief Serializes Component to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes DirectionalLightComponent from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return DirectionalLightComponent object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	/**
	  * \brief Simple Constructor used to create DirectionalLightComponent instance while serializing.
	  */
	DirectionalLightComponent();

	/**
	  * \brief Initialized type in global typemap.
	  */
	void InitializeComponentType() override;

private:
	glm::vec3 direction;

	static DirectionalLightComponent templateObject;
};

