#pragma once
#include <Component/Component.h>

#include <Utills/IUpdateable.h>

namespace TropicalEngine
{

	class TempPlayerComponent : public Component, public IUpdateable
	{
	public:
		TYPENAME(TempPlayerComponent)

		TempPlayerComponent(Entity* owner);
		~TempPlayerComponent(void);

		void OnUpdate(int deltaTime) override;

		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		TempPlayerComponent();

		void InitializeComponentType() override;
	private:
		static TempPlayerComponent InitializeType();
	};

}