#pragma once

#include"Shaders_header.h"
#include <string>
#include <map>

using namespace std;

class ShaderManager
{
public:
	static map<string, Shader*> shaders;

	static void Load(string name, Shader* shader);	///Loads shader from a file
};