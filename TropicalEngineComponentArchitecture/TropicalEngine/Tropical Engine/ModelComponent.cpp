#include <glm.hpp>
#include "ModelComponent.h"
#include "ModelController.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "ShaderManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "CameraComponent.h"


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

	glUniformMatrix4fv(material->getShader()->getModelMatrixLocation(), 16, GL_FALSE, &(owner->transform.getTransformMatrix()[0][0]));
	glUniformMatrix3fv(material->getShader()->getNormalMatrixLocation(), 9, GL_FALSE, &(owner->transform.getNormalMatrix()[0][0]));
	glUniformMatrix4fv(material->getShader()->getCameraMatrixLocation(), 16, GL_FALSE, &(viewer->getMatrix()[0][0]));
	
	foreach(MeshEntry meshEntry, model->meshes)
	{
		glBindVertexArray(meshEntry.VAO);
		glEnableVertexAttribArray(material->getShader()->getVertexLocation());
		glEnableVertexAttribArray(material->getShader()->getNormalLocation());
		glEnableVertexAttribArray(material->getShader()->getTangentLocation());
		glEnableVertexAttribArray(material->getShader()->getBitangentLocation());
		glEnableVertexAttribArray(material->getShader()->getTexcoordLocation());
		
		glDrawArrays(GL_TRIANGLES, 0, meshEntry.NumVertex);
	
		glDisableVertexAttribArray(material->getShader()->getVertexLocation());
		glDisableVertexAttribArray(material->getShader()->getNormalLocation());
		glDisableVertexAttribArray(material->getShader()->getTangentLocation());
		glDisableVertexAttribArray(material->getShader()->getBitangentLocation());
		glDisableVertexAttribArray(material->getShader()->getTexcoordLocation());
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
