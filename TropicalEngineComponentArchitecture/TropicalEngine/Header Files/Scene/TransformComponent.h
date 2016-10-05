#pragma once
#include <glm.hpp>
#include <gtc/quaternion.hpp>

#include <Component/Component.h>

#include "Transform.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Component for representing position, rotation and scale of object.
	  */
	#pragma endregion
	class TransformComponent : public Component
	{
	public:
		TYPENAME(TransformComponent)

		#pragma region documentation
		/**
		  * \brief TransformComponent constructor.
		  *
		  * @param owner Entity to attach this Component to.
		  * @param localPosition Local position for object owning this Component.
		  * @param localRotation Local Rotation for object owning this Component.
		  * @param localScale Local Scale for object owning this Component.
		  */
		#pragma endregion
		TransformComponent(Entity* owner, glm::vec3 localPosition = glm::vec3(0.0f), glm::quat localRotation = glm::quat(), glm::vec3 localScale = glm::vec3(1.0f));
		#pragma region documentation
		/**
		  * \brief TransformComponent constructor.
		  *
		  * @param owner Entity to attach this Component to.
		  * @param localTransform Transform data for this Component.
		  */
		#pragma endregion
		TransformComponent(Entity* owner, Transform localTransform);
		#pragma region documentation
		/**
		  * \brief TransformComponent destructor.
		  */
		#pragma endregion
		~TransformComponent(void);

		static TransformComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Gets Transform data of this component.
		  *
		  * @param isGlobal Decides if local Transform or global transfor shouldbe returned.
		  * @return Transform data of this component.
		  */
		#pragma endregion
		Transform& getTransform(bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Gets local Transform data of this component.
		  *
		  * @return Local Transform data of this component.
		  */
		#pragma endregion
		Transform& getLocalTransform();
		#pragma region documentation
		/**
		  * \brief Gets global Transform data of this component.
		  *
		  * @return Global Transform data of this component.
		  */
		#pragma endregion
		Transform& getGlobalTransform();
		#pragma region documentation
		/**
		  * \brief Gets global or local position.
		  *
		  * @param isGlobal Decides if returned value will be global or local position.
		  * @return Global or local position.
		  */
		#pragma endregion
		glm::vec3 getPosition(bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Gets local position.
		  *
		  * @return Local position.
		  */
		#pragma endregion
		glm::vec3 getLocalPosition();
		#pragma region documentation
		/**
		  * \brief Gets global position.
		  *
		  * @return Global position.
		  */
		#pragma endregion
		glm::vec3 getGlobalPosition();
		#pragma region documentation
		/**
		  * \brief Sets global or local position.
		  *
		  * Sets global or local position and changing other one respectively.
		  * @param position New position to set.
		  * @param isGlobal Decides if value will be set for global or local position.
		  */
		#pragma endregion
		void setPosition(glm::vec3 position, bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Sets local position.
		  *
		  * Sets local position. Global position changes respectively.
		  * @param position Local position to set.
		  */
		#pragma endregion
		void setLocalPosition(glm::vec3 position);
		#pragma region documentation
		/**
		  * \brief Sets global position.
		  *
		  * Sets global position. Local position changes respectively.
		  * @param position Global position to set.
		  */
		#pragma endregion
		void setGlobalPosition(glm::vec3 position);
		#pragma region documentation
		/**
		  * \brief Translates object owning this Component.
		  *
		  * Offsets position of object owning this Component.
		  * @param translation Offset to move.
		  * @param isGlobal Defines if object should be moved along global axis or local axis.
		  */
		#pragma endregion
		void Translate(glm::vec3 translation, bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Translate object along local axis.
		  *
		  * @param translation Offset to move.
		  */
		#pragma endregion
		void LocalTranslate(glm::vec3 translation);
		#pragma region documentation
		/**
		  * \brief Translate object along global axis.
		  *
		  * @param translation Offset to move.
		  */
		#pragma endregion
		void GlobalTranslate(glm::vec3 translation);

		#pragma region documentation
		/**
		  * \brief Gets global or local rotation of object owning this Component.
		  *
		  * @param isGlobal Defines if method will return global or local rotation.
		  * @return Quaternion defining object rotation.
		  */
		#pragma endregion
		glm::quat getRotation(bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Gets local rotation of object owning this Component.
		  *
		  * @return Quaternion defining object local rotation.
		  */
		#pragma endregion
		glm::quat getLocalRotation();
		#pragma region documentation
		/**
		  * \brief Gets global rotation of object owning this Component.
		  *
		  * @return Quaternion defining object global rotation.
		  */
		#pragma endregion
		glm::quat getGlobalRotation();
		#pragma region documentation
		/**
		  * \brief Sets global or local rotation for object owning this Component.
		  *
		  * Sets global or local rotation and updates the other one respectively.
		  * @param rotation Quaternion describing new rotation.
		  * @param isGlobal Defines if method will set global or local rotation.
		  */
		#pragma endregion
		void setRotation(glm::quat rotation, bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Sets local rotation for object owning this Component.
		  *
		  * Sets local rotation and updates global one respectively.
		  * @param rotation Quaternion describing new rotation.
		  */
		#pragma endregion
		void setLocalRotation(glm::quat rotation);
		#pragma region documentation
		/**
		  * \brief Sets global rotation for object owning this Component.
		  *
		  * Sets global rotation and updates local one respectively.
		  * @param rotation Quaternion describing new rotation.
		  */
		#pragma endregion
		void setGlobalRotation(glm::quat rotation);
		#pragma region documentation
		/**
		  * \brief Rotates object owning this Component.
		  *
		  * @param rotation Quaternion defining rotation operation.
		  * @param isGlobal defines if rotation is using global axes or local axes.
		  */
		#pragma endregion
		void Rotate(glm::quat rotation, bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Rotates object owning this Component using local axes.
		  *
		  * @param rotation Quaternion defining rotation operation.
		  */
		#pragma endregion
		void LocalRotate(glm::quat rotation);
		#pragma region documentation
		/**
		  * \brief Rotates object owning this Component using global axes.
		  *
		  * @param rotation Quaternion defining rotation operation.
		  */
		#pragma endregion
		void GlobalRotate(glm::quat rotation);

		#pragma region documentation
		/**
		  * \brief Get scale of object owning this Component.
		  *
		  * @param isGlobal Defines if method will get global or local scale.
		  * @return Global or local scale.
		  */
		#pragma endregion
		glm::vec3 getScale(bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Get local scale of object owning this Component.
		  *
		  * @return Local scale.
		  */
		#pragma endregion
		glm::vec3 getLocalScale();
		#pragma region documentation
		/**
		  * \brief Get global scale of object owning this Component.
		  *
		  * @return Global scale.
		  */
		#pragma endregion
		glm::vec3 getGlobalScale();
		#pragma region documentation
		/**
		  * \brief Set scale of object owning this Component.
		  *
		  * Sets global or local scale, other one adapts respectively.
		  * @param scale New Scale value.
		  * @param isGlobal Defines if method will set global or local scale.
		  */
		#pragma endregion
		void setScale(glm::vec3 scale, bool isGlobal = false);
		#pragma region documentation
		/**
		  * \brief Set local scale of object owning this Component.
		  *
		  * Sets local scale, global one adapts respectively.
		  * @param scale New Scale value.
		  */
		#pragma endregion
		void setLocalScale(glm::vec3 scale);
		#pragma region documentation
		/**
		  * \brief Set global scale of object owning this Component.
		  *
		  * Sets global scale, local one adapts respectively.
		  * @param scale New Scale value.
		  */
		#pragma endregion
		void setGlobalScale(glm::vec3 scale);
		#pragma region documentation
		/**
		  * \brief Multiplies scale uniformly.
		  *
		  * @param scale Value describing scale multiplication.
		  */
		#pragma endregion
		void Scale(float scale);
		#pragma region documentation
		/**
		  * \brief Multiplies scale along three axes separately.
		  *
		  * @param scale Value describing scale multiplication.
		  */
		#pragma endregion
		void Scale(glm::vec3 scale);

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

		#pragma region documentation
		/**
		  * \brief Gets vector pointing from the front of object owning this Component.
		  *
		  * @return Vector pointing from the front of object owning this Component.
		  */
		#pragma endregion
		glm::vec3 getFront();
		#pragma region documentation
		/**
		  * \brief Gets vector pointing from the top of object owning this Component.
		  *
		  * @return Vector pointing from the top of object owning this Component.
		  */
		#pragma endregion
		glm::vec3 getUp();
		#pragma region documentation
		/**
		  * \brief Gets vector pointing from the right side of object owning this Component.
		  *
		  * @return Vector pointing from the right side of object owning this Component.
		  */
		#pragma endregion
		glm::vec3 getRight();

		void Evaluate();

		#pragma region documentation
		/**
		  * \brief Serializes TransformComponent to JSON.
		  *
		  * @return Serialized TransformComponent.
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
		#pragma region documentation
		/**
		  * \brief Helper constructor for TransformComponent deserialization.
		  */
		#pragma endregion
		TransformComponent();
		void InitializeComponentType() override;

	private:
		Transform localTransform;
		Transform globalTransform;

		static TransformComponent templateObject;

		void EvaluateInternal();
	};

}