#pragma once
#include "component.h"
#include <QtCore\qlist.h>

class Material;
class LightComponent;
class CameraComponent;

class RenderComponent :
	public Component
{
public:
	Material* material;
private:
	QList<LightComponent*> lightedBy;
public:
	RenderComponent(Entity* owner, Material* material);
	~RenderComponent(void);

	virtual void Evaluate() = 0;
	virtual void Draw(CameraComponent* viewer) = 0;
};

