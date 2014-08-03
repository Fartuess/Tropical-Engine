#include "Level.h"
#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "ModelComponent.h"
#include "ModelManager.h"
#include "CameraComponent.h"
#include "Entity.h"
#include "DirectionalLightComponent.h"
#include "SceneManager.h"
#include "OglDevTut03.h"

#include "TropicalEngineApplication.h"

void OglDevTut03::InitializeLevel()
{
	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, (glm::vec3(0.0f, 1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	
	Shader* simpleShader = new Shader("../Tropical Engine/PerspectiveSimple_VS.glsl", "../Tropical Engine/PerspectivePhong_PS.glsl", "PhongBlinnSimple");
	Material* simpleMaterial = new Material(simpleShader, nullptr, "Simple Material");
	
	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	TropicalEngineApplication::instance()->modelBuilder->CreateBox("Box");
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("Cylinder");
	TropicalEngineApplication::instance()->modelBuilder->CreateCone("Cone");
	TropicalEngineApplication::instance()->modelBuilder->CreateSphere("Sphere");
	TropicalEngineApplication::instance()->modelBuilder->CreateTorus("Torus");

	planeObject->AttachComponent(new ModelComponent(planeObject, simpleMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Cone")));
	planeObject->name = new QString("TestObject");
	
	level->root.AttachSubobject(planeObject);
	
	Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	mainCamera->AttachComponent(mainCameraComponent);
	mainCamera->name = new QString("Main Camera");
	
	level->root.AttachSubobject(mainCamera);
	TropicalEngineApplication::instance()->sceneManager->LoadLevel(level, "TestLevel");
	TropicalEngineApplication::instance()->sceneManager->setCurrentCamera(mainCameraComponent);
	TropicalEngineApplication::instance()->sceneManager->mainLight = new DirectionalLightComponent(&level->root, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.2, 1.0));
	
	foreach(Entity* object, level->root.subobjects)
	{
		if(object->name != nullptr)
		{
			qDebug(object->name->toLatin1());
		}
	}
}