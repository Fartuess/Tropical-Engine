#include "Shader.h"
#include "Material.h"
#include "MaterialManager.h"
#include "ModelComponent.h"
#include "ModelController.h"

Material::Material(Shader* shader, void* params, QString name)
{
	this->shader = shader;
	MaterialManager::Instance().materials.insert(name, this);
}

Material::~Material(void)
{
	foreach(ModelComponent* modelComponent, ModelController::Instance().modelComponents)
	{
		if(modelComponent->material == this)
			modelComponent->material = &this->getShader()->defaultMaterial;
	}
}

Shader* Material::getShader()
{
	return shader;
}