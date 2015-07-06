#pragma once
#include <QtWidgets/qtreewidget.h>

class Entity;

class SceneGraphItem : public QTreeWidgetItem
{
public:
	Entity* entity;

	SceneGraphItem(QString name, Entity* entity);
	~SceneGraphItem(void);

	void Reload();
};

