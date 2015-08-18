#pragma once
#include "RenderComponent.h"

class Model;

class ModelComponent : public RenderComponent
{
public:
	Model* model;

	ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows = false);
	~ModelComponent(void);

	static ModelComponent InitializeType();

	void Evaluate();// override;
	void Draw(CameraComponent* viewer);// override;

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	ModelComponent();
	void InitializeComponentType() override;

private:
	bool castingShadows;

	static ModelComponent templateObject;
};

