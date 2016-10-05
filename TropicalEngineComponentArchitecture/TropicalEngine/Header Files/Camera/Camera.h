#pragma once

#include <glm.hpp>

#include <Serialization/ISerializableJSON.h>

#include <Scene/Transform.h>

namespace TropicalEngine
{
	#pragma region documentation
	/**
	  * \brief Class storing camera information.
	  */
	#pragma endregion
	class Camera : public ISerializableJSON
	{
	public:
		TYPENAME(Camera)

		friend class CameraComponent;

		#pragma region documentation
		/**
		  * \brief Camera component costructor.
		  *
		  * @param transform Reference to Transform information this camera is using.
		  * @param targetOffset defines direction where Camera is looking at.
		  * @param up vector defining Camera roll.
		  * @param fov field of view of the Camera.
		  * @param aspectRatio width to height ratio of the Camera.
		  * @param zNear Near clipping plane distance.
		  * @param zFar Far clipping plane distance.
		  */
		#pragma endregion
		Camera(Transform& transform, glm::vec3 targetOffset = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float fov = 40.0f, float aspectRatio = 4.0f / 3.0f, float zNear = 0.01f, float zFar = 10000.0f);
		#pragma region documentation
		/**
		  * \brief Default destructor
		  */
		#pragma endregion
		~Camera();

		void setTransformReference(Transform& transform);

		#pragma region documentation
		/**
		  * \brief Gets target offset of the Camera.
		  *
		  * @return Vector describing target offset of Camera.
		  */
		#pragma endregion
		glm::vec3 getTarget();
		#pragma region documentation
		/**
		  * \brief Sets direction where Camera is looking.
		  *
		  * @param targetOffset Position offset describing direction where Camera is looking at.
		  */
		#pragma endregion
		void setTarget(glm::vec3 targetOffset);

		#pragma region documentation
		/**
		  * \brief Gets Up Vector of Camera.
		  *
		  * @return Up Vector of the Camera.
		  */
		#pragma endregion
		glm::vec3 getUp();
		#pragma region documentation
		/**
		  * \brief Sets Up Vector of Camera.
		  *
		  * Sets roll of the Camera by defining Up vector.
		  * @param Up Vector defining up direction of the Camera.
		  */
		#pragma endregion
		void setUp(glm::vec3 up);

		#pragma region documentation
		/**
		  * \brief Gets Field of View of Camera.
		  *
		  * @return Field of View value.
		  */
		#pragma endregion
		float getFov();
		#pragma region documentation
		/**
		  * \brief Sets Field of View of Camera.
		  *
		  * @param fov Field of View value.
		  */
		#pragma endregion
		void setFov(float fov);

		#pragma region documentation
		/**
		  * \brief Gets Aspect ratio of Camera.
		  *
		  * Returns width to height proportions of the Camera.
		  * @return Aspect Ratio of the Camera.
		  */
		#pragma endregion
		float getAspectRatio();
		#pragma region documentation
		/**
		  * \brief Sets Aspect ratio of Camera.
		  *
		  * Sets width to height proportions of the Camera.
		  * @param aspectRatio Aspect Ratio of the Camera.
		  */
		#pragma endregion
		void setAspectRatio(float aspectRatio);

		#pragma region documentation
		/**
		  * \brief Gets Near Clipping Plane distance.
		  *
		  * @return Near Clipping Plane distance.
		  */
		#pragma endregion
		float getZNear();
		#pragma region documentation
		/**
		  * \brief Sets Near Clipping Plane distance.
		  *
		  * @param zNear Near Clipping Plane distance.
		  */
		#pragma endregion
		void setZNear(float zNear);
		#pragma region documentation
		/**
		  * \brief Gets Far Clipping Plane distance.
		  *
		  * @return Far Clipping Plane distance.
		  */
		#pragma endregion
		float getZFar();
		#pragma region documentation
		/**
		  * \brief Sets Far Clipping Plane distance.
		  *
		  * @param zFar Far Clipping Plane Distance.
		  */
		#pragma endregion
		void setZFar(float zFar);

		#pragma region documentation
		/**
		  * \brief Gets Camera Matrix.
		  *
		  * Gets Camera Matrix without Projection.
		  * @return 4x4 Camera Martix.
		  */
		#pragma endregion
		glm::mat4 getCameraMatrix();
		#pragma region documentation
		/**
		  * \brief Gets Projection Matrix.
		  *
		  * Gets Projection Matrix without Camera Matrix.
		  * @return 4x4 Projection Matrix.2
		  */
		#pragma endregion
		glm::mat4 getProjectionMatrix();

		#pragma region documentation
		/**
		  * \brief Serializes Camera to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes Camera from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Camera object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create Camera instance while serializing.
		  */
		#pragma endregion
		Camera();

		#pragma region documentation
		/**
		  * \brief Updates Camera Matrix and Projection matrices.
		  *
		  * Mostly for internal use in engine part of code.
		  */
		#pragma endregion
		void CalculateMatrix();

	private:
		Transform* transform;
		Transform previousTransform;

		glm::vec3 target;
		glm::vec3 up;

		bool isEvaluated = false;
		glm::mat4 cameraMatrix;
		glm::mat4 projectionMatrix;

		float fov;
		float aspectRatio;
		float zNear;
		float zFar;
	};

}