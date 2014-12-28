#include "Scene/Entity.h"
#include "Scene\Level.h"
#include "Scene\SceneManager.h"

SceneManager::SceneManager(void)
{
}

SceneManager::~SceneManager(void)
{
	///TODO: implement it.
}

CameraComponent* SceneManager::getCurrentCamera()
{
	return currentCamera;
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
}

void SceneManager::EvaluateLevels()
{
	foreach(Level* level, levels)
	{
		level->root.transform.Evaluate();
	}
}