#pragma once

#include <glm.hpp>
#include <gtc/quaternion.hpp>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class holding information about position, rotation and scale.
	  */
	#pragma endregion
	class Transform : public ISerializableJSON
	{
	public:
		TYPENAME(Transform)

		#pragma region documentation
		/**
		  * \Brief Constructor for Transform class.
		  *
		  * @param position Position component of Transform.
		  * @param rotation Rotation component of Transform.
		  * @param scale Scale component of Transform.
		  */
		#pragma endregion
		Transform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(), glm::vec3 scale = glm::vec3(1.0f));
		#pragma region documentation
		/**
		  * \brief Transform default destructor.
		  */
		#pragma endregion
		~Transform();

		#pragma region documentation
		/**
		  * \brief Compares if two Transforms have the same position, rotation and scale values.
		  *
		  * @param other Other Transform to compare to.
		  * @return Information if both Transforms are equal.
		  */
		#pragma endregion
		bool operator==(Transform& other);
		#pragma region documentation
		/**
		  * \brief Compares if two Transforms have different position, rotation or scale values.
		  *
		  * @param other Other Transform to compare to.
		  * @return Information if both Transforms are not equal.
		  */
		#pragma endregion
		bool operator!=(Transform& other);
		#pragma region documentation
		/**
		  * \brief combines two Transforms. Combines from let to right?
		  *
		  * @param other Other Transform to combine with.
		  */
		#pragma endregion
		Transform operator*(Transform& other);
		#pragma region documentation
		/**
		  * \brief Gets position component of Transform.
		  *
		  * @return Position component of Transform.
		  */
		#pragma endregion
		glm::vec3 getPosition();
		#pragma region documentation
		/**
		  * \brief Sets new value of position component of Transform.
		  *
		  * @param position New value of position component of Transform.
		  */
		#pragma endregion
		void setPosition(glm::vec3 position);
		#pragma region documentation
		/**
		  * \brief Offsets the value of position component of Transform.
		  *
		  * @param translation Ammount of offset for position component of Transform.
		  */
		#pragma endregion
		void Translate(glm::vec3 translation);

		// TODO: interfacing with Euler angles?
		#pragma region documentation
		/**
		  * \brief Gets value of rotation component of Transform.
		  *
		  * @return Value of rotation component of Transform.
		  */
		#pragma endregion
		glm::quat getRotation();
		#pragma region documentation
		/**
		  * \brief Sets new value of rotation component of Transform.
		  *
		  * @param rotation New value for rotation component of Transform.
		  */
		#pragma endregion
		void setRotation(glm::quat rotation);
		#pragma region documentation
		/**
		  * \brief Rotates Transform.
		  *
		  * @param rotation Amount of rotation.
		  */
		#pragma endregion
		void Rotate(glm::quat rotation);

		#pragma region documentation
		/**
		  * \brief Gets value of scale component of Transform.
		  *
		  * @return Value of scale component of Transform.
		  */
		#pragma endregion
		glm::vec3 getScale();
		#pragma region documentation
		/**
		  * \brief Sets new value of scale component of Transform.
		  *
		  * @param scale New value of scale component of Transform.
		  */
		#pragma endregion
		void setScale(glm::vec3 scale);
		#pragma region documentation
		/**
		  * \brief Uniformly scales Transform.
		  *
		  * @param scale Amount of scale.
		  */
		#pragma endregion
		void Scale(float scale);
		#pragma region documentation
		/**
		  * \brief Nonuniformly scales Transform.
		  *
		  * @param scale Amount of scale.
		  */
		#pragma endregion
		void Scale(glm::vec3 scale);

		#pragma region documentation
		/**
		  * \brief Gets front direction.
		  *
		  * @return Vector describing front direction.
		  */
		#pragma endregion
		glm::vec3 getFrontVector();
		#pragma region documentation
		/**
		  * \brief Gets up direction.
		  *
		  * @return Vector describing up direction.
		  */
		#pragma endregion
		glm::vec3 getUpVector();
		#pragma region documentation
		/**
		  * \brief Gets right direction.
		  *
		  * @return Vector describing right direction.
		  */
		#pragma endregion
		glm::vec3 getRightVector();

		#pragma region documentation
		/**
		  * \brief Gets transformation matrix.
		  *
		  * @return Transformation matrix.
		  */
		#pragma endregion
		glm::mat4x4 getTransformMatrix();
		#pragma region documentation
		/**
		  * \brief Gets normal matrix.
		  *
		  * @return Normal matrix.
		  */
		#pragma endregion
		glm::mat3 getNormalMatrix();

		void Evaluate();

		#pragma region documentation
		/**
		  * \brief Serializes Transform to JSON.
		  *
		  * @return Serialized Transform.
		  */
		#pragma endregion
		QJsonObject toJSON() override;

		#pragma region documentation
		/**
		  * \brief Deserializes JSON to TransformComponent.
		  *
		  * @return TransformComponent in form of IDeserializableFromJSON. Can be casted to TransformComponent directly.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		// TODO: Consider pointers to reduce memory. Possible use cases with thousands of Transforms.
		glm::vec3 frontVector;
		glm::vec3 upVector;
		glm::vec3 rightVector;

		// TODO: Consider pointers to reduce memory. Possible use cases with thousands of Transforms.
		glm::mat4x4 transformMatrix;
		glm::mat3 normalMatrix;

		bool isEvaluated = false;
	};

}