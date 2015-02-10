#include <QtCore\qdebug.h>
#include "Interface\SceneGraphItem.h"
#include "Scene/Entity.h"

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
	foreach(Entity* subobject, entity->subobjects)
	{
		SceneGraphItem* levelItem;
		if(subobject->name != "")
		{
			//qDebug() << *subobject->name;
			levelItem = new SceneGraphItem(subobject->name, subobject);
		}
		else
		{
			levelItem = new SceneGraphItem("UnnamedEntity", subobject);
		}
		addChild(levelItem);
		levelItem->Reload();
	}
}