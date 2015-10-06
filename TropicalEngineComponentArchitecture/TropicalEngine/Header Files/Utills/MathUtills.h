#pragma once
#include <glm.hpp>

#include <QtCore/qmetatype.h>

//Q_DECLARE_METATYPE(glm::vec3)

namespace math
{
	glm::vec3 sphericalToCartesian(glm::quat rotation, float radius = 1.0f);

	//void registerGLMtypes();
	//{
	//	qRegisterMetaType<glm::vec3>("glm::vec3");
	//}
}