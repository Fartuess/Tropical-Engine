#pragma once
#include "Model/RenderComponent.h"

class Model;

class ModelComponent :
	public RenderComponent
{
public:
	Model* model;
private:
	bool castingShadows;

	static ModelComponent templateObject;
protected:
	ModelComponent();
public:
	ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows = false);
	~ModelComponent(void);

	static ModelComponent InitializeType();
protected:
	void InitializeComponentType() override;
public:
	void Evaluate();// override;
	void Draw(CameraComponent* viewer);// override;

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);

	QString getTypeName() override;
	//QString toXML() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON& fromJSON(QJsonObject JSON) override;
};

