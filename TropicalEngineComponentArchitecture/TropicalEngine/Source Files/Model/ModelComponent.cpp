#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <QtCore/qdebug.h>

#include <Model/ModelComponent.h>
#include <Model/ModelController.h>
#include <Model/ModelManager.h>
#include <Model/Model.h>
#include <Shader/Shader.h>
#include <Shader/Material.h>
#include <Shader/ShaderManager.h>
#include <Shader/MaterialManager.h>
#include <Scene/Entity.h>
#include <Scene/TransformComponent.h>
#include <Scene/SceneManager.h>
#include <Camera/CameraComponent.h>
#include <Light/DirectionalLightComponent.h>
#include <Light/PointLightComponent.h>

#include "TropicalEngineApplication.h"

ModelComponent ModelComponent::templateObject = ModelComponent::InitializeType();

ModelComponent::ModelComponent() {}

ModelComponent::ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows):RenderComponent(owner, material)
{
	this->model = model;
	this->castingShadows = castingShadows;
	TropicalEngineApplication::instance()->modelController->AddComponent(this);

	InitializeComponentType();
}

ModelComponent::~ModelComponent(void)
{
	if (owner != nullptr)
	{
		TropicalEngineApplication::instance()->modelController->modelComponents.removeOne(this);
	}
}

ModelComponent ModelComponent::InitializeType()
{
	ModelComponent& modelComponent = *(new ModelComponent());
	AssetManager::addAssetType("Model Component", &modelComponent);
	return modelComponent;
}

void ModelComponent::InitializeComponentType()
{
	if (!isComponentTypeUsed(getTypeName()))
	{
		SetParrentComponentType("Render Component");

		AddParameter("Model", "String");
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

	Shader* usedShader = material->getShader();

	glUniformMatrix4fv(usedShader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getTransformMatrix()));
	glUniformMatrix3fv(usedShader->getNormalMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getNormalMatrix()));
	glUniform3fv(usedShader->getCameraPositionLocation(), 1, glm::value_ptr(viewer->getOwner()->transform.getLocalPosition()));	///TODO: Change to global position when it will work
	glUniformMatrix4fv(usedShader->getCameraMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getCameraMatrix()));
	glUniformMatrix4fv(usedShader->getProjectionMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getProjectionMatrix()));

	glUniform3fv(usedShader->dirLightVectorLocation, 1, glm::value_ptr(TropicalEngineApplication::instance()->sceneManager->mainLight->getDirection()));
	glUniform3fv(usedShader->dirLightColorLocation, 1, glm::value_ptr(TropicalEngineApplication::instance()->sceneManager->mainLight->color));
	glUniform1f(usedShader->dirLightBrightnessLocation, TropicalEngineApplication::instance()->sceneManager->mainLight->brightness);
	glUniform1f(usedShader->dirLightAmbientLocation, 0.2f);

	if (usedShader->pointLightPositionLocations.size() > 0)
	{
		for (int i = 0; i < glm::min(MAX_POINT_LIGHT, lightedBy.size()); i++)	///TODO: Assuming that it is lighted only by pointlights. Change it later to work properly
		{
			PointLightComponent* light = static_cast<PointLightComponent*>(lightedBy[i]);
			glUniform3fv(usedShader->pointLightPositionLocations[i], 1, glm::value_ptr(-light->getOwner()->transform.getLocalPosition()));	///TODO: Figure out why negation is required.
			glUniform3fv(usedShader->pointLightColorLocations[i], 1, glm::value_ptr(light->color));
			glUniform1f(usedShader->pointLightBrightnessLocations[i], light->brightness);
			glUniform1f(usedShader->pointLightRadiusLocations[i], light->getRadius());
			glUniform1f(usedShader->pointLightAttenuationLocations[i], light->attenuation);
		}
	}
	
	for (MeshEntry* meshEntry : model->meshes)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshEntry->vertexVBO);
		glEnableVertexAttribArray(usedShader->getVertexLocation());
		glEnableVertexAttribArray(usedShader->getNormalLocation());
		glEnableVertexAttribArray(usedShader->getTangentLocation());
		glEnableVertexAttribArray(usedShader->getBitangentLocation());
		glEnableVertexAttribArray(usedShader->getTexcoordLocation());

		glVertexAttribPointer(usedShader->getVertexLocation(), 4, GL_FLOAT, GL_FALSE, 0,
			0);
		glVertexAttribPointer(usedShader->getNormalLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)(sizeof(glm::vec4) * meshEntry->NumVertex));
		glVertexAttribPointer(usedShader->getTangentLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ sizeof(glm::vec3))
			* meshEntry->NumVertex));
		glVertexAttribPointer(usedShader->getBitangentLocation(), 3, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ 2 * sizeof(glm::vec3))
			* meshEntry->NumVertex));
		glVertexAttribPointer(usedShader->getTexcoordLocation(), 2, GL_FLOAT, GL_FALSE, 0,
			(void*)((
			sizeof(glm::vec4)
			+ 3 * sizeof(glm::vec3))
			* meshEntry->NumVertex));
		
		//glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_BACK, GL_LINE);
		//glDrawArrays(GL_PATCHES, 0, meshEntry.NumVertex);
		glDrawArrays(usedShader->drawingMode, 0, meshEntry->NumVertex);
		//glDrawArrays(GL_TRIANGLES, 0, meshEntry.NumVertex);
	
		glDisableVertexAttribArray(usedShader->getVertexLocation());
		glDisableVertexAttribArray(usedShader->getNormalLocation());
		glDisableVertexAttribArray(usedShader->getTangentLocation());
		glDisableVertexAttribArray(usedShader->getBitangentLocation());
		glDisableVertexAttribArray(usedShader->getTexcoordLocation());
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

//QString ModelComponent::toXML()
//{
//	return QString(getIndent() + "<ModelComponent model = \"" + model->getName() + "\" material =\"" + material->getName() + "\"/>\n");
//}

QJsonObject ModelComponent::toJSON()
{
	QJsonObject JSON = Component::toJSON();
	JSON["model"] = model->getName();
	JSON["material"] = material->getName();
	JSON["cast shadows"] = castingShadows;

	return JSON;
}

IDeserializableFromJSON* ModelComponent::fromJSON(QJsonObject JSON)
{
	ModelComponent* object = new ModelComponent();

	object->model = TropicalEngineApplication::instance()->modelManager->getModel(JSON["model"].toString());
	object->material = (*TropicalEngineApplication::instance()->materialManager)[JSON["material"].toString()];
	object->castingShadows = JSON["cast shadows"].toBool();

	return object;
}