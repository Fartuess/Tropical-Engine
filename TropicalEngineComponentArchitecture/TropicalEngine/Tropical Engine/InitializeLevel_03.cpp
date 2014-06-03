#include "Level.h"
#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "Entity.h"
#include "SceneManager.h"
#include "OglDevTut03.h"

void OglDevTut03::InitializeLevel()
{
	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Shader* simpleShader = new Shader("../Tropical Engine/BasicVertexShader.glsl", "../Tropical Engine/UnlitSimple.glsl", "PhongBlinnSimple");
	Material* simpleMaterial = new Material(simpleShader, nullptr, "Simple Material");

	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	planeObject->AttachComponent(new ModelComponent(planeObject, simpleMaterial, ModelBuilder::Instance().CreatePlane("Plane")));
	planeObject->name = new QString("Plane Object");

	level->root.AttachSubobject(planeObject);
	
	Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.1f, 1.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 4.0f / 3.0f, 0.01f, 10000.0f);
	mainCamera->AttachComponent(mainCameraComponent);
	mainCamera->name = new QString("Main Camera");

	level->root.AttachSubobject(mainCamera);
	SceneManager::Instance().setCurrentCamera(mainCameraComponent);

	foreach(Entity* object, level->root.subobjects)
	{
		if(object->name != nullptr)
		{
			qDebug(object->name->toLatin1());
		}
	}
}