#include <Utills/IUpdateable.h>
#include <Utills/UpdateManager.h>

namespace TropicalEngine
{

	IUpdateable::IUpdateable(int priority)
	{
		UpdateManager::instance().objects.insertMulti(priority, this);
	}


	IUpdateable::~IUpdateable()
	{
	}

}