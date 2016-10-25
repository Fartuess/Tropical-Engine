#pragma once

#include <glm.hpp>

#include <QtCore/qset.h>
#include <QtCore/qlist.h>

#include <Texture/RenderTexture.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	class ReflectionProbeManager : public Singleton<ReflectionProbeManager>
	{
	public:
		friend class ReflectionProbeComponent;

		ReflectionProbeManager();
		~ReflectionProbeManager();

		QList<class ReflectionProbeComponent*> Reevaluate(glm::vec3 position, bool render = false);

		RenderTexture* getTexture();

	protected:
		void addRefectionProbe(class ReflectionProbeComponent* reflectionProbe);
		void removeReflectionProbe(class ReflectionProbeComponent* reflectionProbe);

	private:
		RenderTexture reflectionTexture;

		QSet<class ReflectionProbeComponent*> reflectionProbes;

		// TODO: Change names.
		class ShaderTechnique* reflectionBlendingTechnique;
		class ShaderTechnique* reflectionBlendingTechnique2;
		class Material* reflectionBlendingMaterial;
		class Entity* reflectionEntity;
		class CameraComponent* cameraComponent;
		class ModelComponent* reflectionEntityModelC;

		float str[3];
	};

}