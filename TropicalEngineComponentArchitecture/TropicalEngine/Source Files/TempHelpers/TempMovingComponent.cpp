#include <TempHelpers/TempMovingComponent.h>

#include <Scene/Entity.h>

namespace TropicalEngine
{

	TempMovingComponent::TempMovingComponent(Entity* owner, glm::vec3 startPos, glm::vec3 endPos, float timespan) : Component(owner)
	{
		this->variance = (endPos - startPos) / 2.0f;
		this->half = startPos + variance;
		this->timespan = timespan;
		this->currentTime = 0.0f;

	}

	TempMovingComponent::~TempMovingComponent()
	{
	}

	void TempMovingComponent::OnUpdate(int deltaTime)
	{
		currentTime += (float)deltaTime / 1000.0f;
		glm::vec3 newPosition = half + (variance * glm::cos((currentTime * 2 * glm::pi<float>()) / timespan));
		owner->transform.setLocalPosition(newPosition);
	}

	void TempMovingComponent::InitializeComponentType()
	{

	}

}