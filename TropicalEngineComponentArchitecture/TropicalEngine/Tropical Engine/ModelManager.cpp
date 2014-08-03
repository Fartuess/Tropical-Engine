#include "ModelManager.h"
#include "Model.h"

ModelManager::ModelManager(void)
{
	///TODO: implement it.
}

ModelManager::~ModelManager(void)
{
	foreach (Model* model, models)
	{
		delete model;
	}
}

Model* ModelManager::getModel(QString name)
{
	return models[name];
}

void ModelManager::Load(QString fileUrl, QString name)
{
	models.insert(name, new Model(fileUrl));
}

void ModelManager::Load(Model* model, QString name)
{
	models.insert(name, model);
}

void ModelManager::FlushModel(QString name, bool forced)
{
	//if(!models.contains(name))
	//	return;
	//Model* model = models[name];
	//if(forced)
	//{
	//	foreach (ModelComponent* modelComponent, modelComponents)
	//	{
	//		if(modelComponent->model == model)
	//			DropComponent(modelComponent);
	//	}
	//	delete model;
	//}
	//else
	//{
	//	foreach (ModelComponent* modelComponent, modelComponents)
	//	{
	//		if(modelComponent->model == model)
	//			return;
	//	}
	//	models.remove(name);
	//	delete model;
	//}
}
