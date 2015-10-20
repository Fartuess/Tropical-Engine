#include <Interface/PropertyItem.h>
#include <Component/Component.h>

PropertyItem::PropertyItem(QString name)
{
	if (!isTemplateItemsInitialized)
	{
		isTemplateItemsInitialized = true;
		InitializeTemplateItems();
	}
	this->name = name;
	setText(0, name);
}

PropertyItem::PropertyItem(QString name, PropertyItem* otherItem)
{
	this->name = name;
	setText(0, name);
	for (int i = 0; i < otherItem->childCount(); i++)
	{
		addChild(new PropertyItem(static_cast<PropertyItem*>(otherItem->child(i))->name, static_cast<PropertyItem*>(otherItem->child(i))));
	}
}

PropertyItem::~PropertyItem(void)
{
	while (childCount() > 0)
	{
		delete takeChild(0);
	}
}

void PropertyItem::Reload(Component* component)
{
	///Figure out if it is important if we copy maps for time saving or not to save memory
	this->component = component;

	QHash<QString, QString> parameters = Component::getParameters(component->getTypeName());
	for (QString parameter : parameters.keys())
	{
		PropertyItem* parameterItem;
		if (templateItems.contains(parameters[parameter]))
		{
			parameterItem = CloneTemplateItem(parameter, parameters[parameter]);
			//theoretically change component for each child as well
		}
		else
		{
			parameterItem = new PropertyItem(parameter);
		}
		parameterItem->component = component;
		addChild(parameterItem);
	}
}

bool PropertyItem::isTemplateItemsInitialized = false;
QHash<QString, PropertyItem*> PropertyItem::templateItems = QHash<QString, PropertyItem*>();

void PropertyItem::AddTemplateItem(PropertyItem* templateItem)
{
	templateItems[templateItem->name] = templateItem;
}

PropertyItem* PropertyItem::CloneTemplateItem(QString name, QString templateName)
{
	PropertyItem* clonedItem = new PropertyItem(name, templateItems[templateName]);
	return clonedItem;
}
void PropertyItem::InitializeTemplateItems()
{
	PropertyItem* vec3_Item = new PropertyItem("Vec3");
	vec3_Item->addChild(new PropertyItem("X"));
	vec3_Item->addChild(new PropertyItem("Y"));
	vec3_Item->addChild(new PropertyItem("Z"));
	AddTemplateItem(vec3_Item);

	PropertyItem* ColorRGB_Item = new PropertyItem("ColorRGB");
	ColorRGB_Item->addChild(new PropertyItem("R"));
	ColorRGB_Item->addChild(new PropertyItem("G"));
	ColorRGB_Item->addChild(new PropertyItem("B"));
	AddTemplateItem(ColorRGB_Item);
}