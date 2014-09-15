#include "RenderComponent.h"
#include "Shader.h"

RenderComponent::RenderComponent(Entity* owner, Material* material):Component(owner)
{
	if(material != nullptr)
		this->material = material;
	else
		this->material = Shader::nullShader->defaultMaterial;
	lightedBy = QList<LightComponent*>();
	InitializeComponentType();
}

void RenderComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		AddParameter("Material", "String");
	}
}

QString RenderComponent::COMPONENTGETNAME("Render Component");

RenderComponent::~RenderComponent(void)
{
}

//void Evaluate()
//{
//	///TODO: implement it.
//}
//
//void Draw(CameraComponent* viewer)
//{
//	///TODO: implement it.
//}
