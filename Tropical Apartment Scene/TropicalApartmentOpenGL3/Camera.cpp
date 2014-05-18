#pragma once

#include "Scene_header.h"

Camera* currentCamera;

	Camera::Camera(Vec3* eye, Vec3* center, Vec3* up)
	{
		this->eye[0]=eye->x;
		this->eye[1]=eye->y;
		this->eye[2]=eye->z;

		this->center[0]=center->x;
		this->center[1]=center->y;
		this->center[2]=center->z;

		this->up[0]=up->x;
		this->up[1]=up->y;
		this->up[2]=up->z;
	}

	void Camera::Translate(Vec3* translation)
	{
		this->eye[0]+=translation->x;
		this->eye[1]+=translation->y;
		this->eye[2]+=translation->z;

		this->center[0]+=translation->x;
		this->center[1]+=translation->y;
		this->center[2]+=translation->z;
	}

	//TODO:	Implement all stuff beneath this line

	void Camera::TranslateLocal(Vec3* translation)
	{

	}

	void Camera::Rotate(Vec3* rotation)
	{
		/*g_camera.center[0]= g_camera.eye[0] + (cos((float)(((float)xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2)));
		g_camera.center[2]= g_camera.eye[2] - (sin((float)(((float)xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2)));
		g_camera.center[1]= g_camera.eye[1] + cos((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2));*/
	}

	void Camera::Rotate(float horizontalRotation, float verticalRotation)
	{
		/*g_camera.center[0]= g_camera.eye[0] + (cos((float)(((float)xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2)));
		g_camera.center[2]= g_camera.eye[2] - (sin((float)(((float)xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2)));
		g_camera.center[1]= g_camera.eye[1] + cos((float)(((float)yPos/(float)TEXTURE_HEIGHT)*2));*/
	}