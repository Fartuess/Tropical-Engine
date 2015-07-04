#include "TempHelpers\TempPlayerComponent.h"

TempPlayerComponent::TempPlayerComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar):CameraComponent(owner, targetOffset, up, fov, aspectRatio, zNear, zFar)
{
	///TODO: implement it.
}

TempPlayerComponent::~TempPlayerComponent(void)
{
	///TODO: implement it.
}

void TempPlayerComponent::Update()
{
	///TODO: implement it.
}

QString TempPlayerComponent::GETTYPENAME("TempPlayerComponent");

IDeserializableFromJSON& TempPlayerComponent::fromJSON(QJsonObject JSON)
{
	///TODO: implement this.
	return *(new TempPlayerComponent(nullptr, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f));
}