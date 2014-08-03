#pragma once
#include <glm.hpp>

namespace math
{
	glm::vec3 sphericalToCartesian(glm::quat rotation, float radius = 1.0f);
}