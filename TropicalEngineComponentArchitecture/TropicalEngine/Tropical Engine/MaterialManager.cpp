#include "Shader.h"
#include "Material.h"
#include "MaterialManager.h"
#include "ModelComponent.h"
#include "ModelController.h"

#include "TropicalEngineApplication.h"

MaterialManager::MaterialManager(void)
{
}


MaterialManager::~MaterialManager(void)
{
	///TODO: implement it.
}

void MaterialManager::Load(Shader* shader, void* params, QString name)	//temporal definition for temporal declaration
{
	new Material(shader, params, name);
}

void MaterialManager::FlushMaterial(QString name, bool forced)
{
	///TODO: implement it.
	if(!materials.contains(name))
		return;
	Material* material = materials[name];
	if(forced)
	{
		foreach(ModelComponent* modelComponent, TropicalEngineApplication::instance()->modelController->modelComponents)
		{
			if(modelComponent->material == material)
				modelComponent->material = &material->getShader()->defaultMaterial;
		}
		delete material;
	}
	else
	{
		foreach(ModelComponent* modelComponent, TropicalEngineApplication::instance()->modelController->modelComponents)
		{
			if(modelComponent->material == material)
				return;
		}
		delete material;
	}
}
