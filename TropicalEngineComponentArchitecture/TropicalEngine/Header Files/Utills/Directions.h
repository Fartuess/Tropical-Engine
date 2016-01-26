#pragma once
#include <glm.hpp>

namespace TropicalEngine
{
	enum PlaneDirections
	{
		XY,
		XZ,
		YZ
	};

	//glm::vec3 PlaneDirectionsToVec3(PlaneDirections directions)
	//{
	//	switch (directions)
	//	{
	//		case XY:
	//			return glm::vec3(1.0f, 1.0f, 0.0f);
	//		case XZ:
	//			return glm::vec3(1.0f, 0.0f, 1.0f);
	//		case YZ:
	//			return glm::vec3(0.0f, 1.0f, 1.0f);
	//		default:
	//			return glm::vec3(1.0f, 1.0f, 0.0f);
	//	}
	//}
}