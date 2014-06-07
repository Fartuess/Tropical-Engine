#include "Shader.h"
#include "Material.h"
#include "MaterialManager.h"
#include "ModelComponent.h"
#include "ModelController.h"

#include "TropicalEngineApplication.h"

Material::Material(Shader* shader, void* params, QString name)
{
	this->shader = shader;
	TropicalEngineApplication::instance()->materialManager->materials.insert(name, this);
}

Material::~Material(void)
{
	foreach(ModelComponent* modelComponent, TropicalEngineApplication::instance()->modelController->modelComponents)
	{
		if(modelComponent->material == this)
			modelComponent->material = &this->getShader()->defaultMaterial;
	}
}

Shader* Material::getShader()
{
	return shader;
}