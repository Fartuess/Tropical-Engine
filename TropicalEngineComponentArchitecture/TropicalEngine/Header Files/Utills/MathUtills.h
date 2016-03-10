#pragma once
#include <glm.hpp>

#include <QtCore/qmetatype.h>

namespace math
{
	glm::vec3 sphericalToCartesian(glm::quat rotation, float radius = 1.0f);

	#pragma region documentation
	/**
	  * \brief converts position in cartesian space to position in spherical space.
	  *
	  * @param direction Position in cartesian space.
	  * @return Position in spherical space. x (radius) y, z (latitude and longitude)
	  */
	#pragma endregion
	glm::vec3 cartesianToSpherical(glm::vec3 direction);
}