#pragma once
#include <glm.hpp>

#include <Component/Component.h>

#define MAX_POINT_LIGHT 2
#define MAX_SPOT_LIGHT 2

namespace TropicalEngine
{

	///TODO: Should it be an abstract class?
	class LightComponent : public Component
	{
	public:
		TYPENAME(LightComponent)

		/**
		  * \brief Color of the light.
		  *
		  * Color of the light in RGB format in [0.0 ; 1.0] space.
		  */
		glm::vec3 color;

		/**
		  * \brief Brightness of the light.
		  */
		float brightness;

		/**
		  * \brief Constructor of LightComponent.
		  *
		  * @param owner Entity object the light will be attached to.
		  * @param color Color of the light.
		  * @param brightness Brightness of the light.
		  * @param isCastingShadows Decides if this light should cast shadows.
		  */
		LightComponent(Entity* owner, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float brightness = 1.0f, bool isCastingShadows = false);

		/**
		  * \brief Destructor for LightComponent.
		  */
		~LightComponent(void);

		/**
		  * \brief Gets information if this light is casting shadows.
		  *
		  * @return Information if this light is casting shadows.
		  */
		bool isCastingShadows();

		/**
		  * \brief Sets information if this light should cast shadows.
		  *
		  * @param isCastingShadows Information if this light should cast shadows.
		  */
		void isCastingShadows(bool isCastingShadows);

		virtual void Evaluate();
		virtual void DrawShadows() {};

		/**
		  * \brief Serializes LightComponent to JSON object.
		  *
		  * @return Result of serialization.
		  */
		QJsonObject toJSON() override;

	protected:

		/**
		  * \brief Is this light casting shadows.
		  */
		bool castingShadows;

		/**
		  * \brief Simple Constructor used to create Component instance while serializing.
		  */
		LightComponent();

		void InitializeComponentType() override;
	};

}