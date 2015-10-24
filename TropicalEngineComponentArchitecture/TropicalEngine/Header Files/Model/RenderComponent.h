#pragma once
#include <QtCore/qlist.h>

#include <Component/Component.h>

/**
  * Base class for renderable components.
  */
class RenderComponent : public Component
{
public:
	TYPENAME("Render Component")

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

	virtual void Evaluate() = 0;

	/**
	  * \brief Draws the Component.
	  *
	  * @param Draws from perspective of this camera.
	  */
	virtual void Draw(class CameraComponent* viewer) = 0;

protected:
	/**
	* \brief Simple Constructor used to create RenderComponent instance while serializing.
	*/
	RenderComponent();

	void InitializeComponentType() override;
};

