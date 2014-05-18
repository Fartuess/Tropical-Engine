#pragma once
//#ifndef ModelManager_Included
//#define ModelManager_Included

#include "Models_header.h"
#include <string>
#include <map>

class ModelManager
{
public:
	static map<string, Model*> models;

	static list<ModelComponent*> modelComponents;
	
	static void Load(string name, Model* mesh);	///Loads model from a file

	static void Init(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light);	///Initializes all models in model manager
};
//#endif //ModelManager_Include