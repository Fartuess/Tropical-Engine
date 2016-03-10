#include <gtc/quaternion.hpp>

#include <QtCore/qmath.h>

#include <Utills/MathUtills.h>

namespace math
{

	glm::vec3 sphericalToCartesian(glm::quat rotation, float radius)
	{
		// TODO: Implement it.
		return glm::vec3();
	}

	glm::vec3 cartesianToSpherical(glm::vec3 direction)
	{
		glm::vec3 spherical;
		spherical.x = qSqrt(qPow(direction.x, 2.0f) + qPow(direction.y, 2.0f) + qPow(direction.z, 2.0f));
		spherical.z = qAcos(direction.z / spherical.x);
		spherical.y = qAtan(direction.y / direction.x);

		glm::vec3 fixer;
		if (direction.x > 0.0f)
		{
			fixer = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			fixer = glm::vec3(0.0f, glm::pi<float>(), 0.0f);
		}
		
		spherical += fixer;

		return spherical;
	}

}