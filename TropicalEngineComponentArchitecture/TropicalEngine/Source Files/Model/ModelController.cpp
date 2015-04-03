#include "Model\ModelController.h"
#include "Model\ModelComponent.h"

ModelController::ModelController(void)
{
	///TODO: implement it.
}

ModelController::~ModelController(void)
{
	for (ModelComponent* modelComponent : modelComponents)
	{
		delete modelComponent;
	}
}

void ModelController::AddComponent(ModelComponent* component)
{
	modelComponents.append(component);
}

void ModelController::DropComponent(ModelComponent* component)
{
	//modelComponents.removeOne(component);	//destructor does this.
	delete component;
}

void ModelController::DrawAll(CameraComponent* viewer)
{
	for (ModelComponent* modelComponent : modelComponents)
	{
		modelComponent->Draw(viewer);
	}
}