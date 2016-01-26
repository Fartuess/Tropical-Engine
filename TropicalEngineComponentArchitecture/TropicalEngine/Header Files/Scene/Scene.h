#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

namespace TropicalEngine
{

	class Scene
	{
	public:
		class DirectionalLightComponent* mainLight;

		Scene(void);
		~Scene(void);

		class CameraComponent* getCurrentCamera();
		void setCurrentCamera(class CameraComponent* camera);

		QMap<QString, class Level*>& getLevels();

		void LoadLevel(QString fileUrl);
		void LoadLevel(QString fileUrl, QString name);
		void LoadLevel(class Level* level, QString name);
		void UnloadLevel(QString name);
		void Clear();

		void EvaluateLevels();

	private:
		QMap<QString, class Level*> levels;
		CameraComponent* currentCamera;
	};

}