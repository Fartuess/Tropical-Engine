#include "Level.h"

Level::Level(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, QString name):transform(&(this->root)), internalPackage(name)
{
	///TODO: implement it.
}

//Level::Level(glm::vec3 position, quat rotation, glm::vec3 scale, QString name):transform(&(this->root)), internalPackage(name)
//{
//	///TODO: implement it.
//}

Level::Level(TransformComponent transform, QString name):transform(&(this->root)), internalPackage(name)
{
	///TODO: implement it.
}


Level::~Level(void)
{
	///TODO: implement it.
}
