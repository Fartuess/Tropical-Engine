#include <QtCore/qmap.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qfile.h>
#include <QtCore/qjsondocument.h>

#include <fbxsdk/core/base/fbxstring.h>

#include <Scene/LevelImporter/FbxLevelImporter.h>

#include <Scene/LevelManager.h>

#include <Model/Model.h>
#include <Model/ModelImporter/FbxModelImporter.h>
#include <Model/ModelComponent.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>
#include <Shader/ShaderBuilder/CommonMeshShaderBuilder.h>
#include <Shader/Material.h>
#include <Shader/ShaderManager.h>

#include <Package/AssetManager.h>

#include <Texture/Texture.h>
#include <Texture/TextureManager.h>

#include <Light/DirectionalLightComponent.h>
#include <Light/AmbientLightComponent.h>

#include <ReflectionProbe/ReflectionProbeComponent.h>

#include <QtCore/qdebug.h>

namespace TropicalEngine
{

	FbxLevelImporter::FbxLevelImporter()
	{
		SdkManager = FbxManager::Create();
		IOSettings = FbxIOSettings::Create(SdkManager, IOSROOT);
		Converter = new FbxGeometryConverter(SdkManager);

		supportedExtensions << "fbx";

		LevelManager::AddImporter(this);
	}


	FbxLevelImporter::~FbxLevelImporter()
	{
	}

	Level* FbxLevelImporter::Load(QString name, QString fileUrl)
	{
		Level* level = new Level(name);

		FbxImporter* Importer = FbxImporter::Create(SdkManager, "");

		// Temporary?

		ShaderTechnique* phongTechnique = new ShaderTechnique("Phong Default", &CommonMeshShaderBuilder::instance());
		phongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");

		Material* defaultMaterial = new Material(phongTechnique, "defaultMaterial");

		DirectionalLightComponent* mainLight = nullptr;

		AmbientLightComponent* ambientLight = nullptr;

		if (Importer->Initialize(fileUrl.toStdString().c_str(), -1, SdkManager->GetIOSettings()))
		{
			FbxScene* scene = FbxScene::Create(SdkManager, "Importing Scene");
			Importer->Import(scene);
			Converter->Triangulate(scene, true);
			if (Converter->SplitMeshesPerMaterial(scene, true) == false)
			{
				qDebug() << "Not all meshes were sucessfully splitted";
			}

			QList<FbxNode*> helper;
			QMap<FbxNode*, Entity*> objects;
			QMap<FbxMesh*, Model*> meshes;
			QList<ModelComponent*> modelComponents;
			QMap<FbxSurfaceMaterial*, Material*> materials;

			helper.append(scene->GetRootNode());

			while (!helper.isEmpty())
			{
				FbxNode* it = helper.takeFirst();

				for (int i = 0; i < it->GetChildCount(); i++)
				{
					helper.append(it->GetChild(i));
				}

				FbxDouble3 _translation = it->LclTranslation.Get();
				FbxDouble3 _scalingPivot = it->ScalingPivot.Get();
				FbxDouble3 _scalingOffset = it->ScalingOffset.Get();
				FbxDouble3 _rotationPivot = it->RotationPivot.Get();
				FbxDouble3 _rotationOffset = it->RotationOffset.Get();

				FbxDouble3 _rotation = it->LclRotation.Get();
				FbxDouble3 _scaling = it->LclScaling.Get();

				FbxEuler::EOrder rotationOrder = it->RotationOrder.Get();

				glm::quat rotation;
				glm::quat rotationX = glm::angleAxis((float)(_rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
				glm::quat rotationY = glm::angleAxis((float)(_rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
				glm::quat rotationZ = glm::angleAxis((float)(_rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));

				switch (rotationOrder)
				{
					case FbxEuler::EOrder::eOrderXYZ:
						rotation = rotationZ * rotationY * rotationX;
						break;
					case FbxEuler::EOrder::eOrderXZY:
						rotation = rotationY * rotationZ * rotationX;
						break;
					case FbxEuler::EOrder::eOrderYXZ:
						rotation = rotationZ * rotationX * rotationY;
						break;
					case FbxEuler::EOrder::eOrderYZX:
						rotation = rotationX * rotationZ * rotationY;
						break;
					case FbxEuler::EOrder::eOrderZXY:
						rotation = rotationY * rotationX * rotationZ;
						break;
					case FbxEuler::EOrder::eOrderZYX:
						rotation = rotationX * rotationY * rotationZ;
						break;
				}

				glm::vec3 scale = glm::vec3(_scaling[0], _scaling[1], _scaling[2]);

				glm::vec3 rotationPivot = glm::vec3(_rotationPivot[0], _rotationPivot[1], _rotationPivot[2]);
				glm::vec3 scalingPivot = glm::vec3(_scalingPivot[0], _scalingPivot[1], _scalingPivot[2]);

				glm::vec3 translation =
					glm::vec3(_translation[0], _translation[1], _translation[2])
					
					- glm::vec3((glm::mat4_cast(rotation) * glm::vec4((rotationPivot * scale), 1.0f) - glm::vec4(rotationPivot * scale, 0.0f)))
				
					+ glm::vec3(scalingPivot)
					- (glm::vec3(scalingPivot) * scale)
					
					+ (glm::vec3(_rotationOffset[0], _rotationOffset[1], _rotationOffset[2]) * scale)

					+ (glm::vec3(_scalingOffset[0], _scalingOffset[1], _scalingOffset[2]))
					;

				#pragma region Debug
				/*
				{
					FbxDouble3 _translation = it->LclTranslation.Get();
					FbxDouble3 _rotationOffset = it->RotationOffset.Get();
					FbxDouble3 _rotationPivot = it->RotationPivot.Get();
					FbxDouble3 _preRotation = it->PreRotation.Get();
					FbxDouble3 _rotation = it->LclRotation.Get();
					FbxDouble3 _postRotation = it->PostRotation.Get();
					FbxDouble3 _scalingOffset = it->ScalingOffset.Get();
					FbxDouble3 _scalingPivot = it->ScalingPivot.Get();
					FbxDouble3 _scaling = it->LclScaling.Get();

					FbxDouble4 _geometricTranslation = it->GetGeometricTranslation(FbxNode::eSourcePivot);
					FbxDouble4 _geometricRotation = it->GetGeometricRotation(FbxNode::eSourcePivot);
					FbxDouble4 _geometricScaling = it->GetGeometricScaling(FbxNode::eSourcePivot);

					FbxDouble3 _zero = FbxDouble3(0.0f, 0.0f, 0.0f);
					FbxDouble4 _zero4 = FbxDouble4(0.0f, 0.0f, 0.0f, 1.0f);
					FbxDouble4 _one4 = FbxDouble4(1.0f, 1.0f, 1.0f, 1.0f);

					if (_rotationOffset != _zero
						|| _preRotation != _zero
						|| _postRotation != _zero
						|| _scalingOffset != _zero
						|| _rotationPivot != _scalingPivot
						|| _geometricTranslation != _zero4
						|| _geometricRotation != _zero4
						|| _geometricScaling != _one4
						)
					{
						qDebug() << "----------------------------";
						qDebug() << QString(it->GetName());
						qDebug() << "Translation: " << _translation[0] << " " << _translation[1] << " " << _translation[2];
						qDebug() << "Rotation Offset: " << _rotationOffset[0] << " " << _rotationOffset[1] << " " << _rotationOffset[2];
						qDebug() << "Rotation Pivot: " << _rotationPivot[0] << " " << _rotationPivot[1] << " " << _rotationPivot[2];
						qDebug() << "Pre-rotation: " << _preRotation[0] << " " << _preRotation[1] << " " << _preRotation[2];
						qDebug() << "Rotation: " << _rotation[0] << " " << _rotation[1] << " " << _rotation[2];
						qDebug() << "Post-rotation: " << _postRotation[0] << " " << _postRotation[1] << " " << _postRotation[2];
						//inverse of rotation pivot
						qDebug() << "Scaling Offset: " << _scalingOffset[0] << " " << _scalingOffset[1] << " " << _scalingOffset[2];
						qDebug() << "Scaling Pivot: " << _scalingPivot[0] << " " << _scalingPivot[1] << " " << _scalingPivot[2];
						qDebug() << "Scaling: " << _scaling[0] << " " << _scaling[1] << " " << _scaling[2];
						//inverse of scaling pivot
						qDebug() << "GEOMETRIC:";
						qDebug() << "Geometric Translation: " << _geometricTranslation[0] << " " << _geometricTranslation[1] << " " << _geometricTranslation[2];
						qDebug() << "Geometric Rotation: " << _geometricRotation[0] << " " << _geometricRotation[1] << " " << _geometricRotation[2];
						qDebug() << "Geometric Scaling" << _geometricScaling[0] << " " << _geometricScaling[1] << " " << _geometricScaling[2];

					}
				}
				*/
				#pragma endregion

				Entity* object = new Entity();
				object->name = QString(it->GetName());

				object->transform.Translate(translation);
				object->transform.Rotate(rotation);
				object->transform.Scale(scale);

				objects[it] = object;

				int meshCounter = 0;
				
				

				FbxProperty specialTypeName = it->FindProperty("TropicalEngineType");

				#pragma region Attribute collecting
				//QMap<QString, FbxNodeAttribute*> attributes;
				//for (int i = 0; i < it->GetNodeAttributeCount(); i++)
				//{
				//	FbxNodeAttribute* nodeAttribute = it->GetNodeAttributeByIndex(i);
				//	QString attributeName = QString(nodeAttribute->GetName());
				//	attributes[attributeName] = nodeAttribute;
				//}
				#pragma endregion

				#pragma region Handling Special Objects

				if (specialTypeName.IsValid())
				{
					if (specialTypeName.Get<FbxString>() == FbxString("ReflectionProbe"))
					{
						float radius = it->FindProperty("Radius").Get<FbxDouble>();
						float strength = it->FindProperty("InfluenceIntensity").Get<FbxDouble>();
						float attenuation = it->FindProperty("InfluenceAttenuation").Get<FbxDouble>();

						QString texturePath = QString((const char*)it->FindProperty("TexturePath").Get<FbxString>());

						QString textureName = texturePath.section(".", -2, -2).section("/", -1);

						Texture* texture;
						if (TextureManager::instance().hasTexture(textureName))
						{
							texture = TextureManager::instance()[textureName];
						}
						else
						{
							texture = TextureManager::instance().Load(textureName, texturePath);
						}

						ReflectionProbeComponent* reflectionProbeComponent = new ReflectionProbeComponent(object, texture ,radius, strength, attenuation);
					}
				}
				#pragma endregion

				#pragma region Handling Standard Objects
				else
				{

					for (int i = 0; i < it->GetNodeAttributeCount(); i++)
					{
						FbxNodeAttribute* nodeAttribute = it->GetNodeAttributeByIndex(i);

						switch (nodeAttribute->GetAttributeType())
						{
						case FbxNodeAttribute::EType::eMesh:
						{
							// Temporary solution creates separate meshes and mesh components instead of single mesh with multiple mesh entires.

							FbxMesh* mesh = (FbxMesh*)nodeAttribute;
							QString meshName = QString(mesh->GetName());
							if (meshes.contains(mesh) == false)
							{
								meshes[mesh] = FbxModelImporter::instance().Load(meshName, mesh);
							}

							int materialId = qMin(meshCounter, it->GetMaterialCount() - 1);
							FbxSurfaceMaterial* _material = it->GetMaterial(materialId);
							meshCounter++;

							Material* material = defaultMaterial;
							if (materials.contains(_material) == false)
							{
								QString _materialName = QString(_material->GetName());
								QStringList _materialNameSplitted = _materialName.split("_");

								bool bShaderTechniqueExists = false;
								ShaderTechnique* shaderTechnique;
								if (ShaderManager::instance().containsShaderTechnique(_materialNameSplitted[0]))
								{
									shaderTechnique = ShaderManager::instance().getShaderTechnique(_materialNameSplitted[0]);
									bShaderTechniqueExists = true;
								}
								else
								{
									QByteArray fileContents;
									QJsonObject JSON;

									if (QFileInfo(fileUrl.section("/", 0, -2) + "/" + _materialNameSplitted[0] + ".tasset").exists())
									{
										QFile shaderTechniqueFile(fileUrl.section("/", 0, -2) + "/" + _materialNameSplitted[0] + ".tasset");
										shaderTechniqueFile.open(QIODevice::ReadOnly);
										fileContents = shaderTechniqueFile.readAll();
										bShaderTechniqueExists = true;
									}
									else if (QFileInfo("./Assets/Shaders/" + _materialNameSplitted[0] + ".tasset").exists())
									{
										QFile shaderTechniqueFile("./Assets/Shaders/" + _materialNameSplitted[0] + ".tasset");
										shaderTechniqueFile.open(QIODevice::ReadOnly);
										fileContents = shaderTechniqueFile.readAll();
										bShaderTechniqueExists = true;
									}
									if (bShaderTechniqueExists)
									{
										QJsonDocument JSONDocument = QJsonDocument::fromJson(fileContents);
										if (!JSONDocument.isNull())
										{
											JSON = JSONDocument.object();
										}
										else
										{
											// TODO: Make this exception more reasonable looking.
											throw Exception<void>("Shader Technique File couldn't be parsed as JSON properly.", 0);
										}

										ShaderTechnique::InitializeType();
										shaderTechnique = (ShaderTechnique*)AssetManager::instance().getTypeHandle("ShaderTechnique")->fromJSON(JSON);
									}
								}
								if (bShaderTechniqueExists)
								{
									material = new Material(shaderTechnique, _materialNameSplitted[1]);
								}

								FbxProperty& itProperty = _material->GetFirstProperty();

								while (itProperty.IsValid())
								{
									QStringList parameterNameSplitted = QString(itProperty.GetName()).split("_");

									if (parameterNameSplitted[0] == "mat")
									{
										if (material->hasParameter("mat_" + parameterNameSplitted[1]))
										{
											// TODO: Check if types are correct otherwise in some cases dung can hit the fan.
											if (parameterNameSplitted[2] == "float")
											{
												float* value = new float(itProperty.Get<FbxDouble>());

												(*material)["mat_" + parameterNameSplitted[1]] = value;
											}
											else if (parameterNameSplitted[2] == "vector2")
											{
												FbxDouble2 _vector2 = itProperty.Get<FbxDouble2>();
												glm::vec2* vector2 = new glm::vec2(_vector2[0], _vector2[1]);

												(*material)["mat_" + parameterNameSplitted[1]] = vector2;
											}
											else if (parameterNameSplitted[2] == "vector3")
											{
												FbxDouble3 _vector3 = itProperty.Get<FbxDouble3>();
												glm::vec3* vector3 = new glm::vec3(_vector3[0], _vector3[1], _vector3[2]);

												(*material)["mat_" + parameterNameSplitted[1]] = vector3;
											}
											else if (parameterNameSplitted[2] == "texture")
											{
												QString texturePath = QString((const char*)itProperty.Get<FbxString>());

												QString textureName = texturePath.section(".", -2, -2).section("/", -1);

												Texture* texture;
												if (TextureManager::instance().hasTexture(textureName))
												{
													texture = TextureManager::instance()[textureName];
												}
												else
												{
													texture = TextureManager::instance().Load(textureName, texturePath);
												}

												(*material)["mat_" + parameterNameSplitted[1]] = texture;

												// TODO: This is temporary.
												if (parameterNameSplitted[1] == "specularTexture")
												{
													(*material)["mat_specularUsesTexture"] = new bool(true);
												}

												// TODO: This is temporary.
												if (parameterNameSplitted[1] == "mask")
												{
													(*material)["mat_maskSeparateTexture"] = new bool(true);
												}
											}
										}
									}

									itProperty = _material->GetNextProperty(itProperty);
								}

								materials[_material] = material;
							}
							else
							{
								material = materials[_material];
							}

							ModelComponent* modelC = new ModelComponent(object, material, meshes[mesh]);

							modelComponents.push_back(modelC);

							break;
						}
						case FbxNodeAttribute::EType::eLight:
						{
							// TODO: Add support of point lights and spot lights.

							FbxLight* light = (FbxLight*)nodeAttribute;

							switch (light->LightType)
							{
							case FbxLight::EType::eDirectional:
							{
								FbxDouble3 _lightColor = light->Color.Get();
								glm::vec3 lightColor = glm::vec3(_lightColor[0], _lightColor[1], _lightColor[2]);

								float lightBrightness = light->Intensity.Get() / 100.0f;

								bool lightCastShadows = light->CastShadows.Get();

								// TODO: Figure out how to handle cases with multiple directional lights in the scene.
								if (mainLight == nullptr)
								{
									mainLight = new DirectionalLightComponent(object, lightColor, -object->transform.getFront(), lightBrightness, lightCastShadows);
								}

								break;
							}
							case FbxLight::EType::ePoint:
							{
								FbxDouble3 _lightColor = light->Color.Get();
								glm::vec3 lightColor = glm::vec3(_lightColor[0], _lightColor[1], _lightColor[2]);

								float lightBrightness = light->Intensity.Get() / 100.0f;

								// FBX exporter converts ambient light into point light
								if (light->DecayType.Get() == FbxLight::EDecayType::eNone)
								{
									if (ambientLight == nullptr)
									{
										ambientLight = new AmbientLightComponent(object, lightColor, lightBrightness);
									}
								}
								break;
							}
							default:
								break;
							}

							break;
						}
						default:
							break;
						}
					}
				}
				#pragma endregion

				if (it->GetParent() != NULL)
				{
					object->AttachTo(objects[it->GetParent()]);
				}
				else
				{
					object->AttachTo(level->getRoot());
				}
			}

			if (mainLight == nullptr)
			{
				mainLight = new DirectionalLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.6, 1.0), 1.0f);
				ambientLight = new AmbientLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 1.0f), 0.2f);
			}

			for (ModelComponent* modelC : modelComponents)
			{
				modelC->lightedBy.append(mainLight);
				if (ambientLight != nullptr)
				{
					modelC->lightedBy.append(ambientLight);
				}
			}
		}
		else
		{
			qDebug() << "Call to FbxImporter::Initialize() failed. Error returned: " + QString(Importer->GetStatus().GetErrorString());
			return nullptr;
		}

		Importer->Destroy();

		return level;
	}
}