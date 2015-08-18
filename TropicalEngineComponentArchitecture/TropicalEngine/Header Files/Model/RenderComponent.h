#pragma once
#include <QtCore/qlist.h>

#include <Component/Component.h>

class RenderComponent : public Component
{
public:
	class Material* material;
//protected:	//temporarily public
	QList<class LightComponent*> lightedBy;

	RenderComponent(Entity* owner, class Material* material);
	~RenderComponent(void);

	virtual void Evaluate() = 0;
	virtual void Draw(class CameraComponent* viewer) = 0;

	QString getTypeName() override;

protected:
	RenderComponent();

	void InitializeComponentType() override;
};

