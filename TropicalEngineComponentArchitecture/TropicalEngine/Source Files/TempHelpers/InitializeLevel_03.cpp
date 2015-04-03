#include "Scene\Level.h"
#include "Shader\Shader.h"
#include "Shader\Material.h"
#include "Texture\Texture.h"
#include "Model\Model.h"
#include "Model\ModelBuilder.h"
#include "Model\ModelComponent.h"
#include "Model\ModelManager.h"
#include "Camera/CameraComponent.h"
#include "Scene/Entity.h"
#include "Light/DirectionalLightComponent.h"
#include "Light\PointLightComponent.h"
#include "Scene\SceneManager.h"
#include "TempHelpers\OglDevTut03.h"

#include "TropicalEngineApplication.h"

#include<QtCore\qdebug.h>
//#include <QtGui\qimagereader.h>
#include <QtCore\qjsondocument.h>

void OglDevTut03::InitializeLevel()
{
	
	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, (glm::vec3(0.0f, 1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	
	//Shader* simpleShader = new Shader("../Tropical Engine/PerspectiveSimple_VS.glsl", "../Tropical Engine/PerspectivePhong_PS.glsl", "PhongBlinnSimple");
	//Material* simpleMaterial = new Material(simpleShader, nullptr, "Simple Material");
	
	Shader* phongShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/Phong_PS.glsl", "Phong");
	Shader* phongBlinnShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinn_PS.glsl", "BlinnPhong");
	Shader* testShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnSimple_PS.glsl", "TexturedPhong");
	Shader* testShaderNRM = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnBump_PS.glsl", "BumpedPhong");
	Shader* maskedShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnBumpMask_PS.glsl", "MaskedBumpedBlinnPhong");
	Shader* phongBlinnParalaxShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnParalax_PS.glsl", "ParalaxedPhong");
	Shader* cookTorranceShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/CookTorrance_PS.glsl", "CookTorrance");
	Shader* straussShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/StraussSimple2_PS.glsl", "Strauss");
	Shader* wardIsoShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/WardIsoSimple_PS.glsl", "WardIso");
	Shader* wardAnisoShader = new Shader("./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/WardAnisoSimple_PS.glsl", "WardAniso");
	Material* phongMaterial = new Material(phongShader, nullptr, "Phong Material");
	Material* phongBlinnMaterial = new Material(phongBlinnShader, nullptr, "Blinn-Phong Material");
	Material* testMaterial = new Material(testShader, nullptr, "Textured Material");
	Material* testMaterialNRM = new Material(testShaderNRM, nullptr, "Bumped Material");
	Material* maskedMaterial = new Material(maskedShader, nullptr, "Masked Material");
	Material* phongBlinnParalaxMaterial = new Material(phongBlinnParalaxShader, nullptr, "Paralaxed Material");
	Material* cookTorranceMaterial = new Material(cookTorranceShader, nullptr, "CookTorrance Material");
	Material* straussMaterial = new Material(straussShader, nullptr, "Strauss Material");
	Material* wardIsoMaterial = new Material(wardIsoShader, nullptr, "Isotropic Ward Material");
	Material* wardAnisoMaterial = new Material(wardAnisoShader, nullptr, "Anisotropic Ward Material");

	Texture* testingTexture = new Texture("./Assets/Core/DefaultTexture.png");
	Texture* testingTextureNormal = new Texture("./Assets/Core/DefaultTexture_NRM.png");

	Texture* testGearTexture = new Texture("./Assets/TestAssets/Gear_occlusion.tga");
	Texture* testGearTextureNormal = new Texture("./Assets/TestAssets/Gear_normals.tga");

	Texture* tessDiffTex = new Texture("./Assets/Core/wall_base.png");
	Texture* tessNrmTex = new Texture("./Assets/Core/wall_normals.png");
	Texture* tessDispTex = new Texture("./Assets/Core/wall_heights.png");

	//Texture* tessVecDispTex = new Texture("../Assets/TestAssets/vectorEar.png");

	Texture* tessVecDispTex = new Texture("./Assets/TestAssets/vectorCube_occlusion.tga");
	Texture* tessVecDispTexNRM = new Texture("./Assets/TestAssets/vectorCube_normals.tga");
	Texture* tessVecDispTexDISP = new Texture("./Assets/TestAssets/vectorCube_directions.tga");
	Texture* tessVecDispTexDISP_TS = new Texture("./Assets/TestAssets/vectorCube_2_directions.tga");

	Texture* tgaTest = new Texture("./Assets/TestAssets/dickbutt.tga");
	Texture* tgaRleTest = new Texture("./Assets/TestAssets/dickbutt_RLE.tga");	//apparently Qt TGA importer doesn't read TGA compressed with RLE.

	phongMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	phongBlinnMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	testMaterial->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_normalTexture", tessNrmTex);
	maskedMaterial->SetParameter("mat_diffuseTexture", testGearTexture);
	maskedMaterial->SetParameter("mat_normalTexture", testGearTextureNormal);
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
	wardIsoMaterial->SetParameter("mat_roughness", new float(0.3f));
	wardAnisoMaterial->SetParameter("mat_diffuse", new glm::vec3(1.0f, 0.7f, 0.0f));
	wardAnisoMaterial->SetParameter("mat_anisoRoughness", new glm::vec2(0.5f, 0.1f));
	
	
	QMap<QString, GLuint> tessalationSubshaders = QMap<QString, GLuint>();
	tessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"] = GL_VERTEX_SHADER;
	tessalationSubshaders["./Shader Files/SimpleTessalation_TCS.glsl"] = GL_TESS_CONTROL_SHADER;
	tessalationSubshaders["./Shader Files/Displacement_TES.glsl"] = GL_TESS_EVALUATION_SHADER;
	tessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"] = GL_FRAGMENT_SHADER;
	Shader* tessalationShader = new Shader(tessalationSubshaders, "TessalationTest");
	tessalationShader->drawingMode = GL_PATCHES;
	Material* testTessalationMaterial = new Material(tessalationShader, nullptr, "TessalationMat");
	
	//float tessDispScale = 1.0f;
	testTessalationMaterial->SetParameter("mat_diffuseTexture", tessDiffTex);
	testTessalationMaterial->SetParameter("mat_normalTexture", tessNrmTex);
	testTessalationMaterial->SetParameter("mat_displacementTexture", tessDispTex);
	testTessalationMaterial->SetParameter("mat_displacementScale", new float(0.1f));
	
	QMap<QString, GLuint> distanceTessalationSubshaders = QMap<QString, GLuint>();
	distanceTessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"] = GL_VERTEX_SHADER;
	distanceTessalationSubshaders["./Shader Files/DistanceBasedTesselation_TCS.glsl"] = GL_TESS_CONTROL_SHADER;
	distanceTessalationSubshaders["./Shader Files/Displacement_TES.glsl"] = GL_TESS_EVALUATION_SHADER;
	distanceTessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"] = GL_FRAGMENT_SHADER;
	
	Shader* distanceTessalationShader = new Shader(distanceTessalationSubshaders, "DistanceTessalationTest");
	distanceTessalationShader->drawingMode = GL_PATCHES;
	Material* distanceTessalationMaterial = new Material(distanceTessalationShader, nullptr, "DistanceTessalationMat");
	
	distanceTessalationMaterial->SetParameter("mat_diffuseTexture", tgaTest);
	distanceTessalationMaterial->SetParameter("mat_normalTexture", tessNrmTex);
	distanceTessalationMaterial->SetParameter("mat_displacementTexture", tessDispTex);
	distanceTessalationMaterial->SetParameter("mat_displacementScale", new float(0.1f));
	
	QMap<QString, GLuint> vectorTessalationSubshaders = QMap<QString, GLuint>();
	vectorTessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"] = GL_VERTEX_SHADER;
	vectorTessalationSubshaders["./Shader Files/DistanceBasedTesselation_TCS.glsl"] = GL_TESS_CONTROL_SHADER;
	vectorTessalationSubshaders["./Shader Files/VectorDisplacement_TES.glsl"] = GL_TESS_EVALUATION_SHADER;
	vectorTessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"] = GL_FRAGMENT_SHADER;
	
	Shader* vectorTessalationShader = new Shader(vectorTessalationSubshaders, "VectorTessalationTest");
	vectorTessalationShader->drawingMode = GL_PATCHES;
	Material* vectorTessalationMaterial = new Material(vectorTessalationShader, nullptr, "VectorTessalationMat");
	
	vectorTessalationMaterial->SetParameter("mat_diffuseTexture", tessVecDispTex);
	vectorTessalationMaterial->SetParameter("mat_normalTexture", tessVecDispTexNRM);
	vectorTessalationMaterial->SetParameter("mat_displacementTexture", tessVecDispTexDISP_TS);
	vectorTessalationMaterial->SetParameter("mat_displacementScale", new float(0.5f));
	vectorTessalationMaterial->SetParameter("mat_tesselationMultiplier", new float(128.0f));
	
	//qDebug() << QImageReader::supportedImageFormats();

	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	TropicalEngineApplication::instance()->modelBuilder->CreatePlane("Plane", 10.0f, 10.0f, 50, 50);
	TropicalEngineApplication::instance()->modelBuilder->CreateBox("Box", glm::vec3(1.0f, 1.0f, 1.0f));
	TropicalEngineApplication::instance()->modelBuilder->CreateBox("BoxDense",glm::vec3(1.0f),glm::vec3(10,10,10));
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("Cylinder");
	TropicalEngineApplication::instance()->modelBuilder->CreateCylinder("CylinderDense", 1.0f, 2.0f, 40, 10);
	TropicalEngineApplication::instance()->modelBuilder->CreateCone("Cone");
	TropicalEngineApplication::instance()->modelBuilder->CreateSphere("Sphere", 1.0f, 40, 40);
	TropicalEngineApplication::instance()->modelBuilder->CreateTorus("Torus");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestModel", "./Assets/TestAssets/TestModel.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestModel2", "./Assets/TestAssets/TestModel2.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("TestTesselation", "./Assets/TestAssets/TestTesselation.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("Teapot", "./Assets/TestAssets/teapot.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("MayaBox", "./Assets/TestAssets/MayaBox.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("VectorSphere", "./Assets/TestAssets/vectorDispSphere.obj");
	TropicalEngineApplication::instance()->modelBuilder->Load("VectorCube", "./Assets/TestAssets/vectorCube_LP_DENSE_T.obj");

	//planeObject->AttachComponent(new ModelComponent(planeObject, cookTorranceMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Plane")));
	ModelComponent* testModelComponent = new ModelComponent(planeObject, vectorTessalationMaterial, TropicalEngineApplication::instance()->modelManager->getModel("VectorCube"));
	planeObject->AttachComponent(testModelComponent);
	planeObject->name = QString("TestObject");
	
	level->root.AttachSubobject(planeObject);
	
	Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	mainCamera->AttachComponent(mainCameraComponent);
	mainCamera->name = QString("Main Camera");
	level->root.AttachSubobject(mainCamera);

	Entity* lightModelTestingCamera = new Entity(glm::vec3(5.0f, 5.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* lightModelTestingCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	lightModelTestingCamera->AttachComponent(lightModelTestingCameraComponent);
	lightModelTestingCamera->name = QString("Light Model Testing Camera");
	level->root.AttachSubobject(lightModelTestingCamera);

	Entity* pointLight = new Entity(glm::vec3(-5.0f, 5.0f, -5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 1000.0f, 0.4f);
	pointLight->name = QString("Point Light");
	testModelComponent->lightedBy.append(pointLightComponent);
	level->root.AttachSubobject(pointLight);
	
	TropicalEngineApplication::instance()->sceneManager->LoadLevel(level, "TestLevel");
	TropicalEngineApplication::instance()->sceneManager->setCurrentCamera(mainCameraComponent);
	TropicalEngineApplication::instance()->sceneManager->mainLight = new DirectionalLightComponent(&level->root, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.2, 1.0), 1.0f);

	qDebug() << QJsonDocument(level->toJSON()).toJson();
	
}