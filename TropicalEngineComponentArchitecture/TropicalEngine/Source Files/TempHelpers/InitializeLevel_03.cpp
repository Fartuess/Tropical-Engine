#include "Scene/Level.h"
#include "Shader/Shader.h"
#include "Shader/Material.h"
#include "Texture/Texture.h"
#include "Model/Model.h"
#include "Model/ModelBuilder.h"
#include "Model/ModelComponent.h"
#include "Model/ModelManager.h"
#include <Model/AssimpModelImporter.h>
#include <Model/FbxModelImporter.h>
#include "Camera/CameraComponent.h"
#include "Scene/Entity.h"
#include "Light/DirectionalLightComponent.h"
#include "Light/PointLightComponent.h"
#include "Scene/SceneManager.h"
#include "TempHelpers/OglDevTut03.h"

#include "TropicalEngineApplication.h"

#include<QtCore/qdebug.h>
//#include <QtGui\qimagereader.h>
#include <QtCore/qjsondocument.h>

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
	Material* straussMaterialMetalic = new Material(straussShader, nullptr, "Strauss Material Metalic");
	Material* wardIsoMaterial = new Material(wardIsoShader, nullptr, "Isotropic Ward Material");
	Material* wardAnisoMaterial = new Material(wardAnisoShader, nullptr, "Anisotropic Ward Material");
	Material* chestMaterial = new Material(testShaderNRM, nullptr, "Steampunk Chest Material");

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

	Texture* chestDiff = new Texture("./Assets/TestAssets/SteampunkChest_Diffuse.tga");
	Texture* chestNRM = new Texture("./Assets/TestAssets/SteampunkChest_NRM.tga");

	phongMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	phongBlinnMaterial->SetParameter("mat_diffuseColor", new glm::vec3(1.0f, 0.7f, 0.0f));
	testMaterial->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_diffuseTexture", testingTexture);
	testMaterialNRM->SetParameter("mat_normalTexture", testingTextureNormal);
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
	straussMaterial->SetParameter("mat_albedo", new glm::vec3(0.0f, 1.0f, 0.0f));
	straussMaterial->SetParameter("mat_roughness", new float(0.8f));	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
	straussMaterial->SetParameter("mat_metaliness", new float(0.0f));
	straussMaterialMetalic->SetParameter("mat_albedo", new glm::vec3(0.0f, 1.0f, 0.0f));
	straussMaterialMetalic->SetParameter("mat_roughness", new float(0.8f));	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
	straussMaterialMetalic->SetParameter("mat_metaliness", new float(1.0f));
	wardIsoMaterial->SetParameter("mat_diffuse", new glm::vec3(1.0f, 0.7f, 0.0f));
	wardIsoMaterial->SetParameter("mat_roughness", new float(0.3f));
	wardAnisoMaterial->SetParameter("mat_diffuse", new glm::vec3(1.0f, 0.7f, 0.0f));
	wardAnisoMaterial->SetParameter("mat_anisoRoughness", new glm::vec2(0.5f, 0.1f));
	chestMaterial->SetParameter("mat_diffuseTexture", chestDiff);
	chestMaterial->SetParameter("mat_normalTexture", chestNRM);
	
	
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
	
	distanceTessalationMaterial->SetParameter("mat_diffuseTexture", tessDiffTex);
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
	vectorTessalationMaterial->SetParameter("mat_tesselationMultiplier", new float(64.0f));
	
	//qDebug() << QImageReader::supportedImageFormats();

	//Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));

	//initialization of assimp model importer
	AssimpModelImporter::Instance();
	FbxModelImporter::Instance();

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
	TropicalEngineApplication::instance()->modelBuilder->Load("FbxTest", "./Assets/TestAssets/FBXtest.fbx");
	TropicalEngineApplication::instance()->modelBuilder->Load("FbxTest2", "./Assets/TestAssets/FBXtest2.fbx");
	TropicalEngineApplication::instance()->modelBuilder->Load("FbxTest3", "./Assets/TestAssets/FBXtestPrepared.fbx");
	TropicalEngineApplication::instance()->modelBuilder->Load("FbxTest4", "./Assets/TestAssets/FBXHierarchyTest.fbx");
	TropicalEngineApplication::instance()->modelBuilder->Load("FbxChest", "./Assets/TestAssets/SteamPunkChest_LP.fbx");

	//Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	////planeObject->AttachComponent(new ModelComponent(planeObject, cookTorranceMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Plane")));
	//ModelComponent* testModelComponent = new ModelComponent(planeObject, vectorTessalationMaterial, TropicalEngineApplication::instance()->modelManager->getModel("VectorCube"));
	//planeObject->AttachComponent(testModelComponent);
	//planeObject->name = QString("TestObject");

	//level->root.AttachSubobject(planeObject);

	Entity* phongExample = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* phongModelC = new ModelComponent(phongExample, phongMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	phongExample->AttachComponent(phongModelC);
	phongExample->name = QString("Phong Example");
	level->root.AttachSubobject(phongExample);

	Entity* phongBlinnExample = new Entity(glm::vec3(4.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* phongBlinnModelC = new ModelComponent(phongBlinnExample, phongBlinnMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	phongBlinnExample->AttachComponent(phongBlinnModelC);
	phongBlinnExample->name = QString("Blinn-Phong Example");
	level->root.AttachSubobject(phongBlinnExample);

	Entity* BumpMapExample = new Entity(glm::vec3(8.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* bumpMapModelC = new ModelComponent(BumpMapExample, testMaterialNRM, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	BumpMapExample->AttachComponent(bumpMapModelC);
	BumpMapExample->name = QString("Bump mapping Example");
	level->root.AttachSubobject(BumpMapExample);

	Entity* MaskedExample = new Entity(glm::vec3(12.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* maskedModelC = new ModelComponent(MaskedExample, maskedMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Box"));
	MaskedExample->AttachComponent(maskedModelC);
	MaskedExample->name = QString("Masked blend mode Example");
	level->root.AttachSubobject(MaskedExample);

	Entity* ParralaxExample = new Entity(glm::vec3(16.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* parralaxModelC = new ModelComponent(ParralaxExample, phongBlinnParalaxMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Teapot"));
	ParralaxExample->AttachComponent(parralaxModelC);
	ParralaxExample->name = QString("Displacement Mapping Example");
	level->root.AttachSubobject(ParralaxExample);

	Entity* CookTorranceExample = new Entity(glm::vec3(20.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* cookTorranceModelC = new ModelComponent(CookTorranceExample, cookTorranceMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	CookTorranceExample->AttachComponent(cookTorranceModelC);
	CookTorranceExample->name = QString("Cook-Torrance Example");
	level->root.AttachSubobject(CookTorranceExample);

	Entity* StraussExample = new Entity(glm::vec3(24.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* straussModelC = new ModelComponent(StraussExample, straussMaterial, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	StraussExample->AttachComponent(straussModelC);
	StraussExample->name = QString("Strauss Example");
	level->root.AttachSubobject(StraussExample);

	Entity* StraussConductiveExample = new Entity(glm::vec3(28.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* straussConductiveModelC = new ModelComponent(StraussConductiveExample, straussMaterialMetalic, TropicalEngineApplication::instance()->modelManager->getModel("Sphere"));
	StraussConductiveExample->AttachComponent(straussConductiveModelC);
	StraussConductiveExample->name = QString("Strauss Metalic Example");
	level->root.AttachSubobject(StraussConductiveExample);

	Entity* WardExample = new Entity(glm::vec3(32.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* wardModelC = new ModelComponent(WardExample, wardIsoMaterial, TropicalEngineApplication::instance()->modelManager->getModel("TestModel2"));
	WardExample->AttachComponent(wardModelC);
	WardExample->name = QString("Ward Example");
	level->root.AttachSubobject(WardExample);

	Entity* WardAnisotropicExample = new Entity(glm::vec3(36.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* wardAnisoModelC = new ModelComponent(WardAnisotropicExample, wardAnisoMaterial, TropicalEngineApplication::instance()->modelManager->getModel("TestModel2"));
	WardAnisotropicExample->AttachComponent(wardAnisoModelC);
	WardAnisotropicExample->name = QString("Ward Anisotropic Example");
	level->root.AttachSubobject(WardAnisotropicExample);

	Entity* DistanceTessellationExample = new Entity(glm::vec3(40.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* distanceTessModelC = new ModelComponent(DistanceTessellationExample, testTessalationMaterial, TropicalEngineApplication::instance()->modelManager->getModel("BoxDense"));
	DistanceTessellationExample->AttachComponent(distanceTessModelC);
	DistanceTessellationExample->name = QString("Distance Tessellation Example");
	level->root.AttachSubobject(DistanceTessellationExample);

	Entity* VectorTessellationExample = new Entity(glm::vec3(44.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* vectorTessModelC = new ModelComponent(VectorTessellationExample, vectorTessalationMaterial, TropicalEngineApplication::instance()->modelManager->getModel("VectorCube"));
	VectorTessellationExample->AttachComponent(vectorTessModelC);
	VectorTessellationExample->name = QString("Vector Displacement Tessellation Example");
	level->root.AttachSubobject(VectorTessellationExample);

	Entity* FbxExample = new Entity(glm::vec3(48.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.2f, 0.2f, 0.2f));
	ModelComponent* FbxExampleModelC = new ModelComponent(FbxExample, chestMaterial, TropicalEngineApplication::instance()->modelManager->getModel("FbxChest"));
	FbxExample->AttachComponent(FbxExampleModelC);
	FbxExample->name = QString("FBX import Example");
	level->root.AttachSubobject(FbxExample);

	Entity* FbxExample2 = new Entity(glm::vec3(52.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* FbxExample2ModelC = new ModelComponent(FbxExample2, phongMaterial, TropicalEngineApplication::instance()->modelManager->getModel("FbxTest2"));
	FbxExample2->AttachComponent(FbxExample2ModelC);
	FbxExample2->name = QString("FBX Example 2");
	level->root.AttachSubobject(FbxExample2);

	Entity* FbxExample3 = new Entity(glm::vec3(60.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* FbxExample3ModelC = new ModelComponent(FbxExample3, phongMaterial, TropicalEngineApplication::instance()->modelManager->getModel("FbxTest4"));
	FbxExample3->AttachComponent(FbxExample3ModelC);
	FbxExample3->name = QString("FBX Hierarchy Example");
	level->root.AttachSubobject(FbxExample3);
	
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

	Entity* pointLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(1.0f, 0.2f, 1.0f), 0.5f, 100.0f, 0.4f);
	pointLight->name = QString("Point Light");
	level->root.AttachSubobject(pointLight);

	//Temporary solution
	phongModelC->lightedBy.append(pointLightComponent);
	phongBlinnModelC->lightedBy.append(pointLightComponent);
	bumpMapModelC->lightedBy.append(pointLightComponent);
	maskedModelC->lightedBy.append(pointLightComponent);
	parralaxModelC->lightedBy.append(pointLightComponent);
	cookTorranceModelC->lightedBy.append(pointLightComponent);
	straussModelC->lightedBy.append(pointLightComponent);
	straussConductiveModelC->lightedBy.append(pointLightComponent);
	wardModelC->lightedBy.append(pointLightComponent);
	wardAnisoModelC->lightedBy.append(pointLightComponent);
	distanceTessModelC->lightedBy.append(pointLightComponent);
	vectorTessModelC->lightedBy.append(pointLightComponent);
	FbxExampleModelC->lightedBy.append(pointLightComponent);

	
	TropicalEngineApplication::instance()->sceneManager->LoadLevel(level, "TestLevel");
	TropicalEngineApplication::instance()->sceneManager->setCurrentCamera(mainCameraComponent);
	TropicalEngineApplication::instance()->sceneManager->mainLight = new DirectionalLightComponent(&level->root, glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.2, 1.0), 1.0f);

	qDebug() << QJsonDocument(level->toJSON()).toJson();
	
}