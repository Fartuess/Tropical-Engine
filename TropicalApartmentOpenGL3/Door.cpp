#pragma once

#include "Scene_header.h"

//This class is deprecated due to keyframe Animation implementation


Door::Door(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, float angle, bool isOpen):GameObject(position, rotation, scale, dynamic, mesh)
{
	Angle = angle;
	this->isOpen=isOpen;
	isOpening=false;
	if(isOpen)
		currentAngle=angle;
	else
		currentAngle=0;
}

void Door::Update(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16])
{
	//Mesh->Draw(Position, Rotation, Scale, Material);
	Vec3* tempScale = new Vec3(Scale->x*scale->x, Scale->y*scale->y, Scale->z*scale->z);
	Vec3* tempRotation = new Vec3(Rotation->x, Rotation->y+currentAngle, Rotation->z);
	if(isOpening)
	{
		if(isOpen)
		{
			if(Angle>0)
			{
				if(currentAngle<0)
				{
					currentAngle+=Angle*time/10;
				}
				else
				{
					isOpening = false;
					isOpen = false;
				}
			}
			else
			{
				if(currentAngle>0)
				{
					currentAngle+=Angle*time/10;
				}
				else
				{
					isOpening = false;
					isOpen = false;
				}
			}
		}
		else
		{
			if(abs(currentAngle)<abs(Angle))
			{
				currentAngle-=Angle*time/10;
			}
			else
			{
				isOpening = false;
				isOpen = true;
			}
		}
	}
	if(Mesh!=NULL)
		Mesh->updateWavefront(position, tempRotation/*Rotation*/, tempScale, time, scaleMatrix);
	delete tempScale;
	delete tempRotation;
}

