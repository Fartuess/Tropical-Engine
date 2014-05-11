#pragma once

#include "Simulations_header.h"

/*
 *	NOTE: Tranformation inheritence is working only for translation now.
 */

GameObject::GameObject(Vec3* position, Vec3* rotation, Vec3* scale)
{
	Position=position;
	Rotation=rotation;
	Scale=scale;
	isDynamic=false;
	Mesh = NULL;
}

GameObject::GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic)
{
	Position=position;
	Rotation=rotation;
	Scale=scale;
	isDynamic=dynamic;
	Mesh = NULL;
}

/*GameObject::GameObject(float position[], float rotation[], float scale[], Model* mesh, Shader* shader)
{
	Position=position;
	Rotation=rotation;
	Scale=scale;
	isDynamic=false;
	Mesh = mesh;
	Material = shader;
}*/

GameObject::GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh)
{
	Position=position;
	Rotation=rotation;
	Scale=scale;
	isDynamic=dynamic;
	Mesh = mesh;
}

GameObject::GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, MaterialPoint* mPoint)
{
	Position=&mPoint->Value;
	Rotation=rotation;
	Scale=scale;
	isDynamic=dynamic;
	Mesh = mesh;
	mPoint->setGameObject(this);
}

GameObject::GameObject(Vec3* position, Vec3* rotation, Vec3* scale, bool dynamic, Model* mesh, MaterialPoint* mPoint, Collider* collider)
{
	Position=&mPoint->Value;
	Rotation=rotation;
	Scale=scale;
	isDynamic=dynamic;
	Mesh = mesh;
	mPoint->setGameObject(this);
	collider->Attach(this);
}

void GameObject::AddSubObject(GameObject* object)
{
	SubObjects.push_back(object);
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::AddComponent(RenderComponent* component)
{
	renderComponents.push_back(component);
}

//void GameObject::setMaterialPoint(MaterialPoint* mpoint)
//{
//	MPoint = mpoint;
//	Position = &mpoint->Value;
//}

void GameObject::Init(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light)
{
	if(Mesh!=NULL)
	Mesh->initWavefront(g_viewMatrix, g_light);
}

void GameObject::InitAll(GLUSfloat g_viewMatrix[16], struct LightProperties* g_light)
{
	Init(g_viewMatrix, g_light);
	for( list<GameObject*>::iterator iter=SubObjects.begin(); iter != SubObjects.end(); ++iter )
	{
		(*iter)->InitAll(g_viewMatrix, g_light);
	}
}

void GameObject::Update(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16])
{
	//Mesh->Draw(Position, Rotation, Scale, Material);
	//Vec3* tempPos = new Vec3(Position->x+position->x, Position->y+position->y, Position->z+position->z);
	Vec3 tempScale(Scale->x*scale->x, Scale->y*scale->y, Scale->z*scale->z);
	if(Mesh!=NULL)
		Mesh->updateWavefront(position, Rotation, &tempScale, time, scaleMatrix);
	//delete tempPos;
	//delete tempScale;
}

void GameObject::UpdateAll(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16])
{
	//if(isDynamic==true)
	Vec3 tempPos(Position->x+position->x, Position->y+position->y, Position->z+position->z);
	Vec3 tempScale(Scale->x*scale->x, Scale->y*scale->y, Scale->z*scale->z);
	{
		Update(&tempPos, rotation, scale, time, scaleMatrix);
		//if(SubObjects.empty()==false)
		{
			for( list<GameObject*>::iterator iter=SubObjects.begin(); iter != SubObjects.end(); ++iter )
			{
				(*iter)->UpdateAll(&tempPos, rotation, &tempScale, time, scaleMatrix);
			}
		}
	}
	//delete tempPos;
	//delete tempScale;
}

void GameObject::Render(GLUSfloat viewMatrix[], LightProperties* light)
{
	if(Mesh!=NULL)
	{
	//Mesh->Draw(Position, Rotation, Scale, viewMatrix, Material, light);
	}
}

void GameObject::RenderAll(GLUSfloat viewMatrix[], LightProperties* light)
{
	Render(viewMatrix, light);
	for( list<GameObject*>::iterator iter=SubObjects.begin(); iter != SubObjects.end(); ++iter )
		{
			(*iter)->RenderAll(viewMatrix, light);
		}
}

void GameObject::Reshape(GLUSint width, GLUSint height)
{
	if(Mesh!=NULL)
	Mesh->reshapeWavefront(width, height);
}

void GameObject::ReshapeAll(GLUSint width, GLUSint height)
{
	Reshape(width, height);
	for( list<GameObject*>::iterator iter=SubObjects.begin(); iter != SubObjects.end(); ++iter )
		{
			(*iter)->ReshapeAll(width, height);
		}
}