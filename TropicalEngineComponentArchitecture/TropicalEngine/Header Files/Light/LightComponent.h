#pragma once
#include <glm.hpp>

#include <Component/Component.h>

#define MAX_POINT_LIGHT 2
#define MAX_SPOT_LIGHT 2

namespace TropicalEngine
{

	// TODO: Figure out if it should be an abstract class?
	#pragma region documentation
	/**
	  * \brief Base class for concrete LightComponent classes.
	  */
	#pragma endregion
	class LightComponent : public Component
	{
	public:
		TYPENAME(LightComponent)

		#pragma region documentation
		/**
		  * \brief Color of the light.
		  *
		  * Color of the light in RGB format in [0.0 ; 1.0] space.
		  */
		#pragma endregion
		glm::vec3 color;
		#pragma region documentation
		/**
		  * \brief Brightness of the light.
		  */
		#pragma endregion
		float brightness;

		#pragma region documentation
		/**
		  * \brief Constructor of LightComponent.
		  *
		  * @param owner Entity object the light will be attached to.
		  * @param color Color of the light.
		  * @param brightness Brightness of the light.
		  * @param isCastingShadows Decides if this light should cast shadows.
		  */
		#pragma endregion
		LightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f, bool isCastingShadows = false);
		#pragma region documentation
		/**
		  * \brief Destructor for LightComponent.
		  */
		#pragma endregion
		~LightComponent(void);

		#pragma region documentation
		/**
		  * \brief Gets information if this light is casting shadows.
		  *
		  * @return Information if this light is casting shadows.
		  */
		#pragma endregion
		bool isCastingShadows();
		#pragma region documentation
		/**
		  * \brief Sets information if this light should cast shadows.
		  *
		  * @param isCastingShadows Information if this light should cast shadows.
		  */
		#pragma endregion
		void isCastingShadows(bool isCastingShadows);

		#pragma region documentation
		/**
		  * \brief Gets Shadowmap texture.
		  *
		  * @return Shadowmap texture.
		  */
		#pragma endregion
		class Texture* getShadowmap();

		virtual void Evaluate();
		virtual void DrawShadows() {};

		#pragma region documentation
		/**
		  * \brief Serializes LightComponent to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;

	protected:
		#pragma region documentation
		/**
		  * \brief Is this light casting shadows.
		  */
		#pragma endregion
		bool castingShadows;

		class RenderTexture* shadowmap = nullptr;

		#pragma region documentation
		/**
		  * \brief Simple Constructor used to create Component instance while serializing.
		  */
		#pragma endregion
		LightComponent();

		void InitializeComponentType() override;
	};

}