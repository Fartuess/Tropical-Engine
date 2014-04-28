#pragma once
//#ifndef Camera_Included
//#define Camera_Included

#include "Utility_header.h"
#include "Scene_header.h"

class Camera		//TODO:	Try to change GLfloat tables to Vec3's and make camera an inherit class or even a component attachable to GameObject
{
	public:
	GLfloat eye[3];
    GLfloat center[3];
    GLfloat up[3];

	
	Camera(Vec3* eye, Vec3* center, Vec3* up);

	void Translate(Vec3* translation);	///Translates camera in global space

	void TranslateLocal(Vec3* translation);	///Translates camera based on it's rotation

	void Rotate(Vec3* rotation);	///Rotates camera

	void Rotate(float horizontalRotation, float verticalRotation);	///Rotates camera

};

extern Camera* currentCamera;

//#endif //Camera_Included