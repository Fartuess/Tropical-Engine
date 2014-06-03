#include "TempPlayerComponent.h"


TempPlayerComponent::TempPlayerComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar):CameraComponent(owner, targetOffset, up, fov, aspectRatio, zNear, zFar)
{
}


TempPlayerComponent::~TempPlayerComponent(void)
{
}

void TempPlayerComponent::Update()
{

}