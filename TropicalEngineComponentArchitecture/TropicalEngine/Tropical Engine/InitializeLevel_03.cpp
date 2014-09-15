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
#include "PointLightComponent.h"
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
	
	Shader* phongShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/Phong_PS.glsl", "Phong");
	Shader* phongBlinnShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/PhongBlinn_PS.glsl", "BlinnPhong");
	Shader* testShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/PhongBlinnSimple_PS.glsl", "TexturedPhong");
	Shader* testShaderNRM = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/PhongBlinnBump_PS.glsl", "BumpedPhong");
	Shader* phongBlinnParalaxShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/PhongBlinnParalax_PS.glsl", "ParalaxedPhong");
	Shader* cookTorranceShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/CookTorrance_PS.glsl", "CookTorrance");
	Shader* straussShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/StraussSimple2_PS.glsl", "Strauss");
	Shader* wardIsoShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/WardIsoSimple_PS.glsl", "WardIso");
	Shader* wardAnisoShader = new Shader("../Tropical Engine/Perspective_NTBTc_VS.glsl", "../Tropical Engine/WardAnisoSimple_PS.glsl", "WardAniso");
	Material* phongMaterial = new Material(phongShader, nullptr, "Phong Material");
	Material* phongBlinnMaterial = new Material(phongBlinnShader, nullptr, "Blinn-Phong Material");
	Material* testMaterial = new Material(testShader, nullptr, "Textured Material");
	Material* testMaterialNRM = new Material(testShaderNRM, nullptr, "Bumped Material");
	Material* phongBlinnParalaxMaterial = new Material(phongBlinnParalaxShader, nullptr, "Paralaxed Material");
	Material* cookTorranceMaterial = new Material(cookTorranceShader, nullptr, "CookTorrance Material");
	Material* straussMaterial = new Material(straussShader, nullptr, "Strauss Material");
	Material* wardIsoMaterial = new Material(wardIsoShader, nullptr, "Isotropic Ward Material");
	Material* wardAnisoMaterial = new Material(wardAnisoShader, nullptr, "Anisotropic Ward Material");

	Texture* testingTexture = new Texture("../Assets/Core/DefaultTexture.png");
	Texture* testingTextureNormal = new Texture("../Assets/Core/DefaultTexture_NRM.png");

	Texture* tessDiffTex = new Texture("../Assets/Core/wall_base.png");
	Texture* tessNrmTex = new Texture("../Assets/Core/wall_normals.png");
	Texture* tessDispTex = new Texture("../Assets/Core/wall_heights.png");

	//phongMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	phongBlinnMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	testMaterial->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_normalTexture", tessNrmTex);
	phongBlinnParalaxMaterial->SetParameter("mat_diffuseTexture", tessDiffTex);
	phongBlinnParalaxMaterial->SetParameter("mat_normalTexture", tessNrmTex);
	phongBlinnParalaxMaterial->SetParameter("mat_heightTexture", tessDispTex);
	float* bumpScale = new float(0.1f);
	phongBlinnParalaxMaterial->SetParameter("mat_bumpScale", bumpScale);
	cookTorranceMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	cookTorranceMaterial->SetParameter("mat_specularColor", new glm::vec3(1.0f, 1.0f, 1.0f));
	float* roughness = new float(0.5f);
	cookTorranceMaterial->SetParameter("mat_roughness", roughness);
	float* refractiveIndex = new float(0.15f);
	cookTorranceMaterial->SetParameter("mat_refractiveIndex", refractiveIndex);
	straussMaterial->SetParameter("mat_albedo", new glm::vec3(1.0f, 0.7f, 0.0f));
	straussMaterial->SetParameter("mat_roughness", new float(0.8f));	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
	straussMaterial->SetParameter("mat_metaliness", new float(0.0f));		//comment to make it metal
	//straussMaterial->SetParameter("mat_metaliness", new float(1.0f));		//uncomment to make it metal
	wardIsoMaterial->SetParameter("mat_diffuse", new glm::vec3(1.0f, 0.7f, 0.0f));
	wardIsoMaterial->SetParameter("mat_roughness", new float(0.5f));
	wardAnisoMaterial->SetParameter("mat_diffuse", new glm::vec3(1.0f, 0.7f, 0.0f));
	wardAnisoMaterial->SetParameter("mat_anisoRoughness", new glm::vec2(0.1f, 0.5f));


	QMap<QString, GLuint> tessalationSubshaders = QMap<QString, GLuint>();
	tessalationSubshaders["../Tropical Engine/Perspective_NTBTcTess_VS.glsl"] = GL_VERTEX_SHADER;
	tessalationSubshaders["../Tropical Engine/SimpleTessalation_TCS.glsl"] = GL_TESS_CONTROL_SHADER;
	tessalationSubshaders["../Tropical Engine/VDisplacement_TES.glsl"] = GL_TESS_EVALUATION_SHADER;
	tessalationSubshaders["../Tropical Engine/PhongBlinnBump_PS.glsl"] = GL_FRAGMENT_SHADER;
	Shader* tessalationShader = new Shader(tessalationSubshaders, "TessalationTest");
	tessalationShader->drawingMode = GL_PATCHES;
	Material* testTessalationMaterial = new Material(tessalationShader, nullptr, "TessalationMat");

	//float tessDispScale = 1.0f;
	testTessalationMaterial->SetParameter("mat_diffuseTexture", tessDiffTex);
	testTessalationMaterial->SetParameter("mat_normalTexture", tessNrmTex);
	testTessalationMaterial->SetParameter("mat_displacementTexture", tessDispTex);
	testTessalationMaterial->SetParameter("mat_displacementScale", new float(0.1f));

	
	//qDebug() << QImageReader::supportedImageFormats();

	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	TropicalEngineApplication::instance()->modelBuilder->CreatePlane("Plane", 10.0f, 10.0f, 50, 50);
	TropicalEngineApplication::instance()->modelBuilder->CreateBox("Box");
	TropicalEngineApplication::instance()->modelBuilder->CreateBox("BoxDense",glm::vec3(1.0f),glm::vec3(10,10,10));
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("Cylinder");
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("CylinderDense", 1.0f, 2.0f, 40, 10);
	TropicalEngineApplication::instance()->modelBuilder->CreateCone("Cone");
	TropicalEngineApplication::instance()->modelBuilder->CreateSphere("Sphere", 1.0f, 40, 40);
	TropicalEngineApplication::instance()->modelBuilder->CreateTorus("Torus");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestModel", "../Assets/TestAssets/TestModel.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestModel2", "../Assets/TestAssets/TestModel2.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("Teapot", "../Assets/TestAssets/teapot.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("MayaBox", "../Assets/TestAssets/MayaBox.obj");

	//planeObject->AttachComponent(new ModelComponent(planeObject, cookTorranceMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Plane")));
	ModelComponent* testModelComponent = new ModelComponent(planeObject, phongMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	planeObject->AttachComponent(testModelComponent);
	planeObject->name = new QString("TestObject");
	
	level->root.AttachSubobject(planeObject);
	
	Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	mainCamera->AttachComponent(mainCameraComponent);
	mainCamera->name = new QString("Main Camera");
	level->root.AttachSubobject(mainCamera);

	Entity* lightModelTestingCamera = new Entity(glm::vec3(5.0f, 2.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* lightModelTestingCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	lightModelTestingCamera->AttachComponent(lightModelTestingCameraComponent);
	lightModelTestingCamera->name = new QString("Light Model Testing Camera");
	level->root.AttachSubobject(lightModelTestingCamera);

	Entity* pointLight = new Entity(glm::vec3(-5.0f, 2.0f, -5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(0.8f, 0.0f, 0.0f), 1.0f, 10.0f, 0.4f);
	pointLight->name = new QString("Point Light");
	testModelComponent->lightedBy.append(pointLightComponent);
	level->root.AttachSubobject(pointLight);
	
	TropicalEngineApplication::instance()->sceneManager->LoadLevel(level, "TestLevel");
	TropicalEngineApplication::instance()->sceneManager->setCurrentCamera(mainCameraComponent);
	TropicalEngineApplication::instance()->sceneManager->mainLight = new DirectionalLightComponent(&level->root, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.2, 1.0));
}