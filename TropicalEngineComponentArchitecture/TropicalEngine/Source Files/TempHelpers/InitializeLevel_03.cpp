#include <QtCore/qdebug.h>
#include <QtCore/qjsondocument.h>

#include <Scene/Level.h>

#include <Shader/Shader.h>
#include <Shader/ShaderManager.h>
#include <Shader/Material.h>
#include <Shader/MaterialManager.h>

#include <Texture/Texture.h>
#include <Texture/TextureManager.h>

#include <Model/Model.h>
#include <Model/ModelBuilder.h>
#include <Model/ModelComponent.h>
#include <Model/ModelManager.h>
#include <Model/AssimpModelImporter.h>
#include <Model/FbxModelImporter.h>

#include <Camera/CameraComponent.h>

#include <Scene/Entity.h>

#include <Light/DirectionalLightComponent.h>
#include <Light/PointLightComponent.h>

#include <Scene/SceneManager.h>

#include <Package/Asset.h>
#include <Package/AssetManager.h>
#include <Package/PackageManager.h>

#include <TempHelpers/OglDevTut03.h>

#include "TropicalEngineApplication.h"

void OglDevTut03::InitializeLevel()
{

	TropicalEngineApplication* engine = TropicalEngineApplication::instance();
	
	/*********************************
	 *
	 * Creating empty level
	 *
	 *********************************/

	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, (glm::vec3(0.0f, 1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	level->name = "TestLevel";
	
	AssetManager& assetManager = *engine->assetManager;
	PackageManager& packageManager = *engine->packageManager;
	Asset* helperAsset;

	/*********************************
	*
	* Creating shaders
	*
	*********************************/

	ShaderManager& shaderManager	=	*engine->shaderManager;

										shaderManager.Load("Phong",					"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/Phong_PS.glsl");
										shaderManager.Load("BlinnPhong",			"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinn_PS.glsl");
	Shader* testShader				=	shaderManager.Load("TexturedPhong",			"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnSimple_PS.glsl");
	Shader* testShaderNRM			=	shaderManager.Load("BumpedPhong",			"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnBump_PS.glsl");
	Shader* maskedShader			=	shaderManager.Load("MaskedBumpedBlinnPhong","./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnBumpMask_PS.glsl");
	Shader* phongBlinnParalaxShader	=	shaderManager.Load("ParalaxedPhong",		"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnParalax_PS.glsl");
	Shader* cookTorranceShader		=	shaderManager.Load("CookTorrance",			"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/CookTorrance_PS.glsl");
	Shader* straussShader			=	shaderManager.Load("Strauss",				"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/StraussSimple2_PS.glsl");
	Shader* wardIsoShader			=	shaderManager.Load("WardIso",				"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/WardIsoSimple_PS.glsl");
	Shader* wardAnisoShader			=	shaderManager.Load("WardAniso",				"./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/WardAnisoSimple_PS.glsl");

	//Adding shaders to the internal package of the level.
	helperAsset = new Asset("Phong Shader", shaderManager["Phong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("BlinnPhong Shader", shaderManager["BlinnPhong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("TexturedPhong Shader", shaderManager["TexturedPhong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("BumpedPhong Shader", shaderManager["BumpedPhong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("MaskedBumpedBlinnPhong Shader", shaderManager["MaskedBumpedBlinnPhong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("ParalaxedPhong Shader", shaderManager["ParalaxedPhong"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("CookTorrance Shader", shaderManager["CookTorrance"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Strauss Shader", shaderManager["Strauss"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("WardIso Shader", shaderManager["WardIso"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("WardAniso Shader", shaderManager["WardAniso"]);
	(*level->getInternalPackage()) << helperAsset;

	/*********************************
	*
	* Creating materials
	*
	*********************************/

	MaterialManager& materialManager	=	*engine->materialManager;

	Material* phongMaterial				=	new Material(shaderManager["Phong"],		"Phong Material");
	Material* phongBlinnMaterial		=	new Material(shaderManager["BlinnPhong"],	"Blinn-Phong Material");
	Material* testMaterial				=	new Material(testShader,					"Textured Material");
	Material* testMaterialNRM			=	new Material(testShaderNRM,					"Bumped Material");
	Material* maskedMaterial			=	new Material(maskedShader,					"Masked Material");
	Material* phongBlinnParalaxMaterial =	new Material(phongBlinnParalaxShader,		"Paralaxed Material");
	Material* cookTorranceMaterial		=	new Material(cookTorranceShader,			"CookTorrance Material");
	Material* straussMaterial			=	new Material(straussShader,					"Strauss Material");
	Material* straussMaterialMetalic	=	new Material(straussShader,					"Strauss Material Metalic");
	Material* wardIsoMaterial			=	new Material(wardIsoShader,					"Isotropic Ward Material");
	Material* wardAnisoMaterial			=	new Material(wardAnisoShader,				"Anisotropic Ward Material");
	Material* chestMaterial				=	new Material(testShaderNRM,					"Steampunk Chest Material");

	/*********************************
	*
	* Loading textures
	*
	*********************************/

	TextureManager& textureManager	=	*engine->textureManager;

										textureManager.Load("Default Texture Albedo",			"./Assets/Core/DefaultTexture.png");
	Texture* testingTextureNormal	=	textureManager.Load("Default Texture Normals",			"./Assets/Core/DefaultTexture_NRM.png");

	Texture* testGearTexture		=	textureManager.Load("Gears AO",							"./Assets/TestAssets/Gear_occlusion.tga");
	Texture* testGearTextureNormal	=	textureManager.Load("Gears Normals",					"./Assets/TestAssets/Gear_normals.tga");

	Texture* tessDiffTex			=	textureManager.Load("Stone Wall Albedo",				"./Assets/Core/wall_base.png");
	Texture* tessNrmTex				=	textureManager.Load("Stone Wall Normals",				"./Assets/Core/wall_normals.png");
	Texture* tessDispTex			=	textureManager.Load("Stone Wall Heights",				"./Assets/Core/wall_heights.png");

	Texture* tessVecDispTex			=	textureManager.Load("Vector Displacement AO",			"./Assets/TestAssets/vectorCube_occlusion.tga");
	Texture* tessVecDispTexNRM		=	textureManager.Load("Vector Displacment Normals",		"./Assets/TestAssets/vectorCube_normals.tga");
	Texture* tessVecDispTexDISP_TS	=	textureManager.Load("Vector Displacement Directions",	"./Assets/TestAssets/vectorCube_2_directions.tga");

	Texture* tgaTest				=	textureManager.Load("TGA Test",							"./Assets/TestAssets/dickbutt.tga");
	Texture* tgaRleTest				=	textureManager.Load("TGA RLE Test",						"./Assets/TestAssets/dickbutt_RLE.tga");	//apparently Qt TGA importer doesn't read TGA compressed with RLE.

	Texture* chestDiff				=	textureManager.Load("Steampunk Chest Albedo",			"./Assets/TestAssets/SteampunkChest_Diffuse.tga");
	Texture* chestNRM				=	textureManager.Load("Steampunk Chest Normals",			"./Assets/TestAssets/SteampunkChest_NRM.tga");

	//Adding textures to the internal package of the level.
	helperAsset = new Asset("Default Texture Albedo", textureManager["Default Texture Albedo"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Default Texture Normals", textureManager["Default Texture Normals"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Gears AO", textureManager["Gears AO"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Gears Normals", textureManager["Gears Normals"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Stone Wall Albedo", textureManager["Stone Wall Albedo"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Stone Wall Normals", textureManager["Stone Wall Normals"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Stone Wall Heights", textureManager["Stone Wall Heights"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Vector Displacement AO", textureManager["Vector Displacement AO"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Vector Displacment Normals", textureManager["Vector Displacment Normals"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Vector Displacement Directions", textureManager["Vector Displacement Directions"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("TGA Test", textureManager["TGA Test"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("TGA RLE Test", textureManager["TGA RLE Test"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Steampunk Chest Albedo", textureManager["Steampunk Chest Albedo"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Steampunk Chest Normals", textureManager["Steampunk Chest Normals"]);
	(*level->getInternalPackage()) << helperAsset;

	/*********************************
	*
	* Setting parameters of materials
	*
	*********************************/

	(*phongMaterial)["mat_diffuseColor"]							=	new glm::vec3(0.0f, 0.7f, 1.0f);

	(*materialManager["Blinn-Phong Material"])["mat_diffuseColor"]	=	new glm::vec3(0.5f, 0.7f, 1.0f);

	(*testMaterial)["mat_diffuseTexture"]							=	textureManager["Default Texture Albedo"];

	(*testMaterialNRM)["mat_diffuseTexture"]						=	textureManager["Default Texture Albedo"];
	(*testMaterialNRM)["mat_normalTexture"]							=	testingTextureNormal;

	(*maskedMaterial)["mat_diffuseTexture"]							=	testGearTexture;
	(*maskedMaterial)["mat_normalTexture"]							=	testGearTextureNormal;

	(*phongBlinnParalaxMaterial)["mat_diffuseTexture"]				=	tessDiffTex;
	(*phongBlinnParalaxMaterial)["mat_normalTexture"]				=	tessNrmTex;
	(*phongBlinnParalaxMaterial)["mat_heightTexture"]				=	tessDispTex;
	(*phongBlinnParalaxMaterial)["mat_bumpScale"]					=	 new float(0.1f);

	(*cookTorranceMaterial)["mat_diffuseColor"]						=	new glm::vec3(1.0f, 0.7f, 0.0f);
	(*cookTorranceMaterial)["mat_specularColor"]					=	new glm::vec3(1.0f, 1.0f, 1.0f);
	(*cookTorranceMaterial)["mat_roughness"]						=	new float(0.5f);
	(*cookTorranceMaterial)["mat_refractiveIndex"]					=	new float(0.15f);

	(*straussMaterial)["mat_albedo"]								=	new glm::vec3(0.0f, 1.0f, 0.0f);
	(*straussMaterial)["mat_roughness"]								=	new float(0.8f);	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
	(*straussMaterial)["mat_metaliness"]							=	new float(0.0f);

	(*straussMaterialMetalic)["mat_albedo"]							=	new glm::vec3(0.0f, 1.0f, 0.0f);
	(*straussMaterialMetalic)["mat_roughness"]						=	new float(0.8f);	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
	(*straussMaterialMetalic)["mat_metaliness"]						=	new float(1.0f);

	(*wardIsoMaterial)["mat_diffuse"]								=	new glm::vec3(1.0f, 0.7f, 0.0f);
	(*wardIsoMaterial)["mat_roughness"]								=	new float(0.3f);

	(*wardAnisoMaterial)["mat_diffuse"]								=	new glm::vec3(1.0f, 0.7f, 0.0f);
	(*wardAnisoMaterial)["mat_anisoRoughness"]						=	new glm::vec2(0.5f, 0.1f);

	(*chestMaterial)["mat_diffuseTexture"]							=	chestDiff;
	(*chestMaterial)["mat_normalTexture"]							=	chestNRM;

	//Adding materials to the internal package of the level.
	helperAsset = new Asset("Phong Material", materialManager["Phong Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Blinn-Phong Material", materialManager["Blinn-Phong Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Textured Material", materialManager["Textured Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Bumped Material", materialManager["Bumped Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Masked Material", materialManager["Masked Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Paralaxed Material", materialManager["Paralaxed Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("CookTorrance Material", materialManager["CookTorrance Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Strauss Material", materialManager["Strauss Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Strauss Material Metalic", materialManager["Strauss Material Metalic"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Isotropic Ward Material", materialManager["Isotropic Ward Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Anisotropic Ward Material", materialManager["Anisotropic Ward Material"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Steampunk Chest Material", materialManager["Steampunk Chest Material"]);
	(*level->getInternalPackage()) << helperAsset;
	
	/*********************************
	*
	* Setting up tessalated shaders
	* and materials
	*
	*********************************/
	
	QMap<QString, GLuint> tessalationSubshaders = QMap<QString, GLuint>();
	tessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"]				=	GL_VERTEX_SHADER;
	tessalationSubshaders["./Shader Files/SimpleTessalation_TCS.glsl"]					=	GL_TESS_CONTROL_SHADER;
	tessalationSubshaders["./Shader Files/Displacement_TES.glsl"]						=	GL_TESS_EVALUATION_SHADER;
	tessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"]						=	GL_FRAGMENT_SHADER;
	Shader* tessalationShader = new Shader(tessalationSubshaders, "TessalationTest");
	tessalationShader->drawingMode = GL_PATCHES;
	Material* testTessalationMaterial = new Material(tessalationShader, "TessalationMat");
	(*testTessalationMaterial)["mat_diffuseTexture"]			=	tessDiffTex;
	(*testTessalationMaterial)["mat_normalTexture"]				=	tessNrmTex;
	(*testTessalationMaterial)["mat_displacementTexture"]		=	tessDispTex;
	(*testTessalationMaterial)["mat_displacementScale"]			=	new float(0.1f);

	QMap<QString, GLuint> distanceTessalationSubshaders = QMap<QString, GLuint>();
	distanceTessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"]		=	GL_VERTEX_SHADER;
	distanceTessalationSubshaders["./Shader Files/DistanceBasedTesselation_TCS.glsl"]	=	GL_TESS_CONTROL_SHADER;
	distanceTessalationSubshaders["./Shader Files/Displacement_TES.glsl"]				=	GL_TESS_EVALUATION_SHADER;
	distanceTessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"]				=	GL_FRAGMENT_SHADER;
	Shader* distanceTessalationShader = new Shader(distanceTessalationSubshaders, "DistanceTessalationTest");
	distanceTessalationShader->drawingMode = GL_PATCHES;
	Material* distanceTessalationMaterial = new Material(distanceTessalationShader, "DistanceTessalationMat");
	(*distanceTessalationMaterial)["mat_diffuseTexture"]		=	tessDiffTex;
	(*distanceTessalationMaterial)["mat_normalTexture"]			=	tessNrmTex;
	(*distanceTessalationMaterial)["mat_displacementTexture"]	=	tessDispTex;
	(*distanceTessalationMaterial)["mat_displacementScale"]		=	new float(0.1f);
	
	QMap<QString, GLuint> vectorTessalationSubshaders = QMap<QString, GLuint>();
	vectorTessalationSubshaders["./Shader Files/Perspective_NTBTcTess_VS.glsl"]			=	GL_VERTEX_SHADER;
	vectorTessalationSubshaders["./Shader Files/DistanceBasedTesselation_TCS.glsl"]		=	GL_TESS_CONTROL_SHADER;
	vectorTessalationSubshaders["./Shader Files/VectorDisplacement_TES.glsl"]			=	GL_TESS_EVALUATION_SHADER;
	vectorTessalationSubshaders["./Shader Files/PhongBlinnBump_PS.glsl"]				=	GL_FRAGMENT_SHADER;
	Shader* vectorTessalationShader = new Shader(vectorTessalationSubshaders, "VectorTessalationTest");
	vectorTessalationShader->drawingMode = GL_PATCHES;
	Material* vectorTessalationMaterial = new Material(vectorTessalationShader, "VectorTessalationMat");
	(*vectorTessalationMaterial)["mat_diffuseTexture"]			=	tessVecDispTex;
	(*vectorTessalationMaterial)["mat_normalTexture"]			=	tessVecDispTexNRM;
	(*vectorTessalationMaterial)["mat_displacementTexture"]		=	tessVecDispTexDISP_TS;
	(*vectorTessalationMaterial)["mat_displacementScale"]		=	new float(0.5f);
	(*vectorTessalationMaterial)["mat_tesselationMultiplier"]	=	new float(64.0f);

	//Adding tessalation shaders and materials to the internal package of the level.
	helperAsset = new Asset("Tessalation Shader", shaderManager["TessalationTest"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Tessalation Material", materialManager["TessalationMat"]);
	(*level->getInternalPackage()) << helperAsset;

	helperAsset = new Asset("DistanceTessalation Shader", shaderManager["DistanceTessalationTest"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("DistanceTessalation Material", materialManager["DistanceTessalationMat"]);
	(*level->getInternalPackage()) << helperAsset;

	helperAsset = new Asset("VectorTessalation Shader", shaderManager["VectorTessalationTest"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("VectorTessalation Material", materialManager["VectorTessalationMat"]);
	(*level->getInternalPackage()) << helperAsset;
	
	/*********************************
	*
	* Creating and loading models
	*
	*********************************/

	//initialization of model importers
	AssimpModelImporter::Instance();
	FbxModelImporter::Instance();

	ModelBuilder& modelBuilder = *engine->modelBuilder;
	ModelManager& modelManager = *engine->modelManager;

	modelBuilder.CreatePlane("Plane", 10.0f, 10.0f, 50, 50);
	modelBuilder.CreateBox("Box", glm::vec3(1.0f, 1.0f, 1.0f));
	modelBuilder.CreateBox("BoxDense",glm::vec3(1.0f),glm::vec3(10,10,10));
	modelBuilder.CreateCylinder("Cylinder");
	modelBuilder.CreateCylinder("CylinderDense", 1.0f, 2.0f, 40, 10);
	modelBuilder.CreateCone("Cone");
	modelBuilder.CreateSphere("Sphere", 1.0f, 40, 40);
	modelBuilder.CreateTorus("Torus");
	modelBuilder.Load("TestModel",			"./Assets/TestAssets/TestModel.obj");
	modelBuilder.Load("TestModel2",			"./Assets/TestAssets/TestModel2.obj");
	modelBuilder.Load("TestTesselation",	"./Assets/TestAssets/TestTesselation.obj");
	modelBuilder.Load("Teapot",				"./Assets/TestAssets/teapot.obj");
	modelBuilder.Load("MayaBox",			"./Assets/TestAssets/MayaBox.obj");
	modelBuilder.Load("VectorSphere",		"./Assets/TestAssets/vectorDispSphere.obj");
	modelBuilder.Load("VectorCube",			"./Assets/TestAssets/vectorCube_LP_DENSE_T.obj");
	modelBuilder.Load("FbxTest",			"./Assets/TestAssets/FBXtest.fbx");
	modelBuilder.Load("FbxTest2",			"./Assets/TestAssets/FBXtest2.fbx");
	modelBuilder.Load("FbxTest3",			"./Assets/TestAssets/FBXtestPrepared.fbx");
	modelBuilder.Load("FbxTest4",			"./Assets/TestAssets/FBXHierarchyTest.fbx");
	modelBuilder.Load("FbxChest",			"./Assets/TestAssets/SteamPunkChest_LP.fbx");

	//Adding imported model assets to the internal package of the level.
	helperAsset = new Asset("TestModel Model", modelManager["TestModel"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("TestModel2 Model", modelManager["TestModel2"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("TestTesselation Model", modelManager["TestTesselation"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("Teapot Model", modelManager["Teapot"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("MayaBox Model", modelManager["MayaBox"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("VectorSphere Model", modelManager["VectorSphere"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("VectorCube Model", modelManager["VectorCube"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("FbxTest Model", modelManager["FbxTest"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("FbxTest2 Model", modelManager["FbxTest2"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("FbxTest3 Model", modelManager["FbxTest3"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("FbxTest4 Model", modelManager["FbxTest4"]);
	(*level->getInternalPackage()) << helperAsset;
	helperAsset = new Asset("FbxChest Model", modelManager["FbxChest"]);
	(*level->getInternalPackage()) << helperAsset;

	/*********************************
	*
	* Creating scene objects
	*
	*********************************/

	Entity* phongExample = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* phongModelC = new ModelComponent(phongExample, materialManager["Phong Material"], (*engine->modelManager)["Sphere"]);
	phongExample->AttachComponent(phongModelC);
	phongExample->name = QString("Phong Example");
	level->getRoot()->AttachSubobject(phongExample);

	Entity* phongBlinnExample = new Entity(glm::vec3(4.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* phongBlinnModelC = new ModelComponent(phongBlinnExample, phongBlinnMaterial, engine->modelManager->getModel("Sphere"));
	phongBlinnExample->AttachComponent(phongBlinnModelC);
	phongBlinnExample->name = QString("Blinn-Phong Example");
	level->getRoot()->AttachSubobject(phongBlinnExample);

	Entity* BumpMapExample = new Entity(glm::vec3(8.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* bumpMapModelC = new ModelComponent(BumpMapExample, testMaterialNRM, engine->modelManager->getModel("Sphere"));
	BumpMapExample->AttachComponent(bumpMapModelC);
	BumpMapExample->name = QString("Bump mapping Example");
	level->getRoot()->AttachSubobject(BumpMapExample);

	Entity* MaskedExample = new Entity(glm::vec3(12.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* maskedModelC = new ModelComponent(MaskedExample, maskedMaterial, engine->modelManager->getModel("Box"));
	MaskedExample->AttachComponent(maskedModelC);
	MaskedExample->name = QString("Masked blend mode Example");
	level->getRoot()->AttachSubobject(MaskedExample);

	Entity* ParralaxExample = new Entity(glm::vec3(16.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* parralaxModelC = new ModelComponent(ParralaxExample, phongBlinnParalaxMaterial, engine->modelManager->getModel("Teapot"));
	ParralaxExample->AttachComponent(parralaxModelC);
	ParralaxExample->name = QString("Displacement Mapping Example");
	level->getRoot()->AttachSubobject(ParralaxExample);

	Entity* CookTorranceExample = new Entity(glm::vec3(20.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* cookTorranceModelC = new ModelComponent(CookTorranceExample, cookTorranceMaterial, engine->modelManager->getModel("Sphere"));
	CookTorranceExample->AttachComponent(cookTorranceModelC);
	CookTorranceExample->name = QString("Cook-Torrance Example");
	level->getRoot()->AttachSubobject(CookTorranceExample);

	Entity* StraussExample = new Entity(glm::vec3(24.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* straussModelC = new ModelComponent(StraussExample, straussMaterial, engine->modelManager->getModel("Sphere"));
	StraussExample->AttachComponent(straussModelC);
	StraussExample->name = QString("Strauss Example");
	level->getRoot()->AttachSubobject(StraussExample);

	Entity* StraussConductiveExample = new Entity(glm::vec3(28.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* straussConductiveModelC = new ModelComponent(StraussConductiveExample, straussMaterialMetalic, engine->modelManager->getModel("Sphere"));
	StraussConductiveExample->AttachComponent(straussConductiveModelC);
	StraussConductiveExample->name = QString("Strauss Metalic Example");
	level->getRoot()->AttachSubobject(StraussConductiveExample);

	Entity* WardExample = new Entity(glm::vec3(32.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* wardModelC = new ModelComponent(WardExample, wardIsoMaterial, engine->modelManager->getModel("TestModel2"));
	WardExample->AttachComponent(wardModelC);
	WardExample->name = QString("Ward Example");
	level->getRoot()->AttachSubobject(WardExample);

	Entity* WardAnisotropicExample = new Entity(glm::vec3(36.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* wardAnisoModelC = new ModelComponent(WardAnisotropicExample, wardAnisoMaterial, engine->modelManager->getModel("TestModel2"));
	WardAnisotropicExample->AttachComponent(wardAnisoModelC);
	WardAnisotropicExample->name = QString("Ward Anisotropic Example");
	level->getRoot()->AttachSubobject(WardAnisotropicExample);

	Entity* DistanceTessellationExample = new Entity(glm::vec3(40.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* distanceTessModelC = new ModelComponent(DistanceTessellationExample, testTessalationMaterial, engine->modelManager->getModel("BoxDense"));
	DistanceTessellationExample->AttachComponent(distanceTessModelC);
	DistanceTessellationExample->name = QString("Distance Tessellation Example");
	level->getRoot()->AttachSubobject(DistanceTessellationExample);

	Entity* VectorTessellationExample = new Entity(glm::vec3(44.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* vectorTessModelC = new ModelComponent(VectorTessellationExample, vectorTessalationMaterial, engine->modelManager->getModel("VectorCube"));
	VectorTessellationExample->AttachComponent(vectorTessModelC);
	VectorTessellationExample->name = QString("Vector Displacement Tessellation Example");
	level->getRoot()->AttachSubobject(VectorTessellationExample);

	Entity* FbxExample = new Entity(glm::vec3(48.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.2f, 0.2f, 0.2f));
	ModelComponent* FbxExampleModelC = new ModelComponent(FbxExample, chestMaterial, engine->modelManager->getModel("FbxChest"));
	FbxExample->AttachComponent(FbxExampleModelC);
	FbxExample->name = QString("FBX import Example");
	level->getRoot()->AttachSubobject(FbxExample);

	Entity* FbxExample2 = new Entity(glm::vec3(52.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* FbxExample2ModelC = new ModelComponent(FbxExample2, phongMaterial, engine->modelManager->getModel("FbxTest2"));
	FbxExample2->AttachComponent(FbxExample2ModelC);
	FbxExample2->name = QString("FBX Example 2");
	level->getRoot()->AttachSubobject(FbxExample2);

	Entity* FbxExample3 = new Entity(glm::vec3(60.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	ModelComponent* FbxExample3ModelC = new ModelComponent(FbxExample3, phongMaterial, engine->modelManager->getModel("FbxTest4"));
	FbxExample3->AttachComponent(FbxExample3ModelC);
	FbxExample3->name = QString("FBX Hierarchy Example");
	level->getRoot()->AttachSubobject(FbxExample3);
	
	Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	mainCamera->AttachComponent(mainCameraComponent);
	mainCamera->name = QString("Main Camera");
	level->getRoot()->AttachSubobject(mainCamera);

	Entity* lightModelTestingCamera = new Entity(glm::vec3(5.0f, 5.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	CameraComponent* lightModelTestingCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	lightModelTestingCamera->AttachComponent(lightModelTestingCameraComponent);
	lightModelTestingCamera->name = QString("Light Model Testing Camera");
	level->getRoot()->AttachSubobject(lightModelTestingCamera);

	Entity* pointLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
	PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(1.0f, 0.2f, 1.0f), 0.5f, 100.0f, 0.4f);
	pointLight->name = QString("Point Light");
	level->getRoot()->AttachSubobject(pointLight);

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

	
	engine->sceneManager->LoadLevel(level, "TestLevel");
	engine->sceneManager->setCurrentCamera(mainCameraComponent);
	engine->sceneManager->mainLight = new DirectionalLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.2, 1.0), 1.0f);

	qDebug() << QJsonDocument(level->toJSON()).toJson();
}