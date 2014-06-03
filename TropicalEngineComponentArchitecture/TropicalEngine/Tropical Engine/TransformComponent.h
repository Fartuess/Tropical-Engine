#pragma once
#include <gtc\quaternion.hpp>
#include "_Math.h"
#include "_Component.h"

///TODO: Figure out how to make quaternions work
class TransformComponent :
	public Component
{
private:
	glm::vec3 localPosition;
	glm::quat localRotation;
	//glm::vec3 localRotation;
	glm::vec3 localScale;

	glm::vec3 globalPosition;
	glm::quat globalRotation;
	//glm::vec3 globalRotation;
	glm::vec3 globalScale;

	glm::mat4x4 transformMatrix;
	glm::mat4x4 normalMatrix;

public:

	TransformComponent(Entity* owner);
	//TransformComponent(Entity* owner, glm::vec3 localPosition, glm::vec3 localRotation, glm::vec3 localScale);
	TransformComponent(Entity* owner, glm::vec3 localPosition, glm::quat localRotation, glm::vec3 localScale);
	~TransformComponent(void);

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
	glm::mat4x4 getNormalMatrix();

private:
	void EvaluateGlobals();
	void EvaluateInternal();
public:
	void Evaluate();
};

