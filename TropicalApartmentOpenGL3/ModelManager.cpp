#pragma once

#include "Models_header.h"

using namespace std;

typedef pair <string, Model*> mElement;

map<string, Model*> ModelManager::models;

void ModelManager::Load(string name, Model* mesh)
{
		models.insert(mElement (name, mesh));
}

void ModelManager::Init(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light)
{
	for( map<string, Model*>::iterator iter=models.begin(); iter != models.end(); ++iter )
		{
			(*iter).second->initWavefront(g_viewMatrix, g_light);
		}
}