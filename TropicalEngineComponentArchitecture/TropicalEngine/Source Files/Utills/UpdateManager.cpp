#include <Utills/UpdateManager.h>
#include <Utills/IUpdateable.h>

namespace TropicalEngine
{

	void UpdateManager::UpdateAll()
	{
		int deltaTime = time.elapsed();
		time.restart();
		for (IUpdateable* object : objects)
		{
			object->OnUpdate(deltaTime);
		}
	}

}