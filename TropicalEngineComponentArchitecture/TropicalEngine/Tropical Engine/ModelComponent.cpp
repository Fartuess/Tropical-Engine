#include <glm.hpp>
#include <gtc\type_ptr.hpp>
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

#include "SceneManager.h"
#include "DirectionalLightComponent.h"

#include "TropicalEngineApplication.h"

ModelComponent::ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows):RenderComponent(owner, material)
{
	this->model = model;
	this->castingShadows = castingShadows;
	TropicalEngineApplication::instance()->modelController->AddComponent(this);
}

ModelComponent::~ModelComponent(void)
{
	if(owner != nullptr)
	{
		TropicalEngineApplication::instance()->modelController->modelComponents.removeOne(this);
	}
}

void ModelComponent::Evaluate()
{
	///TODO: implement it.
}

void ModelComponent::Draw(CameraComponent* viewer)
{
	///TODO: implement it.
	material->Use();

	//glm::mat4 check = viewer->getMatrix();

	glUniformMatrix4fv(material->getShader()->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getTransformMatrix()));
	glUniformMatrix3fv(material->getShader()->getNormalMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getNormalMatrix()));
	glUniformMatrix4fv(material->getShader()->getCameraMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getCameraMatrix()));
	glUniformMatrix4fv(material->getShader()->getProjectionMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getProjectionMatrix()));

	//temp? Light code
	glUniform3fv(material->getShader()->dirLightVectorLocation, 1, glm::value_ptr(TropicalEngineApplication::instance()->sceneManager->mainLight->getDirection()));
	glUniform3fv(material->getShader()->dirLightColorLocation, 1, glm::value_ptr(TropicalEngineApplication::instance()->sceneManager->mainLight->color));
	glUniform1f(material->getShader()->dirLightBrightnessLocation, TropicalEngineApplication::instance()->sceneManager->mainLight->brightness);
	glUniform1f(material->getShader()->dirLightAmbientLocation, 0.2f);
	
	foreach(MeshEntry meshEntry, model->meshes)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshEntry.vertexVBO);
		glEnableVertexAttribArray(material->getShader()->getVertexLocation());
		glEnableVertexAttribArray(material->getShader()->getNormalLocation());
		glEnableVertexAttribArray(material->getShader()->getTangentLocation());
		glEnableVertexAttribArray(material->getShader()->getBitangentLocation());
		glEnableVertexAttribArray(material->getShader()->getTexcoordLocation());

		glVertexAttribPointer(material->getShader()->getVertexLocation(), 4, GL_FLOAT, GL_FALSE, 0,
			0);
		glVertexAttribPointer(material->getShader()->getNormalLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)(sizeof(glm::vec4) * meshEntry.NumVertex));
		glVertexAttribPointer(material->getShader()->getTangentLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ sizeof(glm::vec3))
			* meshEntry.NumVertex));
		glVertexAttribPointer(material->getShader()->getBitangentLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ 2 * sizeof(glm::vec3))
			* meshEntry.NumVertex));
		glVertexAttribPointer(material->getShader()->getTexcoordLocation(), 2, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ 3 * sizeof(glm::vec3))
			* meshEntry.NumVertex));
		
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

QString ModelComponent::toXML()
{
	return QString(getIndent() + "<ModelComponent model = \"" + model->name + "\" material =\"" + material->name + "\"/>\n");
}