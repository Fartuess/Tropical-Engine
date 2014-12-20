#include <gtc\matrix_transform.hpp>
#include "TransformComponent.h"
#include "Entity.h"

TransformComponent::TransformComponent(Entity* owner):Component(owner)
{
	localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	localRotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	localScale = glm::vec3(1.0f, 1.0f, 1.0f);
	EvaluateGlobals();

	InitializeComponentType();
}

TransformComponent::TransformComponent(Entity* owner, glm::vec3 localPosition, glm::quat localRotation, glm::vec3 localScale):Component(owner)
{
	this->localPosition = localPosition;
	this->localRotation = localRotation;
	this->localScale = localScale;
	EvaluateGlobals();

	InitializeComponentType();
}

TransformComponent::~TransformComponent(void)
{

}

void TransformComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		AddParameter("Local Position", "Vec3");
		AddParameter("Local Rotation", "Vec3");
		AddParameter("Local Scale", "Vec3");
	}
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
	return glm::mat3(owner->getParrent()->transform.getTransformMatrix()) * globalPosition;
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
	///TODO: should be done differently
	glm::vec3 difference = position - localPosition;
	LocalTranslate(difference);
}

void TransformComponent::setGlobalPosition(glm::vec3 position)
{
	glm::vec3 difference = position - globalPosition;
	GlobalTranslate(difference);
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
	///TODO: it should be done differently
	localPosition += translation;
	globalPosition += glm::vec3(
		translation.x * right.x + translation.y * up.x + translation.z * (-front.x),
		translation.x * right.y + translation.y * up.y + translation.z * (-front.y),
		translation.x * right.z + translation.y * up.z + translation.z * (-front.z));
	Evaluate();
}

void TransformComponent::GlobalTranslate(glm::vec3 translation)
{
	globalPosition += translation;
	///TODO: calculate local position.
	Evaluate();
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
	glm::quat helper;
	if(glm::axis(rotation) == glm::vec3(0.0f, 1.0f, 0.0f))
	{
		helper =  glm::normalize(rotation) * localRotation;
	}
	else
	{
		helper = glm::normalize(rotation) * localRotation;
	}
	setLocalRotation(helper);
}

void TransformComponent::GlobalRotate(glm::quat rotation)
{
	setGlobalRotation(rotation * localRotation);
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
	glm::vec3 difference = glm::vec3(scale / localScale);
	localScale = scale;
	globalScale = globalScale * difference;
	Evaluate();
}

void TransformComponent::setGlobalScale(glm::vec3 scale)
{
	glm::vec3 difference = glm::vec3(scale / globalScale);
	globalScale = scale;
	localScale = localScale * difference;
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

glm::mat3 TransformComponent::getNormalMatrix()
{
	return normalMatrix;
}

glm::vec3 TransformComponent::getFront()
{
	return front;
}

glm::vec3 TransformComponent::getUp()
{
	return up;
}

glm::vec3 TransformComponent::getRight()
{
	return right;
}

void TransformComponent::EvaluateGlobals()
{
	///TODO: implement it.
}

void TransformComponent::EvaluateInternal()
{
	if(owner->getParrent() == nullptr)
	{
		transformMatrix = glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), localScale), glm::angle(localRotation), glm::axis(localRotation)), localPosition);
		normalMatrix = glm::mat3(glm::translate(glm::rotate(glm::transpose(glm::scale(glm::mat4(1.0f), localScale)), glm::angle(localRotation), glm::axis(localRotation)), localPosition));

		front = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		up = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		right = glm::vec3(glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		transformMatrix = owner->getParrent()->transform.getTransformMatrix() * glm::translate(glm::rotate(glm::scale(glm::mat4(1.0f), localScale), glm::angle(localRotation), glm::axis(localRotation)), localPosition);
		normalMatrix = glm::mat3(glm::translate(glm::rotate(glm::transpose(glm::scale(glm::mat4(1.0f), localScale) * owner->getParrent()->transform.getTransformMatrix()), glm::angle(localRotation), glm::axis(localRotation)), localPosition));

		front = glm::normalize(glm::vec3(owner->getParrent()->transform.getTransformMatrix() * glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
		up = glm::normalize(glm::vec3(owner->getParrent()->transform.getTransformMatrix() * glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
		right = glm::normalize(glm::vec3(owner->getParrent()->transform.getTransformMatrix() * glm::rotate(glm::mat4(1.0f), glm::angle(localRotation), glm::axis(localRotation)) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	}
}

void TransformComponent::Evaluate()
{
	EvaluateInternal();
	foreach(Entity* childObject, getOwner()->subobjects)
	{
		childObject->transform.Evaluate();
	}
}

QString TransformComponent::COMPONENTGETNAME("Transform Component");

QString TransformComponent::toXML()
{
	QString XMLString = QString(getIndent() + "<TransformComponent>\n");
	increaseIndent();
	XMLString += QString(getIndent() + "<Position X = \"" + localPosition.x + "\" Y = \"" + localPosition.y + "\" Z = \"" + localPosition.z + "\"/>\n");
	XMLString += QString(getIndent() + "<Rotation W = \"" + localRotation.w + "X = \"" + localRotation.x + "\" Y = \"" + localRotation.y + "\" Z = \"" + localRotation.z + "\"/>\n");
	XMLString += QString(getIndent() + "<Scale X = \"" + localScale.x + "\" Y = \"" + localScale.y + "\" Z = \"" + localScale.z + "\"/>\n");
	decreaseIndent();
	XMLString += QString(getIndent() + "</TransformComponent>\n");

	return XMLString;
}