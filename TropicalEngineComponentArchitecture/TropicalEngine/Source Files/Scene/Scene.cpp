#include <Scene/Entity.h>
#include <Scene/Level.h>
#include <Scene/Scene.h>
#include <Scene/SceneManager.h>

#include <Camera/CameraComponent.h>

#include <TropicalEngineApplication.h>

namespace TropicalEngine
{

	Scene::Scene(void)
	{
		TropicalEngineApplication::instance()->sceneManager->scenes.insert(this);
	}

	Scene::~Scene(void)
	{
		///TODO: implement it.
	}

	CameraComponent* Scene::getCurrentCamera()
	{
		if (currentCamera != nullptr)
		{
			return currentCamera;
		}
		else
		{
			///TODO: figure out what to handle situation where there is no camera in level.
			Entity* tempCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
			currentCamera = new CameraComponent(tempCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
			return currentCamera;
		}
	}

	void Scene::setCurrentCamera(CameraComponent* camera)
	{
		currentCamera = camera;
	}

	QMap<QString, Level*>& Scene::getLevels()
	{
		return levels;
	}

	void Scene::LoadLevel(QString fileUrl)
	{
		///TODO: implement it.
		//Check in Level Manager if said level is already loaded.
	}

	void Scene::LoadLevel(QString fileUrl, QString name)
	{
		///TODO: implement it.
	}

	void Scene::LoadLevel(Level* level, QString name)
	{
		///TODO: implement it.
		levels.insert(name, level);
	}

	void Scene::UnloadLevel(QString name)
	{
		///TODO: implement it.
		Level* level = levels.take(name);
		//delete level;
	}

	void Scene::Clear()
	{
		QList<Level*> currentLevels = levels.values();
		for (Level* level : currentLevels)
		{
			//delete level;
		}
		levels.clear();
	}

	void Scene::EvaluateLevels()
	{
		for (Level* level : levels)
		{
			level->getRoot()->transform.Evaluate();
		}
	}

}