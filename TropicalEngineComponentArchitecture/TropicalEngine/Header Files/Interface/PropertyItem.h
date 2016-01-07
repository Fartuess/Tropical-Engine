#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	class Component;

	class PropertyItem : public QTreeWidgetItem
	{
	public:
		QString name;
		Component* component;	///TODO: create getters and setters for this little fellow.

		PropertyItem(QString name);
		PropertyItem(QString name, PropertyItem* otherItem);
		~PropertyItem(void);

		void Reload(Component* component);

		static void AddTemplateItem(PropertyItem* templateItem);
		static PropertyItem* CloneTemplateItem(QString name, QString templateName);

	private:
		static bool isTemplateItemsInitialized;	//guinea english to fit naming conventions :D
		static QHash<QString, PropertyItem*> templateItems;

		static void InitializeTemplateItems();
	};

}