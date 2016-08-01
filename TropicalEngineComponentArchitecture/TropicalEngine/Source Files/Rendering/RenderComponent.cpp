#include <Rendering/RenderComponent.h>
#include <Rendering/RenderingManager.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>

namespace TropicalEngine
{

	RenderComponent::RenderComponent() {}

	RenderComponent::RenderComponent(Entity* owner, Material* material) : Component(owner)
	{
		if (material != nullptr)
		{
			this->material = material;
		}
		else
		{
			this->material = Shader::nullShader->defaultMaterial;
		}
		//lightedBy = QList<LightComponent*>();
		InitializeComponentType();

		levelChanged();
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

	void RenderComponent::levelChanged()
	{
		RenderingManager::instance().removeRenderableObject(this);

		if (this->material->getShaderTechnique() != nullptr)
		{
			for (QString shaderPass : this->material->getShaderTechnique()->getShaderPasses().keys())
			{
				RenderingManager::instance().addRenderableObject(this, getLevel(), shaderPass);
			}
		}
		else
		{
			RenderingManager::instance().addRenderableObject(this, getLevel(), "Default");
		}
	}

	//void Evaluate()
	//{
	//	// TODO: implement it.
	//}

}