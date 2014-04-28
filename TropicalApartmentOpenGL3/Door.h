#pragma once
//#ifndef DoorCPP_Included
//#define DoorCPP_Included

#include "Models_header.h"
#include "Scene_header.h"

class Door: public GameObject
{
public:
	float Angle;
	bool isOpen;
	bool isOpening;
	float currentAngle;

	Door(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, float angle, bool isOpen);

	void Update(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);

};

//#endif //DoorCPP_Included