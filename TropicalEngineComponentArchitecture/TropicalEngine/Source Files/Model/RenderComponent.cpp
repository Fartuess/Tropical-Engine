#include <Model/RenderComponent.h>
#include <Shader/Shader.h>

namespace TropicalEngine
{

	RenderComponent::RenderComponent() {}

	RenderComponent::RenderComponent(Entity* owner, Material* material) :Component(owner)
	{
		if (material != nullptr)
			this->material = material;
		else
			this->material = Shader::nullShader->defaultMaterial;
		lightedBy = QList<LightComponent*>();
		InitializeComponentType();
	}

	void RenderComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			AddParameter("Material", "String");
		}
	}

	RenderComponent::~RenderComponent(void)
	{
	}

	//void Evaluate()
	//{
	//	///TODO: implement it.
	//}

}