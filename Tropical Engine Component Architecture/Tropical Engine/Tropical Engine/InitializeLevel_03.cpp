#include "Level.h"
#include "Shader.h"
#include "Material.h"
#include "Model.h"
#include "ModelBuilder.h"
#include "ModelComponent.h"
#include "OglDevTut03.h"

#include "Entity.h"

void OglDevTut03::InitializeLevel()
{
	level = new Level(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	Shader* simpleShader = new Shader("../Tropical Engine/BasicVertexShader.glsl", "../Tropical Engine/PhongBlinnSimple.glsl", "PhongBlinnSimple");
	Material* simpleMaterial = new Material(simpleShader, nullptr, "Simple Material");

	Entity* planeObject = new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	planeObject->AttachComponent(new ModelComponent(planeObject, simpleMaterial, ModelBuilder::Instance().CreatePlane("Plane")));
	planeObject->name = new QString("Plane Object");

	level->root.AttachSubobject(planeObject);
	foreach(Entity* object, level->root.subobjects)
	{
		if(object->name != nullptr)
		{
			qDebug(object->name->toLatin1());
		}
	}
}