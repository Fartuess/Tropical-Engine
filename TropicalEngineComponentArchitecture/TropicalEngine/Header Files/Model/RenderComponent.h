#pragma once
#include <QtCore\qlist.h>
#include "Component\Component.h"

class Material;
class LightComponent;
class CameraComponent;

class RenderComponent :
	public Component
{
public:
	Material* material;
//protected:	//temporarily public
	QList<LightComponent*> lightedBy;
protected:
	RenderComponent();
public:
	RenderComponent(Entity* owner, Material* material);
	~RenderComponent(void);
protected:
	void InitializeComponentType() override;
public:
	virtual void Evaluate() = 0;
	virtual void Draw(CameraComponent* viewer) = 0;

	QString getTypeName() override;
};

