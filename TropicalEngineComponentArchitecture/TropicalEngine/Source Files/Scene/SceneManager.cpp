#include "Scene/Entity.h"
#include "Scene\Level.h"
#include "Scene\SceneManager.h"
#include "Camera\CameraComponent.h"

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
	///TODO: implement it.
}

CameraComponent* SceneManager::getCurrentCamera()
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

void SceneManager::setCurrentCamera(CameraComponent* camera)
{
	currentCamera = camera;
}

QMap<QString, Level*>& SceneManager::getLevels()
{
	return levels;
}

void SceneManager::LoadLevel(QString fileUrl)
{
	///TODO: implement it.
}

void SceneManager::LoadLevel(QString fileUrl, QString name)
{
	///TODO: implement it.
}

void SceneManager::LoadLevel(Level* level, QString name)
{
	///TODO: implement it.
	levels.insert(name, level);
}

void SceneManager::UnloadLevel(QString name)
{
	///TODO: implement it.
	Level* level = levels.take(name);
	//delete level;
}

void SceneManager::Clear()
{
	QList<Level*> currentLevels = levels.values();
	for (Level* level : currentLevels)
	{
		//delete level;
	}
	levels.clear();
}

void SceneManager::EvaluateLevels()
{
	for (Level* level : levels)
	{
		level->root.transform.Evaluate();
	}
}