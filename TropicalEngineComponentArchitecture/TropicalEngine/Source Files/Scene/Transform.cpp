#include <gtc/matrix_transform.hpp>

#include <Scene/Transform.h>

namespace TropicalEngine
{

	Transform::Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	{
		this->position = position;
		this->rotation = rotation  * glm::quat();
		this->scale = scale;
	}

	Transform::~Transform()	{}

	bool Transform::operator==(Transform& other)
	{
		return (position == other.position
			&& rotation == other.rotation
			&& scale == other.scale);
	}

	bool Transform::operator!=(Transform& other)
	{
		return !(operator==(other));
	}

	Transform Transform::operator*(Transform& other)
	{
		glm::vec3 newPosition = glm::vec3(other.getTransformMatrix() * glm::vec4(this->getPosition(), 1.0));
		glm::quat newRotation = other.rotation * this->rotation;
		glm::vec3 newScale = this->scale * other.scale;

		return Transform(newPosition, newRotation, newScale);
	}

	glm::vec3 Transform::getPosition()
	{
		return position;
	}

	void Transform::setPosition(glm::vec3 position)
	{
		this->position = position;
		isEvaluated = false;
	}

	void Transform::Translate(glm::vec3 translation)
	{
		setPosition(this->position + translation);
	}

	glm::quat Transform::getRotation()
	{
		return rotation;
	}

	void Transform::setRotation(glm::quat rotation)
	{
		this->rotation = rotation * glm::quat();
		isEvaluated = false;
	}

	void Transform::Rotate(glm::quat rotation)
	{
		glm::quat helper;

		helper = glm::rotate(this->rotation, glm::angle(rotation), glm::axis(rotation));

		setRotation(helper);
	}


	glm::vec3 Transform::getScale()
	{
		return scale;
	}

	void Transform::setScale(glm::vec3 scale)
	{
		this->scale = scale;
		isEvaluated = false;
	}

	void Transform::Scale(float scale)
	{
		Scale(glm::vec3(scale));
	}

	void Transform::Scale(glm::vec3 scale)
	{
		setScale(this->scale * scale);
	}

	glm::vec3 Transform::getFrontVector()
	{
		if (!isEvaluated)
		{
			Evaluate();
		}
		return frontVector;
	}

	glm::vec3 Transform::getUpVector()
	{
		if (!isEvaluated)
		{
			Evaluate();
		}
		return upVector;
	}

	glm::vec3 Transform::getRightVector()
	{
		if (!isEvaluated)
		{
			Evaluate();
		}
		return rightVector;
	}


	glm::mat4x4 Transform::getTransformMatrix()
	{
		if (!isEvaluated)
		{
			Evaluate();
		}
		return transformMatrix;
	}

	glm::mat3 Transform::getNormalMatrix()
	{
		if (!isEvaluated)
		{
			Evaluate();
		}
		return normalMatrix;
	}

	void Transform::Evaluate()
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
		glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
		glm::mat4 scalingMatrix = glm::scale(glm::mat4(), scale);

		transformMatrix = translationMatrix * rotationMatrix * scalingMatrix;

		normalMatrix = glm::mat3(rotationMatrix * glm::transpose(scalingMatrix));

		frontVector = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		upVector = glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		rightVector = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		isEvaluated = true;
	}

	QJsonObject Transform::toJSON()
	{
		QJsonObject JSON = QJsonObject();
		QJsonObject positionJSON = QJsonObject();
		positionJSON["x"] = position.x;
		positionJSON["y"] = position.y;
		positionJSON["z"] = position.z;
		JSON["position"] = positionJSON;
		QJsonObject rotationJSON = QJsonObject();
		QJsonObject rotationAxisJSON = QJsonObject();
		glm::vec3 rotationAxisVector = glm::axis(rotation);
		rotationAxisJSON["x"] = rotationAxisVector.x;
		rotationAxisJSON["y"] = rotationAxisVector.y;
		rotationAxisJSON["z"] = rotationAxisVector.z;
		rotationJSON["axis"] = rotationAxisJSON;
		rotationJSON["angle"] = glm::angle(rotation);
		JSON["rotation"] = rotationJSON;
		QJsonObject scaleJSON = QJsonObject();
		scaleJSON["x"] = scale.x;
		scaleJSON["y"] = scale.y;
		scaleJSON["z"] = scale.z;
		JSON["scale"] = scaleJSON;

		return JSON;
	}

	IDeserializableFromJSON* Transform::fromJSON(QJsonObject JSON)
	{
		QJsonObject positionJSON = JSON["position"].toObject();
		glm::vec3 position = glm::vec3(positionJSON["x"].toDouble(), positionJSON["y"].toDouble(), positionJSON["z"].toDouble());

		QJsonObject rotationJSON = JSON["rotation"].toObject();
		QJsonObject rotationAxisJSON = rotationJSON["axis"].toObject();
		glm::quat rotation = glm::angleAxis((float)rotationJSON["angle"].toDouble(), glm::vec3(rotationAxisJSON["x"].toDouble(), rotationAxisJSON["y"].toDouble(), rotationAxisJSON["z"].toDouble()));

		QJsonObject scaleJSON = JSON["scale"].toObject();
		glm::vec3 scale = glm::vec3(scaleJSON["x"].toDouble(), scaleJSON["y"].toDouble(), scaleJSON["z"].toDouble());

		return new Transform(position, rotation, scale);
	}
}