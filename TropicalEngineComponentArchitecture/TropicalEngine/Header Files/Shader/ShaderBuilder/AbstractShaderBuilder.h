#pragma once
#include <QtCore/qmap.h>

namespace TropicalEngine
{

	class AbstractShaderBuilder
	{
	public:

		friend class ShaderTechnique;

		AbstractShaderBuilder();
		~AbstractShaderBuilder();

		void setInput(QString name, QString path);
		virtual void resetInputs() = 0;
		
		
		QString& operator[](QString name)      { return inputs[name]; };
		const QString operator[](QString name) const { return inputs[name]; };

		virtual class Shader* createShader(QString shaderName, QString shaderPass = "Default") = 0;
	protected:
		QMap<QString, QString> inputs;
	};

}