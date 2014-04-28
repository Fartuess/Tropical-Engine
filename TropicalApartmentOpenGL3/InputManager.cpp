#include "Input_header.h"
#include "Simulations_header.h"
#include "Scene_header.h"


void InputManager::Update(float time, float cameraSpeed, int* xPos, int* yPos, float g_viewMatrix[16])
{

	glfwPollEvents();
	if(glfwGetKey('W')>0)
	{
	currentCamera->eye[2]-=cameraSpeed*sin((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	currentCamera->eye[0]+=cameraSpeed*cos((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	currentCamera->eye[1]+=cameraSpeed*cos((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	}
	if(glfwGetKey('S')>0)
	{
	currentCamera->eye[2]+=cameraSpeed*sin((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	currentCamera->eye[0]-=cameraSpeed*(cos((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2)))*time;
	currentCamera->eye[1]-=cameraSpeed*cos((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	}
	if(glfwGetKey('A')>0)
	{
	currentCamera->eye[0]-=cameraSpeed*sin((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	currentCamera->eye[2]-=cameraSpeed*(cos((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2)))*time;
	}
	if(glfwGetKey('D')>0)
	{
	currentCamera->eye[0]+=cameraSpeed*sin((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2))*time;
	currentCamera->eye[2]+=cameraSpeed*(cos((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2)))*time;
	}
	if(glfwGetKey(GLFW_KEY_SPACE)>0)
	{
	currentCamera->eye[1]+=cameraSpeed*time;
	}
	if(glfwGetKey(GLFW_KEY_LCTRL)>0||glfwGetKey('C')>0)
	{
	currentCamera->eye[1]-=cameraSpeed*time;
	}
	if(glfwGetKey('O')>0)
	{
		mPoint1->addForce(&Vec3(0.0f, 1.0f, -0.35f));
		mPoint1->addAcceleration(&Vec3(0.0f, -0.5f, 0.0f));
	}
	glfwGetMousePos( xPos, yPos );

	currentCamera->center[0]= currentCamera->eye[0] + (cos((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2)));
	currentCamera->center[2]= currentCamera->eye[2] - (sin((float)(((float)*xPos/(float)TEXTURE_WIDTH)*(-4)+3))*sin((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2)));
	currentCamera->center[1]= currentCamera->eye[1] + cos((float)(((float)*yPos/(float)TEXTURE_HEIGHT)*2));

	glusLookAtf(g_viewMatrix, currentCamera->eye[0], currentCamera->eye[1], currentCamera->eye[2], currentCamera->center[0], currentCamera->center[1], currentCamera->center[2], currentCamera->up[0], currentCamera->up[1], currentCamera->up[2]);

	//Opening&Closing Doors

	if(glfwGetKey('E')>0)
	{
		Door1->isOpening=true;
		Door2->isOpening=true;
	}
}