#include <Rendering/RenderComponent.h>
#include <Rendering/RenderingManager.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>

#include <TropicalEngineApplication.h>

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
		TropicalEngineApplication::instance()->renderingManager->removeRenderableObject(this);

		if (this->material->getShaderTechnique() != nullptr)
		{
			for (QString shaderPass : this->material->getShaderTechnique()->getShaderPasses().keys())
			{
				TropicalEngineApplication::instance()->renderingManager->addRenderableObject(this, getLevel(), shaderPass);
			}
		}
		else
		{
			TropicalEngineApplication::instance()->renderingManager->addRenderableObject(this, getLevel(), "Color");
		}
	}

	//void Evaluate()
	//{
	//	// TODO: implement it.
	//}

}