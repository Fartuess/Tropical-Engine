#include <Utills/IUpdateable.h>
#include <Utills/UpdateManager.h>

#include <TropicalEngineApplication.h>

IUpdateable::IUpdateable(int priority)
{
	TropicalEngineApplication::instance()->updateManager->objects.insertMulti(priority, this);
}


IUpdateable::~IUpdateable()
{
}
