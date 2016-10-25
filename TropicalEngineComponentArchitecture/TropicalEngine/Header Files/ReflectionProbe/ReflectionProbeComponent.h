#pragma once

#include <glm.hpp>

#include <Component/Component.h>

namespace TropicalEngine
{

	class ReflectionProbeComponent : public Component
	{
	public:
		TYPENAME(ReflectionProbeComponent)

		ReflectionProbeComponent(Entity* owner, class Texture* texture, float radius = 1.0f, float strength = 1.0f, float attenuation = 1.0f);
		~ReflectionProbeComponent();

		static ReflectionProbeComponent InitializeType();

		float getRadius()	{ return radius; }
		void setRadius(float radius)	{ this->radius = radius; }

		float getStrength()	{ return strength; }
		void setStrength(float strength)	{ this->strength = strength; }

		float getAttenuation()	{ return attenuation; }
		void setAttenuation()	{ this->attenuation = attenuation; }

		class Texture* getTexture()	{ return texture; }
		void setTexture(class Texture* texture)	{ this->texture = texture; }

		float getInfluence(glm::vec3 position);

	protected:
		float radius;
		float strength;
		float attenuation;
		class Texture* texture;	// panoramic latlong texture

		ReflectionProbeComponent()	{}
		void InitializeComponentType() override;
	};

}