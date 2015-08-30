#pragma once
#include <QtCore/qlist.h>

class CameraComponent;
class ModelComponent;

/**
  * Class for managing model instances in the scene.
  */
class ModelController
{
public:
	friend class ModelComponent;
	friend class Material;
	friend class MaterialManager;

	/**
	  * \brief Constructor for ModelController.
	  */
	ModelController(void);

	/**
	  * \brief Destructor for ModelController.
	  */
	~ModelController(void);

	/**
	  * \brief Adds model component to the ModelController.
	  *
	  * @param component ModelComponent to be added to the controller.
	  */
	void AddComponent(ModelComponent* component);

	/**
	  * \brief Draws all model instances in ModelController.
	  *
	  * Draws all models from certain perspective.
	  * @param viewer Camera to write models for.
	  */
	void DrawAll(CameraComponent* viewer);

private:
	QList<ModelComponent*> modelComponents;

	void DropComponent(ModelComponent* component);
};

