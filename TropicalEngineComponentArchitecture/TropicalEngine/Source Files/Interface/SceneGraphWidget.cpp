#include <Scene/Level.h>
#include <Scene/Scene.h>

#include <Interface/SceneGraphWidget.h>
#include <Interface/SceneGraphItem.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	SceneGraphWidget::SceneGraphWidget(Scene* scene)
	{
		setColumnCount(1);
		//setHeaderLabel("Scene Graph");
		setHeaderHidden(true);

		setScene(scene);
	}


	SceneGraphWidget::~SceneGraphWidget(void)
	{
	}

	void SceneGraphWidget::Reload()
	{
		clear();
		QMap<QString, Level*>& levels = scene->getLevels();
		for (QString levelName : levels.keys())
		{
			SceneGraphItem* levelItem = new SceneGraphItem(levelName, levels[levelName]->getRoot());
			addTopLevelItem(levelItem);
			levelItem->Reload();
		}
	}

}