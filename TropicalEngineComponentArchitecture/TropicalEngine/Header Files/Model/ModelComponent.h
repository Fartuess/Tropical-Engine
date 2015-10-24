#pragma once
#include "RenderComponent.h"

class Model;

/**
  * Component for rendering models.
  */
class ModelComponent : public RenderComponent
{
public:
	TYPENAME("Model Component")

	/**
	  * \brief Model used for this component.
	  */
	Model* model;

	/**
	  * \brief Constructor of ModelComponent.
	  *
	  * @param owner Entity object to which ModelComponent will be attached to.
	  * @param material Material to be set for this component.
	  * @param model Model to be drawn with this component.
	  * @param castingShadows Decides if this model should cast shadows.
	  */
	ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows = false);

	/**
	  * \brief Default destructor
	  */
	~ModelComponent(void);

	static ModelComponent InitializeType();

	void Evaluate() override;

	/**
	* \brief Draws the Component.
	*
	* @param Draws from perspective of this camera.
	*/
	void Draw(CameraComponent* viewer) override;

	/**
	  * \brief Gets information if this model is casting shadows.
	  *
	  * @return Information if this model is casting shadows.
	  */
	bool isCastingShadows();

	/**
	  * \brief Sets if this model should cast shadows.
	  *
	  * @param isCastingShadows If this model should cast shadows.
	  */
	void isCastingShadows(bool isCastingShadows);

	/**
	  * \brief Serializes ModelComponent to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes ModelComponent from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return ModelComponent object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	ModelComponent();
	void InitializeComponentType() override;

private:
	bool castingShadows;

	static ModelComponent templateObject;
};

