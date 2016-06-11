#pragma once

#include "LightComponent.h"

namespace TropicalEngine
{

	class AmbientLightComponent : public LightComponent
	{
	public:
		TYPENAME(AmbientLightComponent)

		AmbientLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f);
		~AmbientLightComponent();

		static AmbientLightComponent InitializeType();

		QJsonObject toJSON() override;

		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		AmbientLightComponent();

		void InitializeComponentType() override;

	private:
		static AmbientLightComponent templateObject;
	};

}

