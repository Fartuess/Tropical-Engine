#include <QtCore/qmap.h>

#include <Scene/LevelImporter/FbxLevelImporter.h>

#include <Scene/LevelManager.h>

#include <Model/Model.h>
#include <Model/ModelImporter/FbxModelImporter.h>
#include <Model/ModelComponent.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>
#include <Shader/ShaderBuilder/CommonMeshShaderBuilder.h>
#include <Shader/Material.h>

#include <Light/DirectionalLightComponent.h>

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

		ShaderTechnique* phongTechnique = new ShaderTechnique("Phong", &CommonMeshShaderBuilder::instance());
		phongTechnique->setInput("Lighting Model", "./Shader Files/LightingModels/PhongLightingModel.glsl");

		Material* defaultMaterial = new Material(phongTechnique, "defaultMaterial");

		// TODO: Remove this temp stuff.
		DirectionalLightComponent* mainLight = new DirectionalLightComponent(level->getRoot(), glm::vec3(1.0f, 1.0f, 0.9f), glm::vec3(0.5, 0.6, 1.0), 1.0f);

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

				for (int i = 0; i < it->GetNodeAttributeCount(); i++)
				{
					FbxNodeAttribute* nodeAttribute = it->GetNodeAttributeByIndex(i);
					if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
					{
						// Temporary solution creates separate meshes and mesh components instead of single mesh with multiple mesh entires.

						FbxMesh* mesh = (FbxMesh*)nodeAttribute;
						QString meshName = QString(mesh->GetName());
						if (meshes.contains(mesh) == false)
						{
							meshes[mesh] = FbxModelImporter::instance().Load(meshName, mesh);
						}
						ModelComponent* modelC = new ModelComponent(object, defaultMaterial, meshes[mesh]);

						// TODO: Remove this temp stuff.
						modelC->lightedBy.append(mainLight);
					}
				}

				if (it->GetParent() != NULL)
				{
					object->AttachTo(objects[it->GetParent()]);
				}
				else
				{
					object->AttachTo(level->getRoot());
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