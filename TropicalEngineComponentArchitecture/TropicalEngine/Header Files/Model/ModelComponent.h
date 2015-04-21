#pragma once
#include "Model\RenderComponent.h"

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
protected:
	void InitializeComponentType() override;
public:
	void Evaluate();// override;
	void Draw(CameraComponent* viewer);// override;

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
};

