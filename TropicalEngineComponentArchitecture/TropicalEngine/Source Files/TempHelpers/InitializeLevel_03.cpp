#include <QtCore/qdebug.h>
#include <QtCore/qjsondocument.h>

#include <Scene/Level.h>

#include <Shader/Shader.h>
#include <Shader/ShaderManager.h>
#include <Shader/Material.h>
#include <Shader/MaterialManager.h>
#include <Shader/ShaderBuilder/CommonMeshShaderBuilder.h>
#include <Shader/ShaderTechnique.h>

#include <Texture/Texture.h>
#include <Texture/TextureManager.h>

#include <Model/Model.h>
#include <Model/ModelBuilder.h>
#include <Model/ModelComponent.h>
#include <Model/ModelManager.h>
#include <Model/ModelImporter/AssimpModelImporter.h>
#include <Model/ModelImporter/FbxModelImporter.h>
#include <Model/ModelBuilder/TriangleModelBuilder.h>
#include <Model/ModelBuilder/PlaneModelBuilder.h>
#include <Model/ModelBuilder/BoxModelBuilder.h>
#include <Model/ModelBuilder/CylinderModelBuilder.h>
#include <Model/ModelBuilder/ConeModelBuilder.h>
#include <Model/ModelBuilder/SphereModelBuilder.h>
#include <Model/ModelBuilder/TorusModelBuilder.h>

#include <Camera/CameraComponent.h>

#include <Scene/Entity.h>

#include <Light/DirectionalLightComponent.h>
#include <Light/PointLightComponent.h>
#include <Light/SpotLightComponent.h>

#include <Scene/SceneManager.h>

#include <Package/Asset.h>
#include <Package/AssetManager.h>
#include <Package/PackageManager.h>

#include <TempHelpers/OglDevTut03.h>
#include <TempHelpers/TempPlayerComponent.h>
#include <TempHelpers/TempMovingComponent.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	void OglDevTut03::InitializeLevel()
	{
		TropicalEngineApplication* engine = TropicalEngineApplication::instance();

		/*********************************
		 *
		 * Creating empty level
		 *
		 *********************************/

		level = new Level("TestLevel");

		AssetManager& assetManager = *engine->assetManager;
		PackageManager& packageManager = *engine->packageManager;
		Asset* helperAsset;

		/*********************************
		*
		* Creating shaders
		*
		*********************************/

		ShaderManager& shaderManager = *engine->shaderManager;

		Shader* phongBlinnParalaxShader = shaderManager.Load("ParalaxedPhong", "./Shader Files/Perspective_NTBTc_VS.glsl", "./Shader Files/PhongBlinnParalax_PS.glsl");

		ShaderTechnique* lambertTechnique = new ShaderTechnique("Lambert", &CommonMeshShaderBuilder::Instance());
		lambertTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/LambertLightingModel.glsl");
		
		ShaderTechnique* phongTechnique = new ShaderTechnique("Phong", &CommonMeshShaderBuilder::Instance());
		phongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");

		ShaderTechnique* blinnPhongTechnique = new ShaderTechnique("BlinnPhong", &CommonMeshShaderBuilder::Instance());
		blinnPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");

		ShaderTechnique* cookTorranceTechnique = new ShaderTechnique("CookTorrance", &CommonMeshShaderBuilder::Instance());
		cookTorranceTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/CookTorranceLightingModel.glsl");

		ShaderTechnique* straussTechnique = new ShaderTechnique("Strauss", &CommonMeshShaderBuilder::Instance());
		straussTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/StraussLightingModel.glsl");

		ShaderTechnique* wardIsoTechnique = new ShaderTechnique("WardIso", &CommonMeshShaderBuilder::Instance());
		wardIsoTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/WardIsotropicLightingModel.glsl");

		ShaderTechnique* wardAnisoTechnique = new ShaderTechnique("WardAniso", &CommonMeshShaderBuilder::Instance());
		wardAnisoTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/WardAnisotropicLightingModel.glsl");

		ShaderTechnique* texturedLambertTechnique = new ShaderTechnique("LambertTextured", &CommonMeshShaderBuilder::Instance());
		texturedLambertTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/LambertLightingModel.glsl");
		texturedLambertTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/Textured.glsl");

		ShaderTechnique* bumpmappedPhongTechnique = new ShaderTechnique("PhongBumpmapped", &CommonMeshShaderBuilder::Instance());
		bumpmappedPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");
		bumpmappedPhongTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");

		ShaderTechnique* maskedBumpmappedBlinnPhongTechnique = new ShaderTechnique("BlinnBumpmappedMasked", &CommonMeshShaderBuilder::Instance());
		maskedBumpmappedBlinnPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		maskedBumpmappedBlinnPhongTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		maskedBumpmappedBlinnPhongTechnique->setInput("Blend Mode", "./Shader Files/Blending/BlendMasked.glsl");

		ShaderTechnique* staticTessellationTechnique = new ShaderTechnique("StaticTessallation", &CommonMeshShaderBuilder::Instance());
		staticTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		staticTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		staticTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		staticTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/SimpleTessellation.glsl");
		staticTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationDisplacement.glsl");

		ShaderTechnique* distanceTessellationTechnique = new ShaderTechnique("DistanceTessallation", &CommonMeshShaderBuilder::Instance());
		distanceTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		distanceTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		distanceTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		distanceTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/DistanceBasedTessellation.glsl");
		distanceTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationDisplacement.glsl");

		ShaderTechnique* vectorTessellationTechnique = new ShaderTechnique("VectorTessallation", &CommonMeshShaderBuilder::Instance());
		vectorTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		vectorTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		vectorTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		vectorTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/DistanceBasedTessellation.glsl");
		vectorTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationVectorDisplacement.glsl");


		//Adding shaders to the internal package of the level.
		//helperAsset = new Asset("Phong Shader", shaderManager["Phong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("BlinnPhong Shader", shaderManager["BlinnPhong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("TexturedPhong Shader", shaderManager["TexturedPhong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("BumpedPhong Shader", shaderManager["BumpedPhong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("MaskedBumpedBlinnPhong Shader", shaderManager["MaskedBumpedBlinnPhong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("ParalaxedPhong Shader", shaderManager["ParalaxedPhong"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("CookTorrance Shader", shaderManager["CookTorrance"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("Strauss Shader", shaderManager["Strauss"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("WardIso Shader", shaderManager["WardIso"]);
		//(*level->getInternalPackage()) << helperAsset;
		//helperAsset = new Asset("WardAniso Shader", shaderManager["WardAniso"]);
		//(*level->getInternalPackage()) << helperAsset;
		/// TODO: tessallation shaders missing

		/*********************************
		*
		* Creating materials
		*
		*********************************/

		MaterialManager& materialManager = *engine->materialManager;

		Material* lambertMaterial				= new Material(shaderManager.getShaderTechnique("Lambert"), "Lambert Material");
		Material* phongMaterial					= new Material(shaderManager.getShaderTechnique("Phong"), "Phong Material");
		Material* phongBlinnMaterial			= new Material(shaderManager.getShaderTechnique("BlinnPhong"), "Blinn-Phong Material");
		Material* cookTorranceMaterial			= new Material(shaderManager.getShaderTechnique("CookTorrance"), "CookTorrance Material");
		Material* straussMaterial				= new Material(shaderManager.getShaderTechnique("Strauss"), "Strauss Material");
		Material* straussMaterialMetalic		= new Material(shaderManager.getShaderTechnique("Strauss"), "Strauss Material Metalic");
		Material* wardIsoMaterial				= new Material(shaderManager.getShaderTechnique("WardIso"), "Isotropic Ward Material");
		Material* wardAnisoMaterial				= new Material(shaderManager.getShaderTechnique("WardAniso"), "Anisotropic Ward Material");

		Material* texturedMaterial				= new Material(shaderManager.getShaderTechnique("LambertTextured"), "Textured Material");
		Material* bumpedMaterial				= new Material(shaderManager.getShaderTechnique("PhongBumpmapped"), "Bumped Material");
		Material* maskedMaterial				= new Material(shaderManager.getShaderTechnique("BlinnBumpmappedMasked"), "Masked Material");

		Material* phongBlinnParalaxMaterial		= new Material(phongBlinnParalaxShader, "Paralaxed Material");

		Material* staticTessellationMaterial	= new Material(shaderManager.getShaderTechnique("StaticTessallation"), "Tessallated Material");
		Material* distanceTessellationMaterial	= new Material(shaderManager.getShaderTechnique("DistanceTessallation"), "Distance Tessallated Material");
		Material* vectorTessellationMaterial	= new Material(shaderManager.getShaderTechnique("VectorTessallation"), "Vector Tessallated Material");
		
		Material* chestMaterial					= new Material(shaderManager.getShaderTechnique("PhongBumpmapped"), "Steampunk Chest Material");

		/*********************************
		*
		* Loading textures
		*
		*********************************/

		TextureManager& textureManager = *engine->textureManager;

											  textureManager.Load("Default Texture Albedo", "./Assets/Core/DefaultTexture.png");
		Texture* testingTextureNormal		= textureManager.Load("Default Texture Normals", "./Assets/Core/DefaultTexture_NRM.png");

		Texture* testGearTexture			= textureManager.Load("Gears AO", "./Assets/TestAssets/Gear_occlusion.tga");
		Texture* testGearTextureNormal		= textureManager.Load("Gears Normals", "./Assets/TestAssets/Gear_normals.tga");

		Texture* tessDiffTex				= textureManager.Load("Stone Wall Albedo", "./Assets/Core/wall_base.png");
		Texture* tessNrmTex					= textureManager.Load("Stone Wall Normals", "./Assets/Core/wall_normals.png");
		Texture* tessDispTex				= textureManager.Load("Stone Wall Heights", "./Assets/Core/wall_heights.png");

		Texture* tessVecDispTex				= textureManager.Load("Vector Displacement AO", "./Assets/TestAssets/vectorCube_occlusion.tga");
		Texture* tessVecDispTexNRM			= textureManager.Load("Vector Displacment Normals", "./Assets/TestAssets/vectorCube_normals.tga");
		Texture* tessVecDispTexDISP_TS		= textureManager.Load("Vector Displacement Directions", "./Assets/TestAssets/vectorCube_2_directions.tga");

		Texture* tgaTest					= textureManager.Load("TGA Test", "./Assets/TestAssets/dickbutt.tga");
		Texture* tgaRleTest					= textureManager.Load("TGA RLE Test", "./Assets/TestAssets/dickbutt_RLE.tga");	//apparently Qt TGA importer doesn't read TGA compressed with RLE.

		Texture* chestDiff					= textureManager.Load("Steampunk Chest Albedo", "./Assets/TestAssets/SteampunkChest_Diffuse.tga");
		Texture* chestNRM					= textureManager.Load("Steampunk Chest Normals", "./Assets/TestAssets/SteampunkChest_NRM.tga");

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

		(*lambertMaterial)["mat_color"]					= new glm::vec3(0.0f, 1.0f, 0.7f);

		(*phongMaterial)["mat_color"]					= new glm::vec3(0.0f, 0.7f, 1.0f);

		(*materialManager["Blinn-Phong Material"])["mat_color"] = new glm::vec3(0.5f, 0.7f, 1.0f);

		(*cookTorranceMaterial)["mat_color"]			= new glm::vec3(1.0f, 0.7f, 0.0f);
		(*cookTorranceMaterial)["mat_specular"]			= new glm::vec3(1.0f, 1.0f, 1.0f);
		(*cookTorranceMaterial)["mat_roughness"]		= new float(0.5f);
		(*cookTorranceMaterial)["mat_refractiveIndex"]	= new float(0.15f);

		(*straussMaterial)["mat_color"]					= new glm::vec3(0.1f, 1.0f, 0.1f);
		(*straussMaterial)["mat_roughness"]				= new float(0.8f);	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
		(*straussMaterial)["mat_metalness"]				= new float(0.0f);

		(*straussMaterialMetalic)["mat_color"]			= new glm::vec3(0.1f, 1.0f, 0.1f);
		(*straussMaterialMetalic)["mat_roughness"]		= new float(0.8f);	//actually its smoothness. Changed name to fit PBR naming conventions but didn't inverse it in shader yet.
		(*straussMaterialMetalic)["mat_metalness"]		= new float(1.0f);

		(*wardIsoMaterial)["mat_color"]					= new glm::vec3(1.0f, 0.7f, 0.0f);
		(*wardIsoMaterial)["mat_roughness"]				= new float(0.3f);

		(*wardAnisoMaterial)["mat_color"]				= new glm::vec3(1.0f, 0.7f, 0.0f);
		(*wardAnisoMaterial)["mat_roughness"]			= new glm::vec2(0.5f, 0.1f);

		(*texturedMaterial)["mat_color"] = textureManager["Default Texture Albedo"];

		(*bumpedMaterial)["mat_color"] = textureManager["Default Texture Albedo"];
		(*bumpedMaterial)["mat_normal"] = testingTextureNormal;

		(*maskedMaterial)["mat_color"] = testGearTexture;
		(*maskedMaterial)["mat_normal"] = testGearTextureNormal;

		(*phongBlinnParalaxMaterial)["mat_diffuseTexture"] = tessDiffTex;
		(*phongBlinnParalaxMaterial)["mat_normalTexture"] = tessNrmTex;
		(*phongBlinnParalaxMaterial)["mat_heightTexture"] = tessDispTex;
		(*phongBlinnParalaxMaterial)["mat_bumpScale"] = new float(0.1f);

		(*staticTessellationMaterial)["mat_color"] = tessDiffTex;
		(*staticTessellationMaterial)["mat_normal"] = tessNrmTex;
		(*staticTessellationMaterial)["mat_displacementTexture"] = tessDispTex;
		(*staticTessellationMaterial)["mat_displacementScale"] = new float(0.1f);

		(*distanceTessellationMaterial)["mat_color"] = tessDiffTex;
		(*distanceTessellationMaterial)["mat_normal"] = tessNrmTex;
		(*distanceTessellationMaterial)["mat_displacementTexture"] = tessDispTex;
		(*distanceTessellationMaterial)["mat_displacementScale"] = new float(0.1f);
		(*distanceTessellationMaterial)["mat_tesselationMultiplier"] = new float(48.0f);

		(*vectorTessellationMaterial)["mat_color"] = tessVecDispTex;
		(*vectorTessellationMaterial)["mat_normal"] = tessVecDispTexNRM;
		(*vectorTessellationMaterial)["mat_displacementTexture"] = tessVecDispTexDISP_TS;
		(*vectorTessellationMaterial)["mat_displacementScale"] = new float(0.4f);
		(*vectorTessellationMaterial)["mat_tesselationMultiplier"] = new float(64.0f);

		(*chestMaterial)["mat_color"]			= chestDiff;
		(*chestMaterial)["mat_normal"]			= chestNRM;

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
		* Creating and loading models
		*
		*********************************/

		//initialization of model importers
		AssimpModelImporter::Instance();
		FbxModelImporter::Instance();

		ModelBuilder& modelBuilder = *engine->modelBuilder;
		ModelManager& modelManager = *engine->modelManager;

		AbstractModelBuilder* triangleBuilder = static_cast<TriangleModelBuilder*>(modelBuilder.getModelBuilder("Triangle"));
		triangleBuilder->setParameter("name", QString("Triangle"));
		triangleBuilder->Build();

		PlaneModelBuilder planeBuilder = PlaneModelBuilder();
		planeBuilder.setParameter("name", QString("Plane"));
		planeBuilder.setParameter("size X", float(10.0f));
		planeBuilder.setParameter("size Y", float(10.0f));
		planeBuilder.setParameter("subdivisions X", int(50));
		planeBuilder.setParameter("subdivisions Y", int(50));
		planeBuilder.Build();

		BoxModelBuilder boxBuilder = BoxModelBuilder();
		boxBuilder.setParameter("name", QString("Box"));
		boxBuilder.Build();

		BoxModelBuilder boxDenseBuilder = BoxModelBuilder();
		boxDenseBuilder.setParameter("name", QString("BoxDense"));
		boxDenseBuilder.setParameter("subdivisions X", uint(10));
		boxDenseBuilder.setParameter("subdivisions Y", uint(10));
		boxDenseBuilder.setParameter("subdivisions Z", uint(10));
		boxDenseBuilder.Build();

		CylinderModelBuilder cylinderBuilder = CylinderModelBuilder();
		cylinderBuilder.setParameter("name", QString("Cylinder"));
		cylinderBuilder.Build();

		CylinderModelBuilder cylinderDenseBuilder = CylinderModelBuilder();
		cylinderDenseBuilder.setParameter("name", QString("CylinderDense"));
		cylinderDenseBuilder.setParameter("subdivisions axis", uint(40));
		cylinderDenseBuilder.setParameter("subdivisions height", uint(10));
		cylinderDenseBuilder.Build();

		ConeModelBuilder coneBuilder = ConeModelBuilder();
		coneBuilder.setParameter("name", QString("Cone"));
		coneBuilder.Build();

		SphereModelBuilder sphereBuilder = SphereModelBuilder();
		sphereBuilder.setParameter("name", QString("Sphere"));
		sphereBuilder.setParameter("subdivisions axis", uint(40));
		sphereBuilder.setParameter("subdivisions height", uint(40));
		sphereBuilder.Build();

		TorusModelBuilder torusBuilder = TorusModelBuilder();
		torusBuilder.setParameter("name", QString("Torus"));
		torusBuilder.Build();

		modelBuilder.Load("TestModel", "./Assets/TestAssets/TestModel.obj");
		modelBuilder.Load("TestModel2", "./Assets/TestAssets/TestModel2.obj");
		modelBuilder.Load("TestTesselation", "./Assets/TestAssets/TestTesselation.obj");
		modelBuilder.Load("Teapot", "./Assets/TestAssets/teapot.obj");
		modelBuilder.Load("MayaBox", "./Assets/TestAssets/MayaBox.obj");
		modelBuilder.Load("VectorSphere", "./Assets/TestAssets/vectorDispSphere.obj");
		modelBuilder.Load("VectorCube", "./Assets/TestAssets/vectorCube_LP_DENSE_T.obj");
		modelBuilder.Load("FbxTest", "./Assets/TestAssets/FBXtest.fbx");
		modelBuilder.Load("FbxTest2", "./Assets/TestAssets/FBXtest2.fbx");
		modelBuilder.Load("FbxTest3", "./Assets/TestAssets/FBXtestPrepared.fbx");
		modelBuilder.Load("FbxTest4", "./Assets/TestAssets/FBXHierarchyTest.fbx");
		modelBuilder.Load("FbxChest", "./Assets/TestAssets/SteamPunkChest_LP.fbx");

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

		Entity* phongExample = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* phongModelC = new ModelComponent(phongExample, lambertMaterial, (*engine->modelManager)["Torus"]);
		phongExample->name = QString("Phong Example");
		level->getRoot()->AttachSubobject(phongExample);

		Entity* phongBlinnExample = new Entity(glm::vec3(4.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* phongBlinnModelC = new ModelComponent(phongBlinnExample, phongBlinnMaterial, engine->modelManager->getModel("Sphere"));
		phongBlinnExample->name = QString("Blinn-Phong Example");
		level->getRoot()->AttachSubobject(phongBlinnExample);

		Entity* BumpMapExample = new Entity(glm::vec3(8.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* bumpMapModelC = new ModelComponent(BumpMapExample, bumpedMaterial, engine->modelManager->getModel("TestModel2"));
		BumpMapExample->name = QString("Bump mapping Example");
		level->getRoot()->AttachSubobject(BumpMapExample);

		Entity* MaskedExample = new Entity(glm::vec3(12.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* maskedModelC = new ModelComponent(MaskedExample, maskedMaterial, engine->modelManager->getModel("Box"));
		MaskedExample->name = QString("Masked blend mode Example");
		level->getRoot()->AttachSubobject(MaskedExample);

		Entity* ParralaxExample = new Entity(glm::vec3(16.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* parralaxModelC = new ModelComponent(ParralaxExample, phongBlinnParalaxMaterial, engine->modelManager->getModel("Teapot"));
		ParralaxExample->name = QString("Displacement Mapping Example");
		level->getRoot()->AttachSubobject(ParralaxExample);

		Entity* CookTorranceExample = new Entity(glm::vec3(20.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* cookTorranceModelC = new ModelComponent(CookTorranceExample, cookTorranceMaterial, engine->modelManager->getModel("Sphere"));
		CookTorranceExample->name = QString("Cook-Torrance Example");
		level->getRoot()->AttachSubobject(CookTorranceExample);

		Entity* StraussExample = new Entity(glm::vec3(24.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* straussModelC = new ModelComponent(StraussExample, straussMaterial, engine->modelManager->getModel("Sphere"));
		StraussExample->name = QString("Strauss Example");
		level->getRoot()->AttachSubobject(StraussExample);

		Entity* StraussConductiveExample = new Entity(glm::vec3(28.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* straussConductiveModelC = new ModelComponent(StraussConductiveExample, straussMaterialMetalic, engine->modelManager->getModel("Sphere"));
		StraussConductiveExample->name = QString("Strauss Metalic Example");
		level->getRoot()->AttachSubobject(StraussConductiveExample);

		Entity* WardExample = new Entity(glm::vec3(32.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* wardModelC = new ModelComponent(WardExample, wardIsoMaterial, engine->modelManager->getModel("TestModel2"));
		WardExample->name = QString("Ward Example");
		level->getRoot()->AttachSubobject(WardExample);

		Entity* WardAnisotropicExample = new Entity(glm::vec3(36.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* wardAnisoModelC = new ModelComponent(WardAnisotropicExample, wardAnisoMaterial, engine->modelManager->getModel("TestModel2"));
		WardAnisotropicExample->name = QString("Ward Anisotropic Example");
		level->getRoot()->AttachSubobject(WardAnisotropicExample);

		Entity* DistanceTessellationExample = new Entity(glm::vec3(40.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* distanceTessModelC = new ModelComponent(DistanceTessellationExample, distanceTessellationMaterial, engine->modelManager->getModel("BoxDense"));
		DistanceTessellationExample->name = QString("Distance Tessellation Example");
		level->getRoot()->AttachSubobject(DistanceTessellationExample);

		Entity* VectorTessellationExample = new Entity(glm::vec3(44.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* vectorTessModelC = new ModelComponent(VectorTessellationExample, vectorTessellationMaterial, engine->modelManager->getModel("VectorCube"));
		VectorTessellationExample->name = QString("Vector Displacement Tessellation Example");
		level->getRoot()->AttachSubobject(VectorTessellationExample);

		Entity* FbxExample = new Entity(glm::vec3(48.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.2f, 0.2f, 0.2f));
		ModelComponent* FbxExampleModelC = new ModelComponent(FbxExample, chestMaterial, engine->modelManager->getModel("FbxChest"));
		FbxExample->name = QString("FBX import Example");
		level->getRoot()->AttachSubobject(FbxExample);

		Entity* FbxExample2 = new Entity(glm::vec3(52.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* FbxExample2ModelC = new ModelComponent(FbxExample2, phongMaterial, engine->modelManager->getModel("FbxTest2"));
		FbxExample2->name = QString("FBX Example 2");
		level->getRoot()->AttachSubobject(FbxExample2);

		Entity* FbxExample3 = new Entity(glm::vec3(60.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* FbxExample3ModelC = new ModelComponent(FbxExample3, phongMaterial, engine->modelManager->getModel("FbxTest4"));
		FbxExample3->name = QString("FBX Hierarchy Example");
		level->getRoot()->AttachSubobject(FbxExample3);

		Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		mainCamera->name = QString("Main Camera");
		TempPlayerComponent* cameraController = new TempPlayerComponent(mainCamera);
		level->getRoot()->AttachSubobject(mainCamera);

		Entity* lightModelTestingCamera = new Entity(glm::vec3(5.0f, 5.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		CameraComponent* lightModelTestingCameraComponent = new CameraComponent(lightModelTestingCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		lightModelTestingCamera->name = QString("Light Model Testing Camera");
		level->getRoot()->AttachSubobject(lightModelTestingCamera);

		Entity* pointLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(), glm::vec3(0.4f, 0.4f, 0.4f));
		PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(1.0f, 0.2f, 1.0f), 0.8f, 18.0f, 1.0f);
		TempMovingComponent* pointLightMoveComponent = new TempMovingComponent(pointLight, glm::vec3(60.0f, -0.2f, 3.0f), glm::vec3(0.0f, -0.2f, 3.0f), 15.0f);
		ModelComponent* pointLightMarker = new ModelComponent(pointLight, phongMaterial, engine->modelManager->getModel("Sphere"));
		pointLight->name = QString("Point Light");
		level->getRoot()->AttachSubobject(pointLight);

		Entity* spotLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(), glm::vec3(0.4f, 0.4f, 0.4f));
		SpotLightComponent* spotLightComponent = new SpotLightComponent(spotLight, glm::vec3(1.0f, 0.2f, 0.1f), 1.5f, 25.0f);
		TempMovingComponent* spotLightMoveComponent = new TempMovingComponent(spotLight, glm::vec3(60.0f, 2.2f, 0.0f), glm::vec3(0.0f, 2.2f, 0.0f), 20.0f);
		ModelComponent* spotLightMarker = new ModelComponent(spotLight, phongMaterial, engine->modelManager->getModel("Cone"));
		spotLight->name = QString("Spot Light");
		level->getRoot()->AttachSubobject(spotLight);

		Entity* ground = new Entity(glm::vec3(30.0f, -10.0f, 0.0f), glm::quat(), glm::vec3(15.0f));
		ModelComponent* groundModel = new ModelComponent(ground, phongBlinnMaterial, engine->modelManager->getModel("Plane"));
		ground->name = QString("Ground");
		level->getRoot()->AttachSubobject(ground);

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

		phongModelC->lightedBy.append(spotLightComponent);
		phongBlinnModelC->lightedBy.append(spotLightComponent);
		bumpMapModelC->lightedBy.append(spotLightComponent);
		maskedModelC->lightedBy.append(spotLightComponent);
		parralaxModelC->lightedBy.append(spotLightComponent);
		cookTorranceModelC->lightedBy.append(spotLightComponent);
		straussModelC->lightedBy.append(spotLightComponent);
		straussConductiveModelC->lightedBy.append(spotLightComponent);
		wardModelC->lightedBy.append(spotLightComponent);
		wardAnisoModelC->lightedBy.append(spotLightComponent);
		distanceTessModelC->lightedBy.append(spotLightComponent);
		vectorTessModelC->lightedBy.append(spotLightComponent);
		FbxExampleModelC->lightedBy.append(spotLightComponent);


		engine->sceneManager->LoadLevel(level, "TestLevel");
		engine->sceneManager->setCurrentCamera(mainCameraComponent);
		engine->sceneManager->mainLight = new DirectionalLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.6, 1.0), 1.0f);

		//qDebug() << QJsonDocument(level->toJSON()).toJson();
	}

}