#pragma once
#include <QtWidgets/qtreewidget.h>

class SceneGraphWidget : public QTreeWidget
{
public:
	SceneGraphWidget(void);
	~SceneGraphWidget(void);

	void Reload();
};

