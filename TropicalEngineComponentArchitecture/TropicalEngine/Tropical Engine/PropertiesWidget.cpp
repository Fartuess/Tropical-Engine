#include "PropertiesWidget.h"
#include "PropertyItem.h"
#include "SceneGraphWidget.h"
#include "SceneGraphItem.h"
#include "Entity.h"

PropertiesWidget::PropertiesWidget(void)
{
	setColumnCount(2);
	QStringList* headerLabels = new QStringList();;
	*headerLabels << "Name" << "Value";
	setHeaderLabels(*headerLabels);
	//setHeaderHidden(true);
}


PropertiesWidget::~PropertiesWidget(void)
{
	while (topLevelItemCount() > 0)
	{
		delete takeTopLevelItem(0);
	}
}

void PropertiesWidget::Reload()
{
	///TODO: Clear list before filling it up again.
	while (topLevelItemCount() > 0)
	{
		delete takeTopLevelItem(0);
	}

	Entity* entity = static_cast<SceneGraphItem*>((static_cast<SceneGraphWidget*>(sender())->selectedItems()[0]))->entity;

	foreach(Component* component, entity->components)
	{
		PropertyItem* propertyItem = new PropertyItem(component->getName());
		propertyItem->Reload(component);
		addTopLevelItem(propertyItem);
	}
}