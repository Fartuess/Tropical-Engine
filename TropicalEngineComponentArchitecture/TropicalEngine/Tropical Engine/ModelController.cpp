#include "ModelController.h"
#include "ModelComponent.h"


ModelController::ModelController(void)
{
}


ModelController::~ModelController(void)
{
	foreach (ModelComponent* modelComponent, modelComponents)
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
	foreach (ModelComponent* modelComponent, modelComponents)
	{
		modelComponent->Draw(viewer);
	}
}