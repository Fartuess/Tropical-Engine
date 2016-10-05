#include <gtc/matrix_transform.hpp>

#include <Scene/TransformComponent.h>
#include <Scene/Entity.h>

#include <QtCore/qdebug.h>

namespace TropicalEngine
{

	TransformComponent TransformComponent::templateObject = TransformComponent::InitializeType();

	TransformComponent::TransformComponent() {}

	TransformComponent::TransformComponent(Entity* owner, glm::vec3 localPosition, glm::quat localRotation, glm::vec3 localScale)
		: TransformComponent(owner, Transform(localPosition, localRotation, localScale))
	{}

	TransformComponent::TransformComponent(Entity* owner, Transform localTransform)
		: Component(owner), localTransform(localTransform), globalTransform(localTransform)
	{
		InitializeComponentType();
	}

	TransformComponent::~TransformComponent(void)
	{

	}

	TransformComponent TransformComponent::InitializeType()
	{
		TransformComponent& transformComponent = *(new TransformComponent());
		AssetManager::instance().addAssetType("Transform Component", &transformComponent);
		return transformComponent;
	}

	void TransformComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			AddParameter("Local Position", "Vec3");
			AddParameter("Local Rotation", "Vec3");
			AddParameter("Local Scale", "Vec3");
		}
	}

	Transform& TransformComponent::getTransform(bool isGlobal)
	{
		if (isGlobal)
			return getGlobalTransform();
		else
			return getLocalTransform();
	}

	Transform& TransformComponent::getLocalTransform()
	{
		return localTransform;
	}

	Transform& TransformComponent::getGlobalTransform()
	{
		return globalTransform;
	}

	glm::vec3 TransformComponent::getPosition(bool isGlobal)
	{
		if (isGlobal)
			return getGlobalPosition();
		else
			return getLocalPosition();
	}

	glm::vec3 TransformComponent::getLocalPosition()
	{
		return localTransform.getPosition();
	}

	glm::vec3 TransformComponent::getGlobalPosition()
	{
		return globalTransform.getPosition();
	}

	void TransformComponent::setPosition(glm::vec3 position, bool isGlobal)
	{
		if (isGlobal)
			setGlobalPosition(position);
		else
			setLocalPosition(position);
	}

	void TransformComponent::setLocalPosition(glm::vec3 position)
	{
		glm::vec3 difference = position - getLocalPosition();
		LocalTranslate(difference);
	}

	void TransformComponent::setGlobalPosition(glm::vec3 position)
	{
		glm::vec3 difference = position - getGlobalPosition();
		GlobalTranslate(difference);
	}

	void TransformComponent::Translate(glm::vec3 translation, bool isGlobal)
	{
		if (isGlobal)
			GlobalTranslate(translation);
		else
			LocalTranslate(translation);
	}

	void TransformComponent::LocalTranslate(glm::vec3 translation)
	{
		localTransform.Translate(translation);
		
		glm::vec3 front = globalTransform.getFrontVector();
		glm::vec3 up = globalTransform.getUpVector();
		glm::vec3 right = globalTransform.getRightVector();

		globalTransform.Translate(
			glm::vec3(
			translation.x * right.x + translation.y * up.x + translation.z * (-front.x),
			translation.x * right.y + translation.y * up.y + translation.z * (-front.y),
			translation.x * right.z + translation.y * up.z + translation.z * (-front.z))
			);

		Evaluate();
	}

	void TransformComponent::GlobalTranslate(glm::vec3 translation)
	{
		globalTransform.Translate(translation);

		glm::vec3 front = globalTransform.getFrontVector();
		glm::vec3 up = globalTransform.getUpVector();
		glm::vec3 right = globalTransform.getRightVector();

		localTransform.Translate(
			glm::vec3(
			translation.x / right.x + translation.y / up.x + translation.z / (-front.x),
			translation.x / right.y + translation.y / up.y + translation.z / (-front.y),
			translation.x / right.z + translation.y / up.z + translation.z / (-front.z))
			);

		Evaluate();
	}

	glm::quat TransformComponent::getRotation(bool isGlobal)
	{
		if (isGlobal)
			return getGlobalRotation();
		else
			return getLocalRotation();
	}

	glm::quat TransformComponent::getLocalRotation()
	{
		return localTransform.getRotation();
	}

	glm::quat TransformComponent::getGlobalRotation()
	{
		return globalTransform.getRotation();
	}

	void TransformComponent::setRotation(glm::quat rotation, bool isGlobal)
	{
		if (isGlobal)
			setGlobalRotation(rotation);
		else
			setLocalRotation(rotation);
	}

	void TransformComponent::setLocalRotation(glm::quat rotation)
	{
		localTransform.setRotation(rotation);
		// TODO: globalRotation;

		Evaluate();
	}

	void TransformComponent::setGlobalRotation(glm::quat rotation)
	{
		globalTransform.setRotation(rotation);
		// TODO: globalRotation

		Evaluate();
	}

	void TransformComponent::Rotate(glm::quat rotation, bool isGlobal)
	{
		if (isGlobal)
			GlobalRotate(rotation);
		else
			LocalRotate(rotation);
	}

	void TransformComponent::LocalRotate(glm::quat rotation)
	{
		glm::quat helper;

		helper = glm::rotate(getLocalRotation(), glm::angle(rotation), glm::axis(rotation));

		setLocalRotation(helper);
	}

	void TransformComponent::GlobalRotate(glm::quat rotation)
	{
		glm::quat helper;

		helper = glm::rotate(getGlobalRotation(), glm::angle(rotation), glm::axis(rotation));

		setGlobalRotation(helper);
	}

	glm::vec3 TransformComponent::getScale(bool isGlobal)
	{
		if (isGlobal)
			return getGlobalScale();
		else
			return getLocalScale();
	}

	glm::vec3 TransformComponent::getLocalScale()
	{
		return localTransform.getScale();
	}

	glm::vec3 TransformComponent::getGlobalScale()
	{
		return globalTransform.getScale();
	}

	void TransformComponent::setScale(glm::vec3 scale, bool isGlobal)
	{
		if (isGlobal)
			setGlobalScale(scale);
		else
			setLocalScale(scale);
	}

	void TransformComponent::setLocalScale(glm::vec3 scale)
	{
		glm::vec3 difference = glm::vec3(scale / localTransform.getScale());
		Scale(difference);
	}

	void TransformComponent::setGlobalScale(glm::vec3 scale)
	{
		glm::vec3 difference = glm::vec3(scale / getGlobalScale());
		Scale(difference);
	}

	void TransformComponent::Scale(float scale)
	{
		localTransform.Scale(scale);
		globalTransform.Scale(scale);

		Evaluate();
	}

	void TransformComponent::Scale(glm::vec3 scale)
	{
		localTransform.Scale(scale);
		globalTransform.Scale(scale);

		Evaluate();
	}

	glm::mat4x4 TransformComponent::getTransformMatrix()
	{
		return globalTransform.getTransformMatrix();
	}

	glm::mat3 TransformComponent::getNormalMatrix()
	{
		return globalTransform.getNormalMatrix();
	}

	glm::vec3 TransformComponent::getFront()
	{
		//return localTransform.getFrontVector();
		return globalTransform.getFrontVector();
	}

	glm::vec3 TransformComponent::getUp()
	{
		//return localTransform.getUpVector();
		return globalTransform.getUpVector();
	}

	glm::vec3 TransformComponent::getRight()
	{
		//return localTransform.getRightVector();
		return globalTransform.getRightVector();
	}

	void TransformComponent::EvaluateInternal()
	{

		if (owner->getParrent() == nullptr)
		{
			globalTransform = localTransform;
		}
		else
		{
			globalTransform = localTransform * Transform(owner->getParrent()->transform.getGlobalTransform());
		}
	}

	void TransformComponent::Evaluate()
	{
		EvaluateInternal();
		for (Entity* childObject : getOwner()->getSubobjects())
		{
			childObject->transform.Evaluate();
		}
	}

	QJsonObject TransformComponent::toJSON()
	{
		QJsonObject JSON = Component::toJSON();
		JSON["Transform"] = localTransform.toJSON();

		return JSON;
	}

IDeserializableFromJSON* TransformComponent::fromJSON(QJsonObject JSON)
{
	// TODO: implement this.
	return new TransformComponent();
}

}