#include "ModelComponent.h"
#include "ModelManager.h"
#include "Entity.h"


ModelComponent::ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows):RenderComponent(owner, material)
{
	this->model = model;
	this->castingShadows = castingShadows;
	ModelManager::Instance().modelComponents.append(this);
}


ModelComponent::~ModelComponent(void)
{
	if(owner != nullptr)
	{
		ModelManager::Instance().modelComponents.removeOne(this);
	}
}

void ModelComponent::Evaluate()
{
	///TODO: implement it.
}

void ModelComponent::Draw(CameraComponent* viewer)
{
	///TODO: implement it.
}

bool ModelComponent::isCastingShadows()
{
	return castingShadows;
}

void ModelComponent::isCastingShadows(bool isCastingShadows)
{
	castingShadows = isCastingShadows;
}
