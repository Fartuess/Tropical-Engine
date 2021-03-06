#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <QtCore/qdebug.h>

#include <Model/ModelComponent.h>
#include <Model/ModelManager.h>
#include <Model/Model.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>
#include <Shader/Material.h>
#include <Shader/ShaderManager.h>
#include <Shader/MaterialManager.h>

#include <Scene/Entity.h>
#include <Scene/TransformComponent.h>

#include <Scene/Scene.h>

#include <Camera/CameraComponent.h>

#include <Light/DirectionalLightComponent.h>
#include <Light/PointLightComponent.h>
#include <Light/SpotLightComponent.h>
#include <Light/AmbientLightComponent.h>
#include <Light/LightController.h>

namespace TropicalEngine
{

	ModelComponent ModelComponent::templateObject = ModelComponent::InitializeType();

	ModelComponent::ModelComponent() {}

	ModelComponent::ModelComponent(Entity* owner, Material* material, Model* model, bool castingShadows) : RenderComponent(owner, material)
	{
		this->model = model;
		this->castingShadows = castingShadows;
		if (castingShadows)
		{
			LightController::instance().shadowcasters.append(this);
		}

		InitializeType();
		InitializeComponentType();
	}

	ModelComponent::~ModelComponent(void)
	{
		//if (owner != nullptr)
		//{
		//	TropicalEngineApplication::instance()->modelController->modelComponents.removeOne(this);
		//}
	}

	ModelComponent ModelComponent::InitializeType()
	{
		ModelComponent& modelComponent = *(new ModelComponent());
		AssetManager::instance().addAssetType("Model Component", &modelComponent);
		return modelComponent;
	}

	QSet<QString> ModelComponent::getShaderPasses()
	{
		return material->getShaderTechnique()->getShaderPasses().keys().toSet();
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
		// TODO: implement it.
	}

	void ModelComponent::Draw(CameraComponent* viewer, QString shaderPass)
	{
		material->Use();

		Shader* usedShader;

		if (material->getShaderTechnique() == nullptr)
		{
			usedShader = material->getShader();
		}
		else
		{
			usedShader = material->getShaderTechnique()->getShader(shaderPass);
		}

		// TODO: Move Uniform binding into specific classes?

		glUniformMatrix4fv(usedShader->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getTransformMatrix()));
		glUniformMatrix3fv(usedShader->getNormalMatrixLocation(), 1, GL_FALSE, glm::value_ptr(owner->transform.getNormalMatrix()));
		glUniform3fv(usedShader->getCameraPositionLocation(), 1, glm::value_ptr(viewer->getOwner()->transform.getLocalPosition()));	// TODO: Change to global position when it will work
		glUniformMatrix4fv(usedShader->getCameraMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getCameraMatrix()));
		glUniformMatrix4fv(usedShader->getProjectionMatrixLocation(), 1, GL_FALSE, glm::value_ptr(viewer->getProjectionMatrix()));

		// TODO: This for range doesn't count directional and ambient light.
		int pointLightId = 0;
		int spotLightId = 0;
		for (int i = 0; i < glm::min(usedShader->pointLightPositionLocations.size() + usedShader->spotLightPositionLocations.size(), lightedBy.size()); i++)
		{
			QString lightType = lightedBy[i]->getTypeName();

			if (lightType == "AmbientLightComponent")
			{
				AmbientLightComponent* ambientLight = static_cast<AmbientLightComponent*>(lightedBy[i]);

				glUniform1f(usedShader->ambientLightBrightnessLocation, ambientLight->brightness);
				glUniform3fv(usedShader->ambientLightColorLocation, 1, glm::value_ptr(ambientLight->color));
			}

			if (lightType == "DirectionalLightComponent")
			{
				DirectionalLightComponent* directionalLight = static_cast<DirectionalLightComponent*>(lightedBy[i]);
				glUniform3fv(usedShader->dirLightVectorLocation, 1, glm::value_ptr(directionalLight->getDirection()));
				glUniform3fv(usedShader->dirLightColorLocation, 1, glm::value_ptr(directionalLight->color));
				glUniform1f(usedShader->dirLightBrightnessLocation, directionalLight->brightness);
			}
			else if (lightType == "PointLightComponent")
			{
				PointLightComponent* light = static_cast<PointLightComponent*>(lightedBy[i]);
				TransformComponent& lightTransform = light->getOwner()->transform;
				glUniform3fv(usedShader->pointLightPositionLocations[pointLightId], 1, glm::value_ptr(lightTransform.getLocalPosition()));	// TODO: Figure out why negation is required.
				glUniform3fv(usedShader->pointLightColorLocations[pointLightId], 1, glm::value_ptr(light->color));
				glUniform1f(usedShader->pointLightBrightnessLocations[pointLightId], light->brightness);
				glUniform1f(usedShader->pointLightRadiusLocations[pointLightId], light->getRadius());
				glUniform1f(usedShader->pointLightAttenuationLocations[pointLightId], light->attenuation);

				pointLightId++;
			}
			else if (lightType == "SpotLightComponent")
			{
				SpotLightComponent* light = static_cast<SpotLightComponent*>(lightedBy[i]);
				TransformComponent& lightTransform = light->getOwner()->transform;
				glUniform3fv(usedShader->spotLightPositionLocations[spotLightId], 1, glm::value_ptr(lightTransform.getLocalPosition() * glm::vec3(1.0, 1.0, 1.0)));
				//glUniform3fv(usedShader->spotLightDirectionLocations[spotLightId], 1, glm::value_ptr(glm::vec3(glm::rotate(glm::mat4(), glm::angle(lightTransform.getLocalRotation()), glm::axis(lightTransform.getLocalRotation())) * (-1.0f) * glm::vec4(lightTransform.getFront(), 1.0f))));
				glUniform3fv(usedShader->spotLightDirectionLocations[spotLightId], 1, glm::value_ptr((-1.0f) * lightTransform.getFront()));
				glUniform3fv(usedShader->spotLightColorLocations[spotLightId], 1, glm::value_ptr(light->color));
				glUniform1f(usedShader->spotLightBrightnessLocations[spotLightId], light->brightness);
				glUniform1f(usedShader->spotLightRadiusLocations[spotLightId], light->getRadius());
				glUniform1f(usedShader->spotLightAttenuationLocations[spotLightId], light->attenuation);
				glUniform1f(usedShader->spotLightOuterAngleLocations[spotLightId], light->getOuterConeRadius());
				glUniform1f(usedShader->spotLightInnerAngleLoactions[spotLightId], light->getInnerConeRadius());

				spotLightId++;
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

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			if (!meshEntry->isBackfacing)
			{
				glFrontFace(GL_CCW);
			}
			else
			{
				glFrontFace(GL_CW);

			}

			glDrawArrays(usedShader->drawingMode, 0, meshEntry->NumVertex);

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
		if (castingShadows)
		{
			LightController::instance().shadowcasters.append(this);
		}
		else
		{
			LightController::instance().shadowcasters.removeAll(this);
		}
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

		object->model = ModelManager::instance().getModel(JSON["model"].toString());
		object->material = MaterialManager::instance()[JSON["material"].toString()];
		object->castingShadows = JSON["cast shadows"].toBool();

		return object;
	}

}