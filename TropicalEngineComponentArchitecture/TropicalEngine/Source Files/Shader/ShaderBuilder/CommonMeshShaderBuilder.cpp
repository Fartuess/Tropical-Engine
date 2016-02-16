//#include <iostream>

#include <Shader/Shader.h>

#include <Shader/ShaderBuilder/CommonMeshShaderBuilder.h>

#include <Utills/Exception.h>

namespace TropicalEngine
{

	CommonMeshShaderBuilder::CommonMeshShaderBuilder()
	{
		resetInputs();
	}


	CommonMeshShaderBuilder::~CommonMeshShaderBuilder()
	{
	}

	void CommonMeshShaderBuilder::resetInputs()
	{
		inputs["Vertex Shader"] = "./Shader Files/Mesh/DefaultMesh.glsl";
		inputs["TCS Shader"] = "";
		inputs["TES Shader"] = "";

		inputs["Custom Lighting"] = "";
		inputs["Lighting Model"] = "./Shader Files/LightingModels/LambertLightingModel.glsl";
		inputs["Surface Shader"] = "./Shader Files/SurfaceShaders/SimpleColor.glsl";
		inputs["Blend Mode"] = "./Shader Files/Blending/BlendOpaque.glsl";
	}

	Shader* CommonMeshShaderBuilder::createShader(QString shaderName, QString shaderPass)
	{
		Shader* shader;

		QString vertexSource;
		QString tessalationControlSource;
		QString tessalationEvaluationSource;
		QString fragmentSource;

		bool isUsingTessellation = !(inputs["TCS Shader"] == "" || inputs["TES Shader"] == "");

		if (shaderPass == "Default" || shaderPass == "Color")
		{
			vertexSource = Shader::PreprocessShaderFile(inputs["Vertex Shader"]);
			if (isUsingTessellation)
			{
				tessalationControlSource = Shader::PreprocessShaderFile(inputs["TCS Shader"]);
				tessalationEvaluationSource = Shader::PreprocessShaderFile(inputs["TES Shader"]);
			}

			//fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Phong_PS.glsl");

			fragmentSource += "#version 330";
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Core/ShaderCore_Header.glsl");
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Lighting/Lighting_Header.glsl");
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile(inputs["Lighting Model"]);
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile(inputs["Blend Mode"]);
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile(inputs["Surface Shader"]);
			fragmentSource += "\n";
			if (inputs["Custom Lighting"] != "")
			{
				fragmentSource += Shader::PreprocessShaderFile(inputs["Custom Lighting"]);
				fragmentSource += "\n";
			}
			fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Lighting/Lighting.glsl");
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Core/ShaderCore.glsl");

			//std::cout << fragmentSource.toStdString();

			shader = Shader::createShaderFromSources(vertexSource, tessalationControlSource, tessalationEvaluationSource, fragmentSource, shaderName + "_color");
		}
		else if (shaderPass == "Shadowmap")
		{
			vertexSource = Shader::PreprocessShaderFile(inputs["Vertex Shader"]);
			if (isUsingTessellation)
			{
				tessalationControlSource = Shader::PreprocessShaderFile(inputs["TCS Shader"]);
				tessalationEvaluationSource = Shader::PreprocessShaderFile(inputs["TES Shader"]);
			}

			fragmentSource += Shader::PreprocessShaderFile(inputs["Blend Mode"]);
			fragmentSource += "\n";
			fragmentSource += Shader::PreprocessShaderFile("./Shader Files/Shadowmap/ShadowmapCore.glsl");

			shader = Shader::createShaderFromSources(vertexSource, tessalationControlSource, tessalationEvaluationSource, fragmentSource, shaderName + "_shadowmap");
			// TODO: if same shader already exist use that one instead.
		}
		else
		{
			// TODO: This should be handled automatically without programmer having to do it in every builder.
			throw Exception<AbstractShaderBuilder>("This generator doesn't support this shader pass.", this);
		}

		//resetInputs();

		return shader;
	}

}