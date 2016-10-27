#include <gtc/quaternion.hpp>

#include <QtCore/qmap.h>

#include <ReflectionProbe/ReflectionProbeManager.h>
#include <ReflectionProbe/ReflectionProbeComponent.h>

#include <Shader/ShaderTechnique.h>
#include <Shader/ShaderBuilder/CommonMeshShaderBuilder.h>
#include <Shader/Material.h>
//#include <Shader/ShaderManager.h>

#include <Model/ModelBuilder/PlaneModelBuilder.h>
#include <Model/ModelComponent.h>
#include <Model/ModelManager.h>

#include <Utills/Directions.h>

#include <Scene/Entity.h>
#include <Scene/Scene.h>

#include <Camera/CameraComponent.h>

#include <QtCore/qdebug.h>

namespace TropicalEngine
{

	ReflectionProbeManager::ReflectionProbeManager() : reflectionTexture("Reflection", 1024, 512)
	{
		//reflectionBlendingScene = 

		reflectionBlendingTechnique = new ShaderTechnique("Reflection Blending", &CommonMeshShaderBuilder::instance());
		reflectionBlendingTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		reflectionBlendingTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		reflectionBlendingTechnique->setInput("Surface Shader", "./Shader Files/Lighting/ReflectionProbes/PoiReflectionBlend.glsl");

		reflectionBlendingTechnique2 = new ShaderTechnique("Reflection Blending 2", reflectionBlendingTechnique->getShader(), "ReflectionPOI");

		reflectionBlendingMaterial = new Material(reflectionBlendingTechnique2, "Reflection Blending Material");

		PlaneModelBuilder FrameBuilder = PlaneModelBuilder();
		FrameBuilder.setParameter("name", QString("Frame"));
		FrameBuilder.setParameter("size X", 2.0f);
		FrameBuilder.setParameter("size Y", 2.0f);
		FrameBuilder.setParameter("backfacing", true);
		FrameBuilder.setParameter("plane", PlaneDirections::XY);
		FrameBuilder.Build();

		reflectionEntity = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		reflectionEntityModelC = new ModelComponent(reflectionEntity, reflectionBlendingMaterial, ModelManager::instance()["Frame"]);
		cameraComponent = new CameraComponent(reflectionEntity);
		reflectionEntity->name = QString("POI Reflection Blending Entity");
		//level->getRoot()->AttachSubobject(reflectionEntity);
	}


	ReflectionProbeManager::~ReflectionProbeManager()
	{
	}

	RenderTexture* ReflectionProbeManager::getTexture()
	{
		return &reflectionTexture;
	}

	void ReflectionProbeManager::addRefectionProbe(ReflectionProbeComponent* reflectionProbe)
	{
		reflectionProbes.insert(reflectionProbe);
	}

	void ReflectionProbeManager::removeReflectionProbe(ReflectionProbeComponent* reflectionProbe)
	{
		reflectionProbes.remove(reflectionProbe);
	}

	QList<ReflectionProbeComponent*> ReflectionProbeManager::Reevaluate(glm::vec3 position, bool render)
	{
		// TODO: figure out how to handle situation with less than 3 probes or situation without any probes.

		QMap<float, ReflectionProbeComponent*> top3influences;
		int count = 0;
		for (ReflectionProbeComponent* i : reflectionProbes)
		{
			float influence = i->getInfluence(position);
			top3influences[influence] = i;
			if (top3influences.count() > 3)
			{
				top3influences.remove(top3influences.firstKey());
			}
			
		}

		int i = 0;
		for (float key : top3influences.keys())
		{
			if (key <= 0.0f)	continue;

			//QString paramName = QString("mat_reflectionProbes[" + QString::number(i) + "]");
			(*reflectionBlendingMaterial)["mat_RPtex" + QString::number(i)] = top3influences[key]->getTexture();
			str[i] = key;
			(*reflectionBlendingMaterial)["mat_RPstr" + QString::number(i)] = &(str[i]);

			i++;
		}

		for (int j = i; j < 3; j++)
		{
			//QString paramName = QString("mat_reflectionProbes[" + QString::number(j) + "]");
			str[j] = 0.0f;
			(*reflectionBlendingMaterial)["mat_RPstr" + QString::number(j)] = &(str[j]);
		}

		if (render)
		{
			// TODO: Make it cleaner (Camera, shader pass?)

			reflectionTexture.BindFramebuffer();
			reflectionEntityModelC->Draw(cameraComponent, "ReflectionPOI");
			RenderTexture::BindDefaultFramebuffer();
		}

		return top3influences.values();
	}

}