#include "Shader\Shader.h"
#include "Shader\ShaderManager.h"
#include "Shader\Material.h"
#include "Shader\MaterialManager.h"
#include "Model\ModelComponent.h"
#include "Model\ModelController.h"

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

void MaterialManager::UseMaterial(QString name)
{
	materials[name]->Use();
}

void MaterialManager::UseMaterial(Material* material)
{
	material->Use();
}

void MaterialManager::FlushMaterial(QString name, bool forced)
{
	///TODO: implement it.
	if (!materials.contains(name))
		return;
	Material* material = materials[name];
	if (forced)
	{
		for (ModelComponent* modelComponent : TropicalEngineApplication::instance()->modelController->modelComponents)
		{
			if (modelComponent->material == material)
				modelComponent->material = material->getShader()->defaultMaterial;
		}
		delete material;
	}
	else
	{
		for (ModelComponent* modelComponent : TropicalEngineApplication::instance()->modelController->modelComponents)
		{
			if (modelComponent->material == material)
				return;
		}
		delete material;
	}
}
