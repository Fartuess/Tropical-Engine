#include <Shader/Shader.h>
#include <Shader/ShaderBuilder/AbstractShaderBuilder.h>
#include <Shader/ShaderManager.h>

#include <Shader/ShaderTechnique.h>

#include <Package/AssetManager.h>

#include <Utills/Exception.h>

namespace TropicalEngine
{
	bool ShaderTechnique::isTypeInitialized = false;

	ShaderTechnique::ShaderTechnique(QString name, AbstractShaderBuilder* shaderBuilder, bool managed)
	{
		InitializeType();

		this->name = name;

		this->shaderBuilder = shaderBuilder;

		this->isManaged = managed;

		inputs = shaderBuilder->inputs;

		if (isManaged)
		{
			ShaderManager::instance().Load(this, name);
		}
	}

	ShaderTechnique::ShaderTechnique(QString name, class Shader* shader, QString shaderPass, bool managed)
	{
		InitializeType();

		this->name = name;

		this->shaderBuilder = nullptr;

		this->isManaged = managed;

		shaderPasses[shaderPass] = shader;

		if (isManaged)
		{
			ShaderManager::instance().Load(this, name);
		}
	}

	ShaderTechnique::~ShaderTechnique()
	{
	}

	void ShaderTechnique::setInput(QString name, QString path)
	{
		if (inputs.contains(name))
		{
			inputs[name] = path;
		}
	}

	//void ShaderTechnique::addShaderPass(QString name, class Shader* shader)
	//{
	//	if (!(shaderPasses.contains(name)))
	//	{
	//		shaderPasses[name] = shader;
	//	}
	//}

	Shader* ShaderTechnique::getShader(QString shaderPass)
	{
		// TODO: This can screw up if same shader builder was used with different inputs.

		if (!shaderPasses.contains(shaderPass))
		{
			if (shaderPass == "Default" && shaderBuilder == nullptr)
			{
				return shaderPasses.first();
			}
			else
			{
				generateShader(shaderPass);
			}
		}
		return shaderPasses[shaderPass];
	}

	class Shader* ShaderTechnique::generateShader(QString shaderPass)
	{
		if (shaderBuilder == nullptr && !shaderPasses.contains(shaderPass))
		{
			throw Exception<ShaderTechnique>("Can't generate shader without any builder.", this);
		}

		try
		{
			QMap<QString, QString> previousShaderBuilderInputs = shaderBuilder->inputs;
			shaderBuilder->inputs = inputs;
			shaderPasses[shaderPass] = shaderBuilder->createShader(name, shaderPass);
			shaderBuilder->inputs = previousShaderBuilderInputs;
		}
		catch (Exception<AbstractShaderBuilder> builderException)
		{
			throw Exception<ShaderTechnique>("This shader technique doesn't support this shader pass.", this);
		}

		if (isManaged)
		{
			ShaderManager::instance().Load(shaderPasses[shaderPass], shaderPasses[shaderPass]->getName());
		}

		return shaderPasses[shaderPass];
	}

	QJsonObject ShaderTechnique::toJSON()
	{
		// TODO: Implement it!
		QJsonObject JSON = QJsonObject();
		

		return JSON;
	}

	IDeserializableFromJSON* ShaderTechnique::fromJSON(QJsonObject JSON)
	{
		QString name = JSON["name"].toString();

		//QString debug = JSON["shader builder"].toString();

		AbstractShaderBuilder* shaderBuilder = ShaderManager::instance().getShaderBuilder(JSON["shader builder"].toString());

		ShaderTechnique* shaderTechnique = new ShaderTechnique(name, shaderBuilder);

		for (QJsonValueRef inputJSON : JSON["inputs"].toArray())
		{
			QString inputName = inputJSON.toObject()["name"].toString();
			QString inputPath = inputJSON.toObject()["path"].toString();

			shaderTechnique->setInput(inputName, inputPath);
		}
		
		return shaderTechnique;
	}

	ShaderTechnique& ShaderTechnique::InitializeType()
	{
		ShaderTechnique* shaderTechnique;
		if (!isTypeInitialized)
		{
			shaderTechnique = new ShaderTechnique();
			AssetManager::instance().addAssetType("ShaderTechnique", shaderTechnique);
			isTypeInitialized = true;
		}
		else
		{
			shaderTechnique = (ShaderTechnique*)AssetManager::instance().getTypeHandle("ShaderTechnique");
		}
		return *shaderTechnique;
	}

	//class Shader* generateShaders()
	//{
	//
	//}

}