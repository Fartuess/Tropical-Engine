#pragma once

#include"Shaders_header.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
}

//prototype with temp values
Material::paramtype Material::stringToType(string type)
{
	if(type == "float") return vec;
	if(type == "Vec2") return vec2;
	if(type == "Vec3") return vec3;
	if(type == "Vec4") return vec4;
	return unknownType;
}

void Material::addVSparam(string name ,void* parameter)
{
	VSparams[name].parameter = parameter;
	//VSparams[name].type = typeid(&parameter).name;
}

void Material::addPSparam(string name ,void* parameter)
{
	PSparams[name].parameter = parameter;
	//PSparams[name].type = typeid(&parameter).name;
}