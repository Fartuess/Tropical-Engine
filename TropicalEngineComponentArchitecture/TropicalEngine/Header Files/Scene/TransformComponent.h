#pragma once
#include <glm.hpp>
#include <gtc/quaternion.hpp>

#include <Component/Component.h>

class TransformComponent : public Component
{
public:
	TransformComponent(Entity* owner, glm::vec3 localPosition = glm::vec3(0.0f), glm::quat localRotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3 localScale = glm::vec3(1.0f));
	~TransformComponent(void);

	static TransformComponent InitializeType();

	glm::vec3 getPosition(bool isGlobal = false);
	glm::vec3 getLocalPosition();
	glm::vec3 getGlobalPosition();
	void setPosition(glm::vec3 position, bool isGlobal = false);
	void setLocalPosition(glm::vec3 position);
	void setGlobalPosition(glm::vec3 position);
	void Translate(glm::vec3 translation, bool isGlobal = false);
	void LocalTranslate(glm::vec3 translation);
	void GlobalTranslate(glm::vec3 translation);

	glm::quat getRotation(bool isGlobal = false);
	glm::quat getLocalRotation();
	glm::quat getGlobalRotation();
	void setRotation(glm::quat rotation, bool isGlobal = false);
	void setLocalRotation(glm::quat rotation);
	void setGlobalRotation(glm::quat rotation);
	void Rotate(glm::quat rotation, bool isGlobal = false);
	void LocalRotate(glm::quat rotation);
	void GlobalRotate(glm::quat rotation);

	glm::vec3 getScale(bool isGlobal = false);
	glm::vec3 getLocalScale();
	glm::vec3 getGlobalScale();
	void setScale(glm::vec3 scale, bool isGlobal = false);
	void setLocalScale(glm::vec3 scale);
	void setGlobalScale(glm::vec3 scale);
	void Scale(float scale);
	void Scale(glm::vec3 scale);

	glm::mat4x4 getTransformMatrix();
	glm::mat3 getNormalMatrix();

	glm::vec3 getFront();
	glm::vec3 getUp();
	glm::vec3 getRight();

	void Evaluate();

	QString getTypeName() override;

	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	TransformComponent();
	void InitializeComponentType() override;

private:
	glm::vec3 localPosition;
	glm::quat localRotation;
	glm::vec3 localScale;

	glm::vec3 globalPosition;
	glm::quat globalRotation;
	glm::vec3 globalScale;

	glm::mat4x4 transformMatrix;
	glm::mat3 normalMatrix;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	static TransformComponent templateObject;

	void EvaluateGlobals();
	void EvaluateInternal();
};

