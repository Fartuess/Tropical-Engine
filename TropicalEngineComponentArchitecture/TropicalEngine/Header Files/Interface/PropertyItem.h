#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	// TODO: Finish documenting PropertyItem class.
	#pragma region documentation
	/**
	  * \brief Single item in PropertiesWidget.
	  */
	#pragma endregion
	class PropertyItem : public QTreeWidgetItem
	{
	public:
		#pragma region documentation
		/**
		  * \brief Name of item.
		  */
		#pragma endregion
		QString name;
		class Component* component;	// TODO: Encapsulate component field in PropertyItem?

		PropertyItem(QString name);
		PropertyItem(QString name, PropertyItem* otherItem);
		~PropertyItem(void);

		void Reload(class Component* component);

		static void AddTemplateItem(PropertyItem* templateItem);
		static PropertyItem* CloneTemplateItem(QString name, QString templateName);

	private:
		static bool isTemplateItemsInitialized;	//guinea english to fit naming conventions :D
		static QHash<QString, PropertyItem*> templateItems;

		static void InitializeTemplateItems();
	};

}