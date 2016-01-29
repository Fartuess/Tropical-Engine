#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Widget for displaying structure of the scene.
	  */
	#pragma endregion
	class SceneGraphWidget : public QTreeWidget
	{
	public:
		#pragma region documentation
		/**
		  * \brief SceneGraphWidget constructor.
		  *
		  * @param scene Scene this widget is displaying.
		  */
		#pragma endregion
		SceneGraphWidget(class Scene* scene);
		#pragma region documentation
		/**
		  * \brief SceneGraphWidget destructor.
		  */
		#pragma endregion
		~SceneGraphWidget(void);

		#pragma region documentation
		/**
		  * \brief Gets Scene that is displayed in SceneGraphWidget.
		  *
		  * @return Scene that is displayed in SceneGraphWidget.
		  */
		#pragma endregion
		class Scene* getScene()	{ return scene; }
		#pragma region documentation
		/**
		  * \brief Sets Scene which will be displayed in SceneGraphWidget.
		  *
		  * @param scene Scene to display in SceneGraphWidget.
		  */
		#pragma endregion
		void setScene(class Scene* scene)	{ this->scene = scene; Reload(); }

		#pragma region documentation
		/**
		  * \brief Reloads information in SceneGraphWidget
		  */
		#pragma endregion
		void Reload();

	private:
		class Scene* scene;
	};

}