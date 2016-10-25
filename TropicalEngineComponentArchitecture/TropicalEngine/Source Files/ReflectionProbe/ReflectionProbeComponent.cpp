#include <ReflectionProbe/ReflectionProbeComponent.h>
#include <ReflectionProbe/ReflectionProbeManager.h>

#include <Texture/Texture.h>

#include <Scene/Entity.h>
#include <Scene/TransformComponent.h>

#include <QtCore/qdebug.h>

namespace TropicalEngine
{

	ReflectionProbeComponent::ReflectionProbeComponent(Entity* owner, class Texture* texture, float radius, float strength, float attenuation) : Component(owner)
	{
		this->radius = radius;
		this->strength = strength;
		this->attenuation = attenuation;
		this->texture = texture;

		ReflectionProbeManager::instance().addRefectionProbe(this);
	}


	ReflectionProbeComponent::~ReflectionProbeComponent()
	{
	}

	ReflectionProbeComponent ReflectionProbeComponent::InitializeType()
	{
		ReflectionProbeComponent& reflectionProbeComponent = *(new ReflectionProbeComponent());
		AssetManager::instance().addAssetType("Reflection Probe Component", &reflectionProbeComponent);
		return reflectionProbeComponent;
	}

	void ReflectionProbeComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			AddParameter("Radius", "Float");
			AddParameter("Influence Intensity", "Float");
			AddParameter("Influence Attenuation", "Float");
			AddParameter("Texture", "String");
		}
	}

	float ReflectionProbeComponent::getInfluence(glm::vec3 position)
	{
		glm::vec3 probePosition = this->getOwner()->transform.getPosition(true);
		float lightDistance = glm::length(probePosition - position);
		if (lightDistance <= radius)
		{	
			float lightDistanceFactor = glm::max(1.0f - (lightDistance / radius), 0.0f);

			return glm::max(glm::pow(lightDistanceFactor, attenuation) * strength, 0.0f);
		}
		else
		{

			return 0.0f;
		}
	}
}