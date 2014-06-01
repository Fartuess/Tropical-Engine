#include "ModelComponent.h"
#include "ModelController.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "ShaderManager.h"
#include "Entity.h"


ModelComponent::ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows):RenderComponent(owner, material)
{
	this->model = model;
	this->castingShadows = castingShadows;
	ModelController::Instance().AddComponent(this);
}


ModelComponent::~ModelComponent(void)
{
	if(owner != nullptr)
	{
		ModelController::Instance().modelComponents.removeOne(this);
	}
}

void ModelComponent::Evaluate()
{
	///TODO: implement it.
}

void ModelComponent::Draw(CameraComponent* viewer)
{
	///TODO: implement it.
	ShaderManager::Instance().UseShader(material->getShader());

	foreach(MeshEntry meshEntry, model->meshes)
	{
		glBindVertexArray(meshEntry.VAO);
		glEnableVertexAttribArray(material->getShader()->getVertexLocation());
		glEnableVertexAttribArray(material->getShader()->getNormalLocation());
		glEnableVertexAttribArray(material->getShader()->getTangentLocation());
		glEnableVertexAttribArray(material->getShader()->getBitangentLocation());
		glEnableVertexAttribArray(material->getShader()->getTexcoordLocation());
		

		glDrawArrays(GL_TRIANGLES, 0, meshEntry.NumVertex);

	}
}

bool ModelComponent::isCastingShadows()
{
	return castingShadows;
}

void ModelComponent::isCastingShadows(bool isCastingShadows)
{
	castingShadows = isCastingShadows;
}
