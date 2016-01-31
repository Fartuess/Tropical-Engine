#ifndef _SPHERICALCOORDINATESYSTEM
#define _SPHERICALCOORDINATESYSTEM

#pragma region documentation
/**
  * \brief Converts cartesian coordinates to spherical coordinates.
  *
  * @param cartesian Position in cartesian coordinate system.
  * @return Position in spherical coordinates saved in ISO convention (radius x, inclination y, azimuth z).
  */
#pragma endregion
vec3 cartesianToSpherical(vec3 cartesian)
{
	vec3 spherical;
	spherical.x = sqrt(pow(cartesian.x, 2.0) + pow(cartesian.y, 2.0) + pow(cartesian.z, 2.0));
	spherical.y = acos(cartesian.z / spherical.x);
	spherical.z = atan(cartesian.y / cartesian.x);

	return spherical;
}
//
//#pragma region documentation
///**
//  * \brief Converts spherical coordinates to cartesian coordinates.
//  *
//  * @param spherical Position in spherical coordinates saved in ISO convention (radius x, inclination y, azimuth z).
//  * @return Position in cartesian coordinate system.
//  */
//#pragma endregion
//vec3 sphericalToCartesian(vec3 spherical)
//{
//	vec3 cartesian;
//	cartesian.x = spherical.x * sin(spherical.y) * cos(spherical.z);
//	cartesian.y = spherical.x * sin(spherical.y) * sin(spherical.z);
//	cartesian.z = spherical.x * cos(spherical.y);
//
//	return cartesian;
//}
//
//#pragma region documentation
///**
//  * \brief Converts spherical coordinates to cartesian coordinates.
//  *
//  * @param radius Radius.
//  * @param iclination Inclination.
//  * @param azimuth Azimuth.
//  * @return Position in cartesian coordinate system.
//  */
//#pragma endregion
//vec3 sphericalToCartesian(float radius, float inclination, float azimuth)
//{
//	return sphericalToCartesian(vec3(radius, inclination, azimuth));
//}

#endif