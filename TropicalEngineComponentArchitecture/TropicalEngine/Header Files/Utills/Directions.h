#pragma once
#include <glm.hpp>

namespace TropicalEngine
{
	#pragma region documentation
	/**
	  * \brief Enum for planar directions.
	  */
	#pragma endregion
	enum PlaneDirections
	{
		#pragma region documentation
		/**
		  * Plane spanning through direction X and Y with surface facing Z.
		  */
		#pragma endregion
		XY,
		#pragma region documentation
		/**
		* Plane spanning through direction X and Z with surface facing Y.
		*/
		#pragma endregion
		XZ,
		#pragma region documentation
		/**
		* Plane spanning through direction Y and Z with surface facing X.
		*/
		#pragma endregion
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