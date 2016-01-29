#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include "Level.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Scene class is Set of Levels to handle together.
	  */
	#pragma endregion
	class Scene
	{
	public:
		// TODO: Is it still needed?
		#pragma region documentation
		/**
		  * \brief Main directional light in the scene.
		  */
		#pragma endregion
		class DirectionalLightComponent* mainLight;

		#pragma region documentation
		/**
		  * \brief Scene constructor.
		  */
		#pragma endregion
		Scene(void);
		#pragma region documentation
		/**
		  * \brief Scene destructor.
		  */
		#pragma endregion
		~Scene(void);

		#pragma region documentation
		/**
		  * \brief Gets Camera which is currently used to draw the scene.
		  *
		  * @return Camera which is currently used to draw the scene.
		  */
		#pragma endregion
		class CameraComponent* getCurrentCamera();
		#pragma region documentation
		/**
		  * \brief Sets Camera which is currently used to draw the scene.
		  *
		  * @param Camera which will be used to draw the scene.
		  */
		#pragma endregion
		void setCurrentCamera(class CameraComponent* camera);

		#pragma region documentation
		/**
		  * \brief Gets Levels which this Scene is made of.
		  *
		  * @return Levels which this Scene is made of.
		  */
		#pragma endregion
		QMap<QString, Level*>& getLevels();

		#pragma region documentation
		/**
		  * \brief Loads level from a file.
		  *
		  * @param fileUrl Path to Level file.
		  */
		#pragma endregion
		void LoadLevel(QString fileUrl);
		#pragma region documentation
		/**
		  * \brief Loads level from a file.
		  *
		  * @param fileUrl Path to Level file.
		  * @param name Name for a Level.
		  */
		#pragma endregion
		void LoadLevel(QString fileUrl, QString name);
		// TODO: Remove name element?
		#pragma region documentation
		/**
		  * \brief Loads existing Level into the Scene.
		  *
		  * @param Level object to load into Scene.
		  * @param name TO DELETE?
		  */
		#pragma endregion
		void LoadLevel(Level* level, QString name);
		#pragma region documentation
		/**
		  * \brief Unloads Level from Scene.
		  *
		  * @param name Name of Level to Unload.
		  */
		#pragma endregion
		void UnloadLevel(QString name);
		#pragma region documentation
		/**
		  * \brief Unloads all Levels from the Scene.
		  */
		#pragma endregion
		void Clear();

		void EvaluateLevels();

	private:
		QMap<QString, Level*> levels;
		CameraComponent* currentCamera;
	};

}