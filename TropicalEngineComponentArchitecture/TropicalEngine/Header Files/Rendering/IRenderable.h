#pragma once

#include <QtCore/qset.h>
#include <QtCore/qstring.h>

namespace TropicalEngine
{

	class IRenderable
	{
	public:

		virtual QSet<QString> getShaderPasses() = 0;
		virtual bool hasShaderPass(QString shaderPass);
		virtual void Draw(class CameraComponent* camera, QString shaderPass = "Default") = 0;
	};

}