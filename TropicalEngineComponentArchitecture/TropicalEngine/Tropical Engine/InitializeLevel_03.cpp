#include "Level.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
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

//#include<QtCore\qdebug.h>
//#include <QtGui\qimagereader.h>

void OglDevTut03::InitializeLevel()
{
	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, (glm::vec3(0.0f, 1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	
	//Shader* simpleShader = new Shader("../Tropical Engine/PerspectiveSimple_VS.glsl", "../Tropical Engine/PerspectivePhong_PS.glsl", "PhongBlinnSimple");
	//Material* simpleMaterial = new Material(simpleShader, nullptr, "Simple Material");
	
	//Shader* testShader = new Shader("../Tropical Engine/NormTexcoord_VS.glsl", "../Tropical Engine/TexturedPhong_PS.glsl", "TexturedPhong");
	Shader* testShaderNRM = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/PhongBlinnBump_PS.glsl", "BumpedPhong");
	//Material* testMaterial = new Material(testShader, nullptr, "Textured Material");
	Material* testMaterialNRM = new Material(testShaderNRM, nullptr, "Bumped Material");
	Texture* testingTexture = new Texture("../Assets/Core/DefaultTexture.png");
	Texture* testingTextureNormal = new Texture("../Assets/Core/DefaultTexture_NRM.png");
	//testMaterial->SetParameter("mat_diffuseTexture", testingTexture);

	testMaterialNRM->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_normalTexture", testingTextureNormal);

	QMap<QString, GLuint> tessalationSubshaders = QMap<QString, GLuint>();
	tessalationSubshaders["../Tropical Engine/Perspective_NTBTcTess_VS.glsl"] = GL_VERTEX_SHADER;
	tessalationSubshaders["../Tropical Engine/SimpleTessalation_TCS.glsl"] = GL_TESS_CONTROL_SHADER;
	tessalationSubshaders["../Tropical Engine/VDisplacement_TES.glsl"] = GL_TESS_EVALUATION_SHADER;
	tessalationSubshaders["../Tropical Engine/PhongBlinnBump_PS.glsl"] = GL_FRAGMENT_SHADER;
	Shader* tessalationShader = new Shader(tessalationSubshaders, "TessalationTest");
	Material* testTessalationMaterial = new Material(tessalationShader, nullptr, "TessalationMat");

	Texture* tessDiffTex = new Texture("../Assets/Core/wall_base.png");
	Texture* tessNrmTex = new Texture("../Assets/Core/wall_normals.png");
	Texture* tessDispTex = new Texture("../Assets/Core/wall_heights.png");
	float tessDispScale = 1.0f;
	testTessalationMaterial->SetParameter("mat_diffuseTexture", tessDiffTex);
	testTessalationMaterial->SetParameter("mat_normalTexture", tessNrmTex);
	testTessalationMaterial->SetParameter("mat_displacementTexture", tessDispTex);
	testTessalationMaterial->SetParameter("mat_displacementScale", &tessDispScale);

	
	//qDebug() << QImageReader::supportedImageFormats();

	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	TropicalEngineApplication::instance()->modelBuilder->CreateBox("Box");
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("Cylinder");
	TropicalEngineApplication::instance()->modelBuilder->CreateCone("Cone");
	TropicalEngineApplication::instance()->modelBuilder->CreateSphere("Sphere");
	TropicalEngineApplication::instance()->modelBuilder->CreateTorus("Torus");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestModel", "../Assets/TestAssets/TestModel.obj");

	planeObject->AttachComponent(new ModelComponent(planeObject, testMaterialNRM, TropicalEngineApplication::instance()->modelManager->getModel("TestModel")));
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