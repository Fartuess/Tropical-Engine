#pragma once
#include <QtCore/QString>

#include <Utills/Singleton.h>

#include "AbstractShaderBuilder.h"

namespace TropicalEngine
{

	class CommonMeshShaderBuilder : public AbstractShaderBuilder, public Singleton<CommonMeshShaderBuilder>
	{
	public:
		CommonMeshShaderBuilder();
		~CommonMeshShaderBuilder();

		virtual void resetInputs() override;

		virtual class Shader* createShader(QString shaderName, QString shaderPass = "Default") override;
	protected:
		QString lighting;
		QString shaderCore;
	};

}