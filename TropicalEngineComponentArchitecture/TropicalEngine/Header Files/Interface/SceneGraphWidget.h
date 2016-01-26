#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	class SceneGraphWidget : public QTreeWidget
	{
	public:
		SceneGraphWidget(class Scene*);
		~SceneGraphWidget(void);

		class Scene* getScene()	{ return scene; }
		void setScene(class Scene* scene)	{ this->scene = scene; Reload(); }

		void Reload();

	private:
		class Scene* scene;
	};

}