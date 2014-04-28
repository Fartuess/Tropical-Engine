#pragma once
//#ifndef GameObject_Included
//#define GameObject_Included

#include "Scene_header.h"

using namespace std;

class Vec3;
class Model;
class Collider;
class MaterialPoint;

class GameObject
{
public:
	Vec3* Position;
	Vec3* Rotation;
	Vec3* Scale;
	bool isDynamic;
	Model* Mesh;
	//Shader* Material;
	//MaterialPoint* MPoint;//is this one required?
	Collider* collider;	//support for one collider for one GameObject node.


	list<GameObject*> SubObjects;
	
	GameObject(Vec3* position, Vec3* rotation, Vec3* scale);
	GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic);
	//GameObject(float position[3], float rotation[3], float scale[3], Model* mesh, Shader* shader);
	GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh);
	GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, MaterialPoint* mPoint);
	GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, MaterialPoint* mPoint, Collider* collider);

	void AddSubObject(GameObject* object);

	//void setMaterialPoint(MaterialPoint* mpoint);

	void InitAll(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light);	///Initializes this Game Object and all of it's childs

	void Init(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light);	///Initializes only this Game Object

	void UpdateAll(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);	///Updates this Game Object and all of it's childs

	virtual void Update(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);	///Updates only this Game Object

	void RenderAll(GLUSfloat viewMatrix[16], LightProperties* light);	///Draws this Game Object and all of it's childs

	void Render(GLUSfloat viewMatrix[16], LightProperties* light);	///Draws only this Game Object

	void Reshape(GLUSint width, GLUSint height);

	void ReshapeAll(GLUSint width, GLUSint height);
};

//#endif // GameObject_Included