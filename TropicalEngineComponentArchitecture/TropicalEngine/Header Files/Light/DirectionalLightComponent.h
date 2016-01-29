#pragma once
#include "LightComponent.h"

namespace TropicalEngine
{
	/// TODO: Finish documenting it.
	#pragma region documentation
	/**
	  * \brief Component enlighting Scene with directional light.
	  */
	#pragma endregion
	class DirectionalLightComponent : public LightComponent
	{
	public:
		TYPENAME(DirectionalLightComponent)

		#pragma region documentation
		/**
		  * \brief Constructor of DirectionalLightComponent.
		  *
		  * @param owner Entity object the light will be attached to.
		  * @param color Color of the light.
		  * @param direction Direction vector defining angle of the light.
		  * @param brightness Brightness of the light.
		  * @param isCastingShadows Decides if this light should cast shadows.
		  */
		#pragma endregion
		DirectionalLightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f), float brightness = 1.0f, bool isCastingShadows = false);
		#pragma region documentation
		/**
		  * \brief Destructor for DirectionalLightComponent.
		  */
		#pragma endregion
		~DirectionalLightComponent(void);

		static DirectionalLightComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Gets direction vector of the light.
		  *
		  * @return Direction vector of the light.
		  */
		#pragma endregion
		glm::vec3 getDirection();
		
		#pragma region documentation
		/**
		  * \brief Sets direction vector of the light.
		  *
		  * @param direction Direction of the light.
		  */
		#pragma endregion
		void setDirection(glm::vec3 direction);

		virtual void Evaluate() override;
		virtual void DrawShadows() override;

		#pragma region documentation
		/**
		  * \brief Serializes Component to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes DirectionalLightComponent from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return DirectionalLightComponent object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create DirectionalLightComponent instance while serializing.
		  */
		#pragma endregion
		DirectionalLightComponent();

		#pragma region documentation
		/**
		  * \brief Initialized type in global typemap.
		  */
		#pragma endregion
		void InitializeComponentType() override;

	private:
		glm::vec3 direction;

		static DirectionalLightComponent templateObject;
	};

}