#include <QtCore/qdebug.h>

#include <TempHelpers/TempPlayerComponent.h>

#include <Input/InputManager.h>

#include <Scene/TransformComponent.h>
#include <Scene/Entity.h>
#include <Scene/SceneManager.h>

#include "TropicalEngineApplication.h"

TempPlayerComponent::TempPlayerComponent(Entity* owner) :
	Component(owner)
{
	///TODO: implement it.
	//normally controller would not define bindings.
	InputManager* inputManager = TropicalEngineApplication::instance()->inputManager;

	inputManager->AddAction("Move Forward",		Qt::Key_W);
	inputManager->AddAction("Move Backward",	Qt::Key_S);
	inputManager->AddAction("Move Left",		Qt::Key_A);
	inputManager->AddAction("Move Right",		Qt::Key_D);
	inputManager->AddAction("Move Up",			Qt::Key_Space);
	inputManager->AddAction("Move Down",		Qt::Key_C);

	inputManager->AddAction("Move Fast");
	inputManager->BindAction("Move Fast", Qt::Key_Shift);
}

TempPlayerComponent::~TempPlayerComponent(void)
{
	///TODO: implement it.
}

void TempPlayerComponent::OnUpdate(int DeltaTime)
{
	InputManager* inputManager = TropicalEngineApplication::instance()->inputManager;

	TransformComponent& ownerTransform = this->getOwner()->transform;
	
	glm::vec3 front = ownerTransform.getFront();
	glm::vec3 right = ownerTransform.getRight();
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	///TODO: replace this temp value
	float speed = 0.003f * (1 + qMin(((float)inputManager->getTime("Move Fast", DeltaTime) / (float)DeltaTime), 1.0f));

	///TODO: Figure out if we are ok with faster diagonal movement
	ownerTransform.LocalTranslate(front * (speed * (float)inputManager->getTime("Move Forward", DeltaTime)));
	ownerTransform.LocalTranslate(-front * (speed * (float)inputManager->getTime("Move Backward", DeltaTime)));
	ownerTransform.LocalTranslate(right * (speed * (float)inputManager->getTime("Move Right", DeltaTime)));
	ownerTransform.LocalTranslate(-right * (speed * (float)inputManager->getTime("Move Left", DeltaTime)));
	ownerTransform.LocalTranslate(up * (speed * (float)inputManager->getTime("Move Up", DeltaTime)));
	ownerTransform.LocalTranslate(-up * (speed * (float)inputManager->getTime("Move Down", DeltaTime)));
}

IDeserializableFromJSON* TempPlayerComponent::fromJSON(QJsonObject JSON)
{
	///TODO: implement this.
	return new TempPlayerComponent(nullptr);
}

TempPlayerComponent::TempPlayerComponent()
{

}

void TempPlayerComponent::InitializeComponentType()
{
	if (!isComponentTypeUsed(getTypeName()))
	{
		///TODO: ??
	}
}

TempPlayerComponent TempPlayerComponent::InitializeType()
{
	TempPlayerComponent& tempPlayerComponent = *(new TempPlayerComponent());
	AssetManager::addAssetType("Temp Player Component", &tempPlayerComponent);
	return tempPlayerComponent;
}