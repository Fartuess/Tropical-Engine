#include <QtCore/qdebug.h>

#include <Interface/SceneGraphItem.h>
#include <Scene/Entity.h>

namespace TropicalEngine
{

	SceneGraphItem::SceneGraphItem(QString name, Entity* entity)
	{
		setText(0, name);
		this->entity = entity;
	}


	SceneGraphItem::~SceneGraphItem(void)
	{
	}

	void SceneGraphItem::Reload()
	{
		for (Entity* subobject : entity->getSubobjects())
		{
			SceneGraphItem* sceneItem;
			if (subobject->name != "")
			{
				//qDebug() << *subobject->name;
				sceneItem = new SceneGraphItem(subobject->name, subobject);
			}
			else
			{
				sceneItem = new SceneGraphItem("UnnamedEntity", subobject);
			}
			addChild(sceneItem);
			sceneItem->Reload();
		}
	}

}