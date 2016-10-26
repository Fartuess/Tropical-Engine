#pragma once

#include <glm.hpp>

#include <Component/Component.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Component used for prerendered panoramic reflections.
	  */
	#pragma endregion
	class ReflectionProbeComponent : public Component
	{
	public:
		TYPENAME(ReflectionProbeComponent)

		#pragma region documentation
		/**
		  * \brief Constructor for ReflectionProbeComponent.
		  *
		  * @param owner Enity owning this component.
		  * @param texture Prerendered panoramic Texture representing reflection.
		  * @param radius Radius of influence of ReflectionProbeComponent.
		  * @param strength Influence strength multiplayer.
		  * @param attenuation Attenuation of influence field.
		  */
		#pragma endregion
		ReflectionProbeComponent(Entity* owner, class Texture* texture, float radius = 1.0f, float strength = 1.0f, float attenuation = 1.0f);
		#pragma region documentation
		/**
		  * \brief Destructor for ReflectionProbeComponent.
		  */
		#pragma endregion
		~ReflectionProbeComponent();

		static ReflectionProbeComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Gets influence radius.
		  *
		  * @return Influence radius.
		  */
		#pragma endregion
		float getRadius()	{ return radius; }
		#pragma region documentation
		/**
		  * \brief Sets influence radius.
		  *
		  * @param radius Influence radius.
		  */
		#pragma endregion
		void setRadius(float radius)	{ this->radius = radius; }

		#pragma region documentation
		/**
		  * \brief Gets influence strength multiplier.
		  *
		  * @return Influence strength multiplier.
		  */
		#pragma endregion
		float getStrength()	{ return strength; }
		#pragma region documentation
		/**
		  * \brief Sets influence strength multiplier.
		  *
		  * @param strenght Influence strength multiplier.
		  */
		#pragma endregion
		void setStrength(float strength)	{ this->strength = strength; }

		#pragma region documentation
		/**
		  * \brief Gets influence attenuation.
		  *
		  * @return Influence attenuation.
		  */
		#pragma endregion
		float getAttenuation()	{ return attenuation; }
		#pragma region documentation
		/**
		  * \brief Sets influence attenutation.
		  *
		  * @param attenuation Influence attenuation.
		  */
		#pragma endregion
		void setAttenuation(float attenuation)	{ this->attenuation = attenuation; }

		#pragma region documentation
		/**
		  * \brief Gets reflection Texture.
		  *
		  * @return Reflection Texture.
		  */
		#pragma endregion
		class Texture* getTexture()	{ return texture; }
		#pragma region documentation
		/**
		  * \brief Sets reflection Texture.
		  */
		#pragma endregion
		void setTexture(class Texture* texture)	{ this->texture = texture; }

		#pragma region documentation
		/**
		  * \brief Gets influence strength for specific point in world space.
		  *
		  * @param position Position in world space for which to calculate influence strength.
		  *
		  * @return Influence Strength.
		  */
		#pragma endregion
		float getInfluence(glm::vec3 position);

	protected:
		float radius;
		float strength;
		float attenuation;
		class Texture* texture;	// panoramic latlong texture

		ReflectionProbeComponent()	{}
		void InitializeComponentType() override;
	};

}