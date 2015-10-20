#pragma once
#include <Component/Component.h>

#include <Utills/IUpdateable.h>

class TempPlayerComponent : public Component, public IUpdateable
{
public:
	TempPlayerComponent(Entity* owner);
	~TempPlayerComponent(void);

	void OnUpdate(int deltaTime) override;

	QString getTypeName() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	TempPlayerComponent();

	void InitializeComponentType() override;
private:
	static TempPlayerComponent InitializeType();
};