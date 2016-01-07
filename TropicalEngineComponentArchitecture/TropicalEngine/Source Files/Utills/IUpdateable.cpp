#include <Utills/IUpdateable.h>
#include <Utills/UpdateManager.h>

#include <TropicalEngineApplication.h>

namespace TropicalEngine
{

	IUpdateable::IUpdateable(int priority)
	{
		TropicalEngineApplication::instance()->updateManager->objects.insertMulti(priority, this);
	}


	IUpdateable::~IUpdateable()
	{
	}

}