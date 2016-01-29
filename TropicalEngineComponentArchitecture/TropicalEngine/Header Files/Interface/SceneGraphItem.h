#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Single item in SceneGraphWidget representing single Entity object.
	  */
	#pragma endregion
	class SceneGraphItem : public QTreeWidgetItem
	{
	public:
		#pragma region documentation
		/**
		  * \brief Entity which data SceneGraphItem is displaying.
		  */
		#pragma endregion
		class Entity* entity;

		#pragma region documentation
		/**
		  * \brief SceneGraphItem constructor.
		  *
		  * @param name Name of item.
		  * @param entity Entity which data SceneGraphItem will be displaying.
		  */
		#pragma endregion
		SceneGraphItem(QString name, class Entity* entity);
		#pragma region documentation
		/**
		  * \brief SceneGraphItem destructor.
		  */
		#pragma endregion
		~SceneGraphItem(void);

		#pragma region documentation
		/**
		  * \brief Reloads information about owned Entity and all its subobjects.
		  */
		#pragma endregion
		void Reload();
	};

}