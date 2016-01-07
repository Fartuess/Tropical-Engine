#include <Scene/Level.h>
#include <Scene/SceneManager.h>

#include <Interface/SceneGraphWidget.h>
#include <Interface/SceneGraphItem.h>

#include "TropicalEngineApplication.h"

namespace TropicalEngine
{

	SceneGraphWidget::SceneGraphWidget(void)
	{
		setColumnCount(1);
		//setHeaderLabel("Scene Graph");
		setHeaderHidden(true);
	}


	SceneGraphWidget::~SceneGraphWidget(void)
	{
	}

	void SceneGraphWidget::Reload()
	{
		clear();
		QMap<QString, Level*>& levels = TropicalEngineApplication::instance()->sceneManager->getLevels();
		for (QString levelName : levels.keys())
		{
			SceneGraphItem* levelItem = new SceneGraphItem(levelName, levels[levelName]->getRoot());
			addTopLevelItem(levelItem);
			levelItem->Reload();
		}
	}

}