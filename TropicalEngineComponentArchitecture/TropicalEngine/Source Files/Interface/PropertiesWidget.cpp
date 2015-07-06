#include "Interface/PropertiesWidget.h"
#include "Interface/PropertyItem.h"
#include "Interface/SceneGraphWidget.h"
#include "Interface/SceneGraphItem.h"
#include "Scene/Entity.h"

PropertiesWidget::PropertiesWidget(void)
{
	setColumnCount(2);
	QStringList* headerLabels = new QStringList();;
	*headerLabels << "Name" << "Value";
	setHeaderLabels(*headerLabels);
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

	if (static_cast<SceneGraphWidget*>(sender())->selectedItems().empty() == false)
	{
		Entity* entity = static_cast<SceneGraphItem*>((static_cast<SceneGraphWidget*>(sender())->selectedItems()[0]))->entity;

		for (Component* component : entity->components)
		{
			PropertyItem* propertyItem = new PropertyItem(component->getTypeName());
			propertyItem->Reload(component);
			addTopLevelItem(propertyItem);
		}
	}
}