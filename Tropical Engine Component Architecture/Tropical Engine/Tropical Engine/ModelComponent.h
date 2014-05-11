#pragma once
#include "RenderComponent.h"

class Model;

class ModelComponent :
	public RenderComponent
{
public:
	Model* model;
private:
	bool castingShadows;
public:
	ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows = false);
	~ModelComponent(void);

	void Evaluate() override;
	void Draw(CameraComponent* viewer) override;

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);
};

