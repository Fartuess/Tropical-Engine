#pragma once
#include <QtCore/qlist.h>

class CameraComponent;
class ModelComponent;

class ModelController
{
public:
	friend class ModelComponent;
	friend class Material;
	friend class MaterialManager;

	ModelController(void);
	~ModelController(void);
	void AddComponent(ModelComponent* component);

	void DrawAll(CameraComponent* viewer);

private:
	QList<ModelComponent*> modelComponents;

	void DropComponent(ModelComponent* component);
};

