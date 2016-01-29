#pragma once
#include <QtCore/qlist.h>

#include <Component/Component.h>

#include "IRenderable.h"

namespace TropicalEngine
{
	// TODO: Figure out changing Component place in Rendering Manager after changing level owning Entity belong to.
	// TODO: Finish documenting RenderComponent class.
	#pragma region documentation
	/**
	  * \brief Base class for renderable components.
	  */
	#pragma endregion
	class RenderComponent : public Component, virtual public IRenderable
	{
	public:
		TYPENAME(RenderComponent)

		#pragma region documentation
		/**
		  * \brief Material used by this Component.
		  */
		#pragma endregion
		class Material* material;


		//protected:	//temporarily public
		QList<class LightComponent*> lightedBy;

		#pragma region documentation
		/**
		  * \brief Constructor of RenderComponent.
		  *
		  * @param owner Entity object to which RenderComponent will be attached to.
		  * @param material Material to be set for this component.
		  */
		#pragma endregion
		RenderComponent(Entity* owner, class Material* material);
		#pragma region documentation
		/**
		  * \brief Destructor for Render Component.
		  */
		#pragma endregion
		~RenderComponent(void);

		virtual void levelChanged() override;

		virtual void Evaluate() = 0;

	protected:
		#pragma region documentation
		/**
		* \brief Simple Constructor used to create RenderComponent instance while serializing.
		*/
		#pragma endregion
		RenderComponent();

		void InitializeComponentType() override;
	};

}