#pragma once

//#include "Scene_header.h"
#include "RenderComponent.h"
#include "Shaders_header.h"
#include "Models_header.h"

class ModelComponent: public RenderComponent
{
public:
	Model* model;
	Material* material;

	ModelComponent(GameObject* owner, Model* model, Material* material);

	void Draw(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);
};