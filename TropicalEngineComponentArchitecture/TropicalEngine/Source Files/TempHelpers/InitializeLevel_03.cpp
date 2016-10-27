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
#include <Texture/CubemapTexture.h>
#include <Texture/TextureManager.h>
#include <Texture/TextureImporter/QtTextureImporter.h>
#include <Texture/TextureImporter/OpenExrTextureImporter.h>

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

#include <Light/AmbientLightComponent.h>
#include <Light/DirectionalLightComponent.h>
#include <Light/PointLightComponent.h>
#include <Light/SpotLightComponent.h>

#include <ReflectionProbe/ReflectionProbeManager.h>

#include <Scene/Scene.h>
#include <Scene/Entity.h>
#include <Scene/LevelImporter/FbxLevelImporter.h>

#include <Package/Asset.h>
#include <Package/AssetManager.h>
#include <Package/PackageManager.h>

#include <Utills/Directions.h>

#include <TempHelpers/OglDevTut03.h>
#include <TempHelpers/TempPlayerComponent.h>
#include <TempHelpers/TempMovingComponent.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	void OglDevTut03::InitializeLevel(Scene* scene)
	{
		TropicalEngineApplication* engine = TropicalEngineApplication::instance();

		#pragma region Creating Level and Asset Managers
		/*********************************
		 *
		 * Creating empty level
		 *
		 *********************************/

		level = new Level("TestLevel");

		AssetManager& assetManager = AssetManager::instance();
		PackageManager& packageManager = PackageManager::instance();;
		Asset* helperAsset;
		#pragma endregion


		#pragma region Creating Shaders
		/*********************************
		*
		* Creating shaders
		*
		*********************************/

		ShaderManager& shaderManager = ShaderManager::instance();

		ShaderTechnique* lambertTechnique = new ShaderTechnique("LambertTest", &CommonMeshShaderBuilder::instance());
		lambertTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/LambertLightingModel.glsl");
		
		ShaderTechnique* phongTechnique = new ShaderTechnique("PhongTest", &CommonMeshShaderBuilder::instance());
		phongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");

		ShaderTechnique* blinnPhongTechnique = new ShaderTechnique("BlinnPhongTest", &CommonMeshShaderBuilder::instance());
		blinnPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");

		ShaderTechnique* cookTorranceTechnique = new ShaderTechnique("CookTorranceTest", &CommonMeshShaderBuilder::instance());
		cookTorranceTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/CookTorranceLightingModel.glsl");

		ShaderTechnique* straussTechnique = new ShaderTechnique("StraussTest", &CommonMeshShaderBuilder::instance());
		straussTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/StraussLightingModel.glsl");

		ShaderTechnique* wardIsoTechnique = new ShaderTechnique("WardIsoTest", &CommonMeshShaderBuilder::instance());
		wardIsoTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/WardIsotropicLightingModel.glsl");

		ShaderTechnique* wardAnisoTechnique = new ShaderTechnique("WardAnisoTest", &CommonMeshShaderBuilder::instance());
		wardAnisoTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/WardAnisotropicLightingModel.glsl");

		ShaderTechnique* celShadingTechnique = new ShaderTechnique("CelShadingTest", &CommonMeshShaderBuilder::instance());
		celShadingTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/CelShadingLightingModel.glsl");
		celShadingTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/Textured.glsl");

		ShaderTechnique* texturedLambertTechnique = new ShaderTechnique("LambertTexturedTest", &CommonMeshShaderBuilder::instance());
		texturedLambertTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/LambertLightingModel.glsl");
		texturedLambertTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/Textured.glsl");

		ShaderTechnique* bumpmappedPhongTechnique = new ShaderTechnique("PhongBumpmappedTest", &CommonMeshShaderBuilder::instance());
		bumpmappedPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		bumpmappedPhongTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");

		ShaderTechnique* maskedBumpmappedBlinnPhongTechnique = new ShaderTechnique("BlinnBumpmappedMaskedTest", &CommonMeshShaderBuilder::instance());
		maskedBumpmappedBlinnPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		maskedBumpmappedBlinnPhongTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		maskedBumpmappedBlinnPhongTechnique->setInput("Blend Mode", "./Shader Files/Blending/BlendMasked.glsl");

		ShaderTechnique* parallaxedBlinnPhongTechnique = new ShaderTechnique("BlinnParallaxedTest", &CommonMeshShaderBuilder::instance());
		parallaxedBlinnPhongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");
		parallaxedBlinnPhongTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/ParallaxMapped.glsl");

		ShaderTechnique* staticTessellationTechnique = new ShaderTechnique("StaticTessallationTest", &CommonMeshShaderBuilder::instance());
		staticTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		staticTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		staticTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		staticTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/SimpleTessellation.glsl");
		staticTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationDisplacement.glsl");

		ShaderTechnique* distanceTessellationTechnique = new ShaderTechnique("DistanceTessallationTest", &CommonMeshShaderBuilder::instance());
		distanceTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		distanceTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		distanceTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		distanceTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/DistanceBasedTessellation.glsl");
		distanceTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationDisplacement.glsl");

		ShaderTechnique* vectorTessellationTechnique = new ShaderTechnique("VectorTessallationTest", &CommonMeshShaderBuilder::instance());
		vectorTessellationTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		vectorTessellationTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		vectorTessellationTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		vectorTessellationTechnique->setInput("TCS Shader", "./Shader Files/Mesh/Tessellation/Control/DistanceBasedTessellation.glsl");
		vectorTessellationTechnique->setInput("TES Shader", "./Shader Files/Mesh/Tessellation/Evaluation/TessellationVectorDisplacement.glsl");

		ShaderTechnique* skyboxTechnique = new ShaderTechnique("SkyboxTest", &CommonMeshShaderBuilder::instance());
		skyboxTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		skyboxTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/Skybox.glsl");

		ShaderTechnique* cubemapTechnique = new ShaderTechnique("CubemapTest", &CommonMeshShaderBuilder::instance());
		cubemapTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		cubemapTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/CubemapReflected.glsl");

		ShaderTechnique* cubemapTexturedTechnique = new ShaderTechnique("CubemapTexturedTest", &CommonMeshShaderBuilder::instance());
		cubemapTexturedTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		cubemapTexturedTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/TexturedCubemapReflected.glsl");

		ShaderTechnique* iblTechnique = new ShaderTechnique("IblTest", &CommonMeshShaderBuilder::instance());
		iblTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		iblTechnique->setInput("Custom Lighting", "./Shader Files/CustomLighting/ImageBasedLighting.glsl");
		iblTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");

		ShaderTechnique* iblCubemapTechnique = new ShaderTechnique("IblCubemapTest", &CommonMeshShaderBuilder::instance());
		iblCubemapTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/BlinnPhongLightingModel.glsl");
		iblCubemapTechnique->setInput("Custom Lighting", "./Shader Files/CustomLighting/ImageBasedLightingCubemap.glsl");
		iblCubemapTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/BumpTextured.glsl");
		#pragma endregion

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
		// TODO: tessallation shaders missing


		#pragma region Creating Materials
		/*********************************
		*
		* Creating materials
		*
		*********************************/

		MaterialManager& materialManager = MaterialManager::instance();

		Material* lambertMaterial				= new Material(shaderManager.getShaderTechnique("LambertTest"), "Lambert Material");
		Material* phongMaterial					= new Material(shaderManager.getShaderTechnique("PhongTest"), "Phong Material");
		Material* phongBlinnMaterial			= new Material(shaderManager.getShaderTechnique("BlinnPhongTest"), "Blinn-Phong Material");
		Material* cookTorranceMaterial			= new Material(shaderManager.getShaderTechnique("CookTorranceTest"), "CookTorrance Material");
		Material* straussMaterial				= new Material(shaderManager.getShaderTechnique("StraussTest"), "Strauss Material");
		Material* straussMaterialMetalic		= new Material(shaderManager.getShaderTechnique("StraussTest"), "Strauss Material Metalic");
		Material* wardIsoMaterial				= new Material(shaderManager.getShaderTechnique("WardIsoTest"), "Isotropic Ward Material");
		Material* wardAnisoMaterial				= new Material(shaderManager.getShaderTechnique("WardAnisoTest"), "Anisotropic Ward Material");

		Material* celShadingMaterial = new Material(shaderManager.getShaderTechnique("CelShadingTest"), "Cel Shading Material");

		Material* texturedMaterial				= new Material(shaderManager.getShaderTechnique("LambertTexturedTest"), "Textured Material");
		Material* bumpedMaterial				= new Material(shaderManager.getShaderTechnique("PhongBumpmappedTest"), "Bumped Material");
		Material* maskedMaterial				= new Material(shaderManager.getShaderTechnique("BlinnBumpmappedMaskedTest"), "Masked Material");

		Material* phongBlinnParalaxMaterial		= new Material(shaderManager.getShaderTechnique("BlinnParallaxedTest"), "Paralaxed Material");

		Material* staticTessellationMaterial	= new Material(shaderManager.getShaderTechnique("StaticTessallationTest"), "Tessallated Material");
		Material* distanceTessellationMaterial	= new Material(shaderManager.getShaderTechnique("DistanceTessallationTest"), "Distance Tessallated Material");
		Material* vectorTessellationMaterial	= new Material(shaderManager.getShaderTechnique("VectorTessallationTest"), "Vector Tessallated Material");
		
		Material* chestMaterial					= new Material(shaderManager.getShaderTechnique("IblTest"), "Steampunk Chest Material");

		Material* skyboxMaterial				= new Material(shaderManager.getShaderTechnique("SkyboxTest"), "Skybox Material");
		Material* cubemapMaterial				= new Material(shaderManager.getShaderTechnique("CubemapTest"), "Cubemap Material");

		Material* cubemapTexturedMaterial = new Material(shaderManager.getShaderTechnique("CubemapTexturedTest"), "CubemapTextured Material");

		Material* iblMaterial					= new Material(shaderManager.getShaderTechnique("IblTest"), "Ibl Material");

		Material* iblCubemapMaterial = new Material(shaderManager.getShaderTechnique("IblCubemapTest"), "IblCubemap Material");
		#pragma endregion

		#pragma region Loading Textures
		/*********************************
		*
		* Loading textures
		*
		*********************************/

		// TODO: Figure out way that it is not needed.
		QtTextureImporter::instance();
		OpenExrTextureImporter::instance();

		TextureManager& textureManager = TextureManager::instance();

											  textureManager.Load("Default Texture Albedo", "./Assets/Core/DefaultTexture.png");
		Texture* testingTextureNormal		= textureManager.Load("Default Texture Normals", "./Assets/Core/DefaultTexture_NRM.png");

		Texture* testGearTexture			= textureManager.Load("Gears AO", "./Assets/TestAssets/Gear_occlusion.tga");
		Texture* testGearTextureNormal		= textureManager.Load("Gears Normals", "./Assets/TestAssets/Gear_normals.tga");

		Texture* tessDiffTex				= textureManager.Load("Stone Wall Albedo", "./Assets/Core/wall_base.png");
		Texture* tessNrmTex					= textureManager.Load("Stone Wall Normals", "./Assets/Core/wall_normals.png");
		Texture* tessDispTex				= textureManager.Load("Stone Wall Heights", "./Assets/Core/wall_heights.png");

		Texture* tessVecDispTex				= textureManager.Load("Vector Displacement AO", "./Assets/TestAssets/vectorCube_occlusion.tga");
		Texture* tessVecDispTexNRM			= textureManager.Load("Vector Displacment Normals", "./Assets/TestAssets/vectorCube_normals.png");
		Texture* tessVecDispTexDISP_TS		= textureManager.Load("Vector Displacement Directions", "./Assets/TestAssets/vectorCube_2_directions.tga");

		Texture* tgaTest					= textureManager.Load("TGA Test", "./Assets/TestAssets/dickbutt.tga");
		Texture* tgaRleTest					= textureManager.Load("TGA RLE Test", "./Assets/TestAssets/dickbutt_RLE.tga");	//apparently Qt TGA importer doesn't read TGA compressed with RLE.

		Texture* chestDiff					= textureManager.Load("Steampunk Chest Albedo", "./Assets/TestAssets/SteampunkChest_Diffuse.tga");
		Texture* chestNRM					= textureManager.Load("Steampunk Chest Normals", "./Assets/TestAssets/SteampunkChest_NRM.tga");

		CubemapTexture* cubemapTexture = textureManager.Load("Cubemap Test",
			"./Assets/TestAssets/TestSky_Top.exr",
			"./Assets/TestAssets/TestSky_Bottom.exr",
			"./Assets/TestAssets/TestSky_Front.exr",
			"./Assets/TestAssets/TestSky_Back.exr",
			"./Assets/TestAssets/TestSky_Left.exr",
			"./Assets/TestAssets/TestSky_Right.exr"
			);

		//CubemapTexture* cubemapTexture = new CubemapTexture("./Assets/TestAssets/TestSky.exr", "Cubemap Test");

		Texture* skyboxTexture = textureManager.Load("Skybox Texture", "./Assets/TestAssets/TestSky.exr");
		#pragma endregion

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

		#pragma region Setting Material parameters
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

		(*celShadingMaterial)["mat_color"] = textureManager["Default Texture Albedo"];
		//(*celShadingMaterial)["mat_color"] = ReflectionProbeManager::instance().getTexture();

		(*texturedMaterial)["mat_color"] = textureManager["Default Texture Albedo"];

		(*bumpedMaterial)["mat_color"] = textureManager["Default Texture Albedo"];
		(*bumpedMaterial)["mat_normal"] = testingTextureNormal;

		(*maskedMaterial)["mat_color"] = testGearTexture;
		(*maskedMaterial)["mat_normal"] = testGearTextureNormal;

		(*phongBlinnParalaxMaterial)["mat_color"] = tessDiffTex;
		(*phongBlinnParalaxMaterial)["mat_normal"] = tessNrmTex;
		(*phongBlinnParalaxMaterial)["mat_bumpScale"] = new float(0.1f);
		(*phongBlinnParalaxMaterial)["mat_height"] = tessDispTex;

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
		(*chestMaterial)["mat_environmentMap"] = skyboxTexture;

		(*skyboxMaterial)["mat_color"] = skyboxTexture;
		(*cubemapMaterial)["mat_color"] = skyboxTexture;

		(*cubemapTexturedMaterial)["mat_color"] = cubemapTexture;

		//(*iblMaterial)["mat_environmentMap"] = skyboxTexture;
		(*iblMaterial)["mat_environmentMap"] = ReflectionProbeManager::instance().getTexture();
		(*iblMaterial)["mat_color"] = textureManager["Default Texture Albedo"];
		(*iblMaterial)["mat_normal"] = testingTextureNormal;
		(*iblMaterial)["mat_specularExponent"] = new float(40.0f);

		(*iblCubemapMaterial)["mat_environmentMap"] = cubemapTexture;
		(*iblCubemapMaterial)["mat_color"] = textureManager["Default Texture Albedo"];
		(*iblCubemapMaterial)["mat_normal"] = testingTextureNormal;
		(*iblCubemapMaterial)["mat_specularExponent"] = new float(20.0f);
		#pragma endregion

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

		#pragma region Creating and loading Models
		/*********************************
		*
		* Creating and loading models
		*
		*********************************/

		//initialization of model importers
		AssimpModelImporter::instance();
		FbxModelImporter::instance();

		ModelBuilder& modelBuilder = ModelBuilder::instance();
		ModelManager& modelManager = ModelManager::instance();

		AbstractModelBuilder* triangleBuilder = static_cast<TriangleModelBuilder*>(modelBuilder.getModelBuilder("Triangle"));
		triangleBuilder->setParameter("name", QString("Triangle"));
		triangleBuilder->Build();

		PlaneModelBuilder planeBuilder = PlaneModelBuilder();
		planeBuilder.setParameter("name", QString("Plane"));
		planeBuilder.setParameter("size X", float(10.0f));
		planeBuilder.setParameter("size Y", float(10.0f));
		planeBuilder.setParameter("subdivisions X", int(50));
		planeBuilder.setParameter("subdivisions Y", int(50));
		planeBuilder.setParameter("tiled", true);
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

		SphereModelBuilder skyboxBuilder = SphereModelBuilder();
		skyboxBuilder.setParameter("name", "Skybox");
		skyboxBuilder.setParameter("radius", 60.0f);
		skyboxBuilder.setParameter("backfacing", true);
		skyboxBuilder.Build();

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
		#pragma endregion

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

		#pragma region Setting Post Processing
		ShaderTechnique* screenTechnique = new ShaderTechnique("Screen", &CommonMeshShaderBuilder::instance());
		screenTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		screenTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		screenTechnique->setInput("Surface Shader", "./Shader Files/SurfaceShaders/Tests/LUTColorGrading.glsl");

		ShaderTechnique* screenTechniquePostProcess = new ShaderTechnique("Screen PP", screenTechnique->getShader(), "PostProcess");

		Texture* LutTestTexture = textureManager.Load("LUT test", "./Assets/TestAssets/TestLUT.tga");
		//Texture* LutTestTexture = textureManager.Load("LUT test", "./Assets/Core/DefaultColorLUT.tga");
		LutTestTexture->setWrapping(GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
		LutTestTexture->setFiltering(GL_NEAREST, GL_NEAREST);

		Material* screenMaterial = new Material(shaderManager.getShaderTechnique("Screen PP"), "Screen Material");
		(*screenMaterial)["mat_emissive"] = textureManager["Screen Color Pass"];
		//(*screenMaterial)["mat_emissive"] = textureManager["Default Texture Albedo"];
		(*screenMaterial)["mat_usesEmissive"] = new bool(true);
		(*screenMaterial)["mat_LUT"] = textureManager["LUT test"];

		PlaneModelBuilder screenBuilder = PlaneModelBuilder();
		screenBuilder.setParameter("name", QString("Screen"));
		screenBuilder.setParameter("size X", 2.0f);
		screenBuilder.setParameter("size Y", 2.0f);
		screenBuilder.setParameter("backfacing", true);
		screenBuilder.setParameter("plane", PlaneDirections::XY);
		screenBuilder.Build();

		Entity* screenEntity = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* screenEntityModelC = new ModelComponent(screenEntity, screenMaterial, ModelManager::instance()["Screen"]);
		screenEntity->name = QString("Screen Entity");
		level->getRoot()->AttachSubobject(screenEntity);
		#pragma endregion

		#pragma region Reflection Probe

		// TODO: make it more universal.

		ShaderTechnique* reflectionBlendingTechnique = new ShaderTechnique("Reflection Blending", &CommonMeshShaderBuilder::instance());
		reflectionBlendingTechnique->setInput("Vertex Shader", "./Shader Files/Mesh/ObjectSpaceMesh.glsl");
		reflectionBlendingTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/UnlitLightingModel.glsl");
		reflectionBlendingTechnique->setInput("Surface Shader", "./Shader Files/Lighting/ReflectionProbes/PoiReflectionBlend.glsl");

		ShaderTechnique* reflectionBlendingTechnique2 = new ShaderTechnique("Reflection Blending 2", reflectionBlendingTechnique->getShader(), "ReflectionPOI");

		Material* reflectionBlendingMaterial = new Material(shaderManager.getShaderTechnique("Reflection Blending 2"), "Reflection Blending Material");
		
		PlaneModelBuilder FrameBuilder = PlaneModelBuilder();
		FrameBuilder.setParameter("name", QString("Frame"));
		FrameBuilder.setParameter("size X", 2.0f);
		FrameBuilder.setParameter("size Y", 2.0f);
		FrameBuilder.setParameter("backfacing", true);
		FrameBuilder.setParameter("plane", PlaneDirections::XY);
		FrameBuilder.Build();

		Entity* reflectionEntity = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* reflectionEntityModelC = new ModelComponent(reflectionEntity, reflectionBlendingMaterial, ModelManager::instance()["Frame"]);
		reflectionEntity->name = QString("POI Reflection Blending Entity");
		level->getRoot()->AttachSubobject(reflectionEntity);

		#pragma endregion

		#pragma region Creating scene objects
		/*********************************
		*
		* Creating scene objects
		*
		*********************************/

		Entity* phongExample = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* phongModelC = new ModelComponent(phongExample, iblMaterial, modelManager["Sphere"]);
		phongExample->name = QString("Phong Example");
		level->getRoot()->AttachSubobject(phongExample);

		Entity* phongBlinnExample = new Entity(glm::vec3(4.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* phongBlinnModelC = new ModelComponent(phongBlinnExample, phongBlinnMaterial, modelManager.getModel("Sphere"));
		phongBlinnExample->name = QString("Blinn-Phong Example");
		level->getRoot()->AttachSubobject(phongBlinnExample);

		Entity* BumpMapExample = new Entity(glm::vec3(8.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* bumpMapModelC = new ModelComponent(BumpMapExample, iblCubemapMaterial, modelManager.getModel("TestModel2"));
		BumpMapExample->name = QString("Bump mapping Example");
		level->getRoot()->AttachSubobject(BumpMapExample);

		Entity* MaskedExample = new Entity(glm::vec3(12.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* maskedModelC = new ModelComponent(MaskedExample, maskedMaterial, modelManager.getModel("Box"));
		MaskedExample->name = QString("Masked blend mode Example");
		level->getRoot()->AttachSubobject(MaskedExample);

		Entity* ParralaxExample = new Entity(glm::vec3(16.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* parralaxModelC = new ModelComponent(ParralaxExample, phongBlinnParalaxMaterial, modelManager.getModel("Teapot"));
		ParralaxExample->name = QString("Displacement Mapping Example");
		level->getRoot()->AttachSubobject(ParralaxExample);

		Entity* CookTorranceExample = new Entity(glm::vec3(20.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* cookTorranceModelC = new ModelComponent(CookTorranceExample, cookTorranceMaterial, modelManager.getModel("Sphere"));
		CookTorranceExample->name = QString("Cook-Torrance Example");
		level->getRoot()->AttachSubobject(CookTorranceExample);

		Entity* StraussExample = new Entity(glm::vec3(24.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* straussModelC = new ModelComponent(StraussExample, straussMaterial, modelManager.getModel("Sphere"));
		StraussExample->name = QString("Strauss Example");
		level->getRoot()->AttachSubobject(StraussExample);

		Entity* StraussConductiveExample = new Entity(glm::vec3(28.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* straussConductiveModelC = new ModelComponent(StraussConductiveExample, straussMaterialMetalic, modelManager.getModel("Sphere"));
		StraussConductiveExample->name = QString("Strauss Metalic Example");
		level->getRoot()->AttachSubobject(StraussConductiveExample);

		Entity* WardExample = new Entity(glm::vec3(32.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* wardModelC = new ModelComponent(WardExample, wardIsoMaterial, modelManager.getModel("TestModel2"));
		WardExample->name = QString("Ward Example");
		level->getRoot()->AttachSubobject(WardExample);

		Entity* WardAnisotropicExample = new Entity(glm::vec3(36.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* wardAnisoModelC = new ModelComponent(WardAnisotropicExample, wardAnisoMaterial, modelManager.getModel("TestModel2"));
		WardAnisotropicExample->name = QString("Ward Anisotropic Example");
		level->getRoot()->AttachSubobject(WardAnisotropicExample);

		Entity* DistanceTessellationExample = new Entity(glm::vec3(40.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* distanceTessModelC = new ModelComponent(DistanceTessellationExample, distanceTessellationMaterial, modelManager.getModel("BoxDense"));
		DistanceTessellationExample->name = QString("Distance Tessellation Example");
		level->getRoot()->AttachSubobject(DistanceTessellationExample);

		Entity* VectorTessellationExample = new Entity(glm::vec3(44.0f, 0.0f, 0.0f));
		VectorTessellationExample->transform.LocalRotate(glm::angleAxis(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f)));
		ModelComponent* vectorTessModelC = new ModelComponent(VectorTessellationExample, vectorTessellationMaterial, modelManager.getModel("VectorCube"));
		VectorTessellationExample->name = QString("Vector Displacement Tessellation Example");
		level->getRoot()->AttachSubobject(VectorTessellationExample);

		Entity* FbxExample = new Entity(glm::vec3(48.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(0.2f, 0.2f, 0.2f));
		ModelComponent* FbxExampleModelC = new ModelComponent(FbxExample, chestMaterial, modelManager.getModel("FbxChest"));
		FbxExample->name = QString("FBX import Example");
		level->getRoot()->AttachSubobject(FbxExample);

		Entity* FbxExample2 = new Entity(glm::vec3(52.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* FbxExample2ModelC = new ModelComponent(FbxExample2, phongMaterial, modelManager.getModel("FbxTest2"));
		FbxExample2->name = QString("FBX Example 2");
		level->getRoot()->AttachSubobject(FbxExample2);

		Entity* FbxExample3 = new Entity(glm::vec3(60.0f, 0.0f, 0.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		ModelComponent* FbxExample3ModelC = new ModelComponent(FbxExample3, phongMaterial, modelManager.getModel("FbxTest4"));
		FbxExample3->name = QString("FBX Hierarchy Example");
		level->getRoot()->AttachSubobject(FbxExample3);

		Entity* mainCamera = new Entity(glm::vec3(0.0f, 0.0f, 5.0f), glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		CameraComponent* mainCameraComponent = new CameraComponent(mainCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		mainCamera->name = QString("Main Camera");
		TempPlayerComponent* cameraController = new TempPlayerComponent(mainCamera);
		level->getRoot()->AttachSubobject(mainCamera);
		//Entity* spotLight2 = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(), glm::vec3(0.4f, 0.4f, 0.4f));
		SpotLightComponent* spotLightComponent2 = new SpotLightComponent(mainCamera, glm::vec3(0.6f, 0.9f, 1.0f), 0.5f, 70.0f, 1.0f, 25.0f, 0.0f);
		//TempMovingComponent* spotLightMoveComponent2 = new TempMovingComponent(mainCamera, glm::vec3(60.0f, 2.2f, 0.0f), glm::vec3(0.0f, 2.2f, 0.0f), 20.0f);
		//ModelComponent* spotLightMarker2 = new ModelComponent(mainCamera, phongMaterial, modelManager.getModel("Cone"));
		//spotLight2->name = QString("Spot Light2");
		//level->getRoot()->AttachSubobject(spotLight2);

		Entity* lightModelTestingCamera = new Entity(glm::vec3(5.0f, 5.0f, 5.0f), glm::angleAxis(180.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
		CameraComponent* lightModelTestingCameraComponent = new CameraComponent(lightModelTestingCamera, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 40.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		lightModelTestingCamera->name = QString("Light Model Testing Camera");
		level->getRoot()->AttachSubobject(lightModelTestingCamera);

		Entity* pointLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::quat(), glm::vec3(0.4f, 0.4f, 0.4f));
		PointLightComponent* pointLightComponent = new PointLightComponent(pointLight, glm::vec3(1.0f, 0.2f, 1.0f), 0.8f, 18.0f, 1.0f);
		TempMovingComponent* pointLightMoveComponent = new TempMovingComponent(pointLight, glm::vec3(60.0f, -0.2f, 3.0f), glm::vec3(0.0f, -0.2f, 3.0f), 15.0f);
		ModelComponent* pointLightMarker = new ModelComponent(pointLight, phongMaterial, modelManager.getModel("Sphere"));
		pointLight->name = QString("Point Light");
		level->getRoot()->AttachSubobject(pointLight);

		Entity* spotLight = new Entity(glm::vec3(5.0f, 2.0f, -5.0f), glm::angleAxis(270.0f, glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(0.4f, 0.4f, 0.4f));
		SpotLightComponent* spotLightComponent = new SpotLightComponent(spotLight, glm::vec3(1.0f, 0.2f, 0.1f), 1.5f, 40.0f);
		TempMovingComponent* spotLightMoveComponent = new TempMovingComponent(spotLight, glm::vec3(60.0f, 2.2f, 0.0f), glm::vec3(0.0f, 2.2f, 0.0f), 20.0f);
		ModelComponent* spotLightMarker = new ModelComponent(spotLight, phongMaterial, modelManager.getModel("Cone"));
		spotLight->name = QString("Spot Light");
		level->getRoot()->AttachSubobject(spotLight);

		Entity* ground = new Entity(glm::vec3(30.0f, -10.0f, 0.0f), glm::quat(), glm::vec3(15.0f));
		ModelComponent* groundModel = new ModelComponent(ground, phongBlinnParalaxMaterial, modelManager.getModel("Plane"));
		ground->name = QString("Ground");
		level->getRoot()->AttachSubobject(ground);

		Entity* skybox = new Entity(glm::vec3(30.0f, 0.0f, 0.0f));
		ModelComponent* skyboxModel = new ModelComponent(skybox, skyboxMaterial, modelManager.getModel("Skybox"));
		skybox->name = "Skybox";
		level->getRoot()->AttachSubobject(skybox);
		#pragma endregion

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
		FbxExample2ModelC->lightedBy.append(pointLightComponent);
		FbxExample3ModelC->lightedBy.append(pointLightComponent);

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
		FbxExample2ModelC->lightedBy.append(spotLightComponent);
		FbxExample3ModelC->lightedBy.append(spotLightComponent);

		phongModelC->lightedBy.append(spotLightComponent2);
		phongBlinnModelC->lightedBy.append(spotLightComponent2);
		bumpMapModelC->lightedBy.append(spotLightComponent2);
		maskedModelC->lightedBy.append(spotLightComponent2);
		parralaxModelC->lightedBy.append(spotLightComponent2);
		cookTorranceModelC->lightedBy.append(spotLightComponent2);
		straussModelC->lightedBy.append(spotLightComponent2);
		straussConductiveModelC->lightedBy.append(spotLightComponent2);
		wardModelC->lightedBy.append(spotLightComponent2);
		wardAnisoModelC->lightedBy.append(spotLightComponent2);
		distanceTessModelC->lightedBy.append(spotLightComponent2);
		vectorTessModelC->lightedBy.append(spotLightComponent2);
		FbxExampleModelC->lightedBy.append(spotLightComponent2);
		FbxExample2ModelC->lightedBy.append(spotLightComponent2);
		FbxExample3ModelC->lightedBy.append(spotLightComponent2);

		#pragma region Loading defined level into the scene or loading scene from file
		scene->LoadLevel(level, "TestLevel");
		scene->setCurrentCamera(mainCameraComponent);
		//scene->setCurrentCamera(lightModelTestingCameraComponent);
		scene->mainLight = new DirectionalLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.6, 1.0), 1.0f);
		AmbientLightComponent* ambientLight = new AmbientLightComponent(level->getRoot(), glm::vec3(1.0f), 0.2f);

		//scene->LoadLevel(FbxLevelImporter::instance().Load("Sponza", "./Assets/Levels/Sponza/Sponza.fbx"), "Sponza");
		//scene->LoadLevel(FbxLevelImporter::instance().Load("TransformTest", "./Assets/Levels/TransformTest/TransformTest4.fbx"), "TransformTest");
		scene->LoadLevel(FbxLevelImporter::instance().Load("MaterialTest", "./Assets/Levels/MaterialTest/MaterialTest1b.fbx"), "MaterialTest");
		scene->LoadLevel(FbxLevelImporter::instance().Load("TransformTest", "./Assets/Levels/SpecialObjectsTest/ReflectionProbesTest.fbx"), "ReflectionProbesTest");
		#pragma endregion

		phongModelC->lightedBy.append(scene->mainLight);
		phongBlinnModelC->lightedBy.append(scene->mainLight);
		//bumpMapModelC->lightedBy.append(scene->mainLight);
		maskedModelC->lightedBy.append(scene->mainLight);
		parralaxModelC->lightedBy.append(scene->mainLight);
		cookTorranceModelC->lightedBy.append(scene->mainLight);
		straussModelC->lightedBy.append(scene->mainLight);
		straussConductiveModelC->lightedBy.append(scene->mainLight);
		wardModelC->lightedBy.append(scene->mainLight);
		wardAnisoModelC->lightedBy.append(scene->mainLight);
		distanceTessModelC->lightedBy.append(scene->mainLight);
		vectorTessModelC->lightedBy.append(scene->mainLight);
		//FbxExampleModelC->lightedBy.append(scene->mainLight);
		FbxExample2ModelC->lightedBy.append(scene->mainLight);
		FbxExample3ModelC->lightedBy.append(scene->mainLight);
		//skyboxModel->lightedBy.append(scene->mainLight);

		phongModelC->lightedBy.append(ambientLight);
		phongBlinnModelC->lightedBy.append(ambientLight);
		//bumpMapModelC->lightedBy.append(ambientLight);
		maskedModelC->lightedBy.append(ambientLight);
		parralaxModelC->lightedBy.append(ambientLight);
		cookTorranceModelC->lightedBy.append(ambientLight);
		straussModelC->lightedBy.append(ambientLight);
		straussConductiveModelC->lightedBy.append(ambientLight);
		wardModelC->lightedBy.append(ambientLight);
		wardAnisoModelC->lightedBy.append(ambientLight);
		distanceTessModelC->lightedBy.append(ambientLight);
		vectorTessModelC->lightedBy.append(ambientLight);
		//FbxExampleModelC->lightedBy.append(ambientLight);
		FbxExample2ModelC->lightedBy.append(ambientLight);
		FbxExample3ModelC->lightedBy.append(ambientLight);
		//skyboxModel->lightedBy.append(ambientLight);

		//qDebug() << QJsonDocument(level->toJSON()).toJson();
	}

}