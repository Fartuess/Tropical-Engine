#pragma once
//#ifndef Structs_Included
//#define Structs_Included


#include "Utility_header.h"
#include<iostream>
#include <string>
#include <GL/glus.h>

/**
 * Properties of the camera.
 */
struct CameraProperties
{
    GLfloat eye[3];
    GLfloat center[3];
    GLfloat up[3];
};

/**
 * Properties of the light.
 */
struct LightProperties
{
    GLfloat direction[3];
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
};

/**
 * Properties of the material, basically all the color factors without the emissive color component.
 */
struct MaterialProperties
{
    GLfloat ambientColor[4];
    GLfloat diffuseColor[4];
    GLfloat specularColor[4];
    GLfloat specularExponent;
};

/**
 * Locations for the light properties.
 */
struct LightLocations
{
    GLint directionLocation;
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
};

/**
 * Locations for the material properties.
 */
struct MaterialLocations
{
    GLint ambientColorLocation;
    GLint diffuseColorLocation;
    GLint specularColorLocation;
    GLint specularExponentLocation;
};

class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float X, float Y, float Z);
	Vec3 operator + (Vec3 &param);
	Vec3 operator * (Vec3 &param);
	Vec3 operator * (const float &param);
	Vec3 operator / (const float &param);
	Vec3 LerpVec3(Vec3* first, Vec3* second, float fractiontime);	///Linear interpolation of two Vectors
};

class Vec2
{
public:
	float x;
	float y;
	Vec2(float X, float Y);
};

struct Vec4
{
public:
	float x;
	float y;
	float z;
	float w;
	Vec4(float X, float Y, float Z, float W);
};

extern Vec3 Vec3Zero;
extern Vec3 Vec3One;

//#endif //Structs_Included