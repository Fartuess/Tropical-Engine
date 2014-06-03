#include <gtc\matrix_transform.hpp>
#include "TransformComponent.h"
#include "Entity.h"

TransformComponent::TransformComponent(Entity* owner):Component(owner)
{
	localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	localRotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	localScale = glm::vec3(0.0f, 0.0f, 0.0f);
	EvaluateGlobals();
}

TransformComponent::TransformComponent(Entity* owner, glm::vec3 localPosition, glm::quat localRotation, glm::vec3 localScale):Component(owner)
{
	this->localPosition = localPosition;
	this->localRotation = localRotation;
	this->localScale = localScale;
	EvaluateGlobals();
}

TransformComponent::~TransformComponent(void)
{
}

glm::vec3 TransformComponent::getPosition(bool isGlobal)
{
	if(isGlobal)
		return globalPosition;
	else
		return localPosition;
}

glm::vec3 TransformComponent::getLocalPosition()
{
	return localPosition;
}

glm::vec3 TransformComponent::getGlobalPosition()
{
	return globalPosition;
}

void TransformComponent::setPosition(glm::vec3 position, bool isGlobal)
{
	if(isGlobal)
		setGlobalPosition(position);
	else
		setLocalPosition(position);
}

void TransformComponent::setLocalPosition(glm::vec3 position)
{
	localPosition = position;
	///TODO: setting global position;
	Evaluate();
}

void TransformComponent::setGlobalPosition(glm::vec3 position)
{
	///TODO: setting local position;
	globalPosition =position;
	Evaluate();
}

void TransformComponent::Translate(glm::vec3 translation, bool isGlobal)
{
	if(isGlobal)
		GlobalTranslate(translation);
	else
		LocalTranslate(translation);
}

void TransformComponent::LocalTranslate(glm::vec3 translation)
{
	setLocalPosition(localPosition + translation);
}

void TransformComponent::GlobalTranslate(glm::vec3 translation)
{
	setGlobalPosition(localPosition + translation);
}

glm::quat TransformComponent::getRotation(bool isGlobal)
{
	if(isGlobal)
		return getGlobalRotation();
	else
		return getLocalRotation();
}

glm::quat TransformComponent::getLocalRotation()
{
	return localRotation;
}

glm::quat TransformComponent::getGlobalRotation()
{
	return globalRotation;
}

void TransformComponent::setRotation(glm::quat rotation, bool isGlobal)
{
	if(isGlobal)
		setGlobalRotation(rotation);
	else
		setLocalRotation(rotation);
}

void TransformComponent::setLocalRotation(glm::quat rotation)
{
	localRotation = rotation;
	///TODO: globalRotation;
	Evaluate();
}

void TransformComponent::setGlobalRotation(glm::quat rotation)
{
	localRotation = rotation;
	///TODO: globalRotation;
	Evaluate();
}

void TransformComponent::Rotate(glm::quat rotation, bool isGlobal)
{
	if(isGlobal)
		GlobalRotate(rotation);
	else
		LocalRotate(rotation);
}

void TransformComponent::LocalRotate(glm::quat rotation)
{
	setLocalRotation(localRotation + rotation);
}

void TransformComponent::GlobalRotate(glm::quat rotation)
{
	setGlobalRotation(globalRotation + rotation);
}

glm::vec3 TransformComponent::getScale(bool isGlobal)
{
	if(isGlobal)
		return globalScale;
	else
		return localScale;
}

glm::vec3 TransformComponent::getLocalScale()
{
	return localScale;
}

glm::vec3 TransformComponent::getGlobalScale()
{
	return globalScale;
}

void TransformComponent::setScale(glm::vec3 scale, bool isGlobal)
{
	if(isGlobal)
		setGlobalScale(scale);
	else
		setLocalScale(scale);
}

void TransformComponent::setLocalScale(glm::vec3 scale)
{
	localScale = scale;
	///TODO: globalScale;
	Evaluate();
}

void TransformComponent::setGlobalScale(glm::vec3 scale)
{
	globalScale = scale;
	///TODO: localScale;
	Evaluate();
}

void TransformComponent::Scale(float scale)
{
	localScale = localScale * scale;
	globalScale = globalScale * scale;
	Evaluate();
}

void TransformComponent::Scale(glm::vec3 scale)
{
	localScale = localScale * scale;
	globalScale = globalScale * scale;
	Evaluate();
}

glm::mat4x4 TransformComponent::getTransformMatrix()
{
	return transformMatrix;
}

glm::mat4x4 TransformComponent::getNormalMatrix()
{
	return normalMatrix;
}

void TransformComponent::EvaluateGlobals()
{
	///TODO: implement it.
}

void TransformComponent::EvaluateInternal()
{
	if(owner == nullptr)
	{
		transformMatrix = glm::translate(glm::rotate(glm::scale(glm::mat4(), localScale), localRotation.w, glm::vec3(localRotation.x, localRotation.y, localRotation.z)), localPosition);
		normalMatrix = glm::translate(glm::rotate(glm::transpose(glm::scale(glm::mat4(), localScale)), localRotation.w, glm::vec3(localRotation.x, localRotation.y, localRotation.z)), localPosition);
	}
	transformMatrix = glm::translate(glm::rotate(glm::scale(owner->transform.getTransformMatrix(), localScale), localRotation.w, glm::vec3(localRotation.x, localRotation.y, localRotation.z)), localPosition);
	normalMatrix = glm::translate(glm::rotate(glm::transpose(glm::scale(glm::mat4(), localScale) * owner->transform.getTransformMatrix()), localRotation.w, glm::vec3(localRotation.x, localRotation.y, localRotation.z)), localPosition);
}

void TransformComponent::Evaluate()
{
	EvaluateInternal();
	foreach(Entity* childObject, getOwner()->subobjects)
	{
		childObject->transform.Evaluate();
	}
}