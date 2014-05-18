#include "ModelComponent.h"

ModelComponent::ModelComponent(GameObject* owner, Model* model, Material* material):RenderComponent(owner)
{
	this->model = model;
	this->material = material;
	ModelManager::modelComponents.push_back(this);
}

void ModelComponent::Draw(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16])
{
	if(model!=NULL)
		model->updateWavefront(position, rotation, scale, time, scaleMatrix);
}