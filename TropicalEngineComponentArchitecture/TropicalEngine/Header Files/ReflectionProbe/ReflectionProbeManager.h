#pragma once

#include <glm.hpp>

#include <QtCore/qset.h>
#include <QtCore/qlist.h>

#include <Texture/RenderTexture.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for Managing Reflection Probes
	  */
	#pragma endregion
	class ReflectionProbeManager : public Singleton<ReflectionProbeManager>
	{
	public:
		friend class ReflectionProbeComponent;

		#pragma region documentation
		/**
		  * \brief ReflectionProbeManager constructor.
		  */
		#pragma endregion
		ReflectionProbeManager();
		#pragma region documentation
		/**
		  * \brief ReflectionProbeManager destructor.
		  */
		#pragma endregion
		~ReflectionProbeManager();

		#pragma region documentation
		/*
		 * \brief Gets 3 most influential reflection probes for given worldspace position and optionally refreshes light information incoming to camera at that position.
		 *
		 * @param position World space position.
		 * @param render Information if blended cubemap should be refreshed.
		 *
		 * @return 3 most influential reflection probes.
		 */
		#pragma endregion
		QList<class ReflectionProbeComponent*> Reevaluate(glm::vec3 position, bool render = false);

		#pragma region documentation
		/**
		  * \brief Gets blended reflection texture.
		  *
		  * @return Blendedr reflection texture.
		  */
		#pragma endregion
		RenderTexture* getTexture();

	protected:
		#pragma region documentation
		/**
		  * \brief Adds ReflectionProbeComponent to the manager.
		  *
		  * @param reflectionProbe Pointer to ReflectionProbeComponent to add.
		  */
		#pragma endregion
		void addRefectionProbe(class ReflectionProbeComponent* reflectionProbe);
		#pragma region documentation
		/**
		  * \brief Removes ReflectionProbeComponent from the manager.
		  *
		  * @param reglefctionProbe Pointer to ReflectionProbeComponent to remove.
		  */
		#pragma endregion
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