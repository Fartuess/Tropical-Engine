#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	class Entity;

	class SceneGraphItem : public QTreeWidgetItem
	{
	public:
		Entity* entity;

		SceneGraphItem(QString name, Entity* entity);
		~SceneGraphItem(void);

		void Reload();
	};

}