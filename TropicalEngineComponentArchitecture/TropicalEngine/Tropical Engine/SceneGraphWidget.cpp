#include "TropicalEngineApplication.h"
#include "SceneManager.h"

#include "SceneGraphWidget.h"
#include "SceneGraphItem.h"
#include "Level.h"


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
	QMap<QString, Level*>& levels = TropicalEngineApplication::instance()->sceneManager->getLevels();
	foreach(QString levelName, levels.keys())
	{
		SceneGraphItem* levelItem = new SceneGraphItem(levelName, &levels[levelName]->root);
		addTopLevelItem(levelItem);
		levelItem->Reload();
	}
}