#pragma once
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Level;
class CameraComponent;
class DirectionalLightComponent;

class SceneManager
{
private:
	QMap<QString, Level*> levels;
	CameraComponent* currentCamera;
public:
	DirectionalLightComponent* mainLight;

	SceneManager(void);
	~SceneManager(void);

	CameraComponent* getCurrentCamera();
	void setCurrentCamera(CameraComponent* camera);

	void LoadLevel(QString fileUrl);
	void LoadLevel(QString fileUrl, QString name);
	void LoadLevel(Level* level, QString name);
	void UnloadLevel(QString name);

	void EvaluateLevels();
};