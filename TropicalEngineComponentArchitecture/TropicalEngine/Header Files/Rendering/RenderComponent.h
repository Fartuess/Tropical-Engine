#pragma once
#include <QtCore/qlist.h>

#include <Component/Component.h>

#include "IRenderable.h"

namespace TropicalEngine
{
	/// TODO: Figure out changing Component place in Rendering Manager after changing level owning Entity belong to.
	/**
	  * Base class for renderable components.
	  */
	class RenderComponent : public Component, virtual public IRenderable
	{
	public:
		TYPENAME(RenderComponent)

		/**
		  * \brief Material used by this Component.
		  */
		class Material* material;


		//protected:	//temporarily public
		QList<class LightComponent*> lightedBy;

		/**
		  * \brief Constructor of RenderComponent.
		  *
		  * @param owner Entity object to which RenderComponent will be attached to.
		  * @param material Material to be set for this component.
		  */
		RenderComponent(Entity* owner, class Material* material);

		/**
		  * \brief Destructor for Render Component.
		  */
		~RenderComponent(void);

		virtual void levelChanged() override;

		virtual void Evaluate() = 0;

		/**
		  * \brief Draws the Component.
		  *
		  * @param Draws from perspective of this camera.
		  */
		//virtual void Draw(class CameraComponent* viewer) = 0;

	protected:
		/**
		* \brief Simple Constructor used to create RenderComponent instance while serializing.
		*/
		RenderComponent();

		void InitializeComponentType() override;
	};

}