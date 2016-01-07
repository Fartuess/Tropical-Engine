#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	class SceneGraphWidget : public QTreeWidget
	{
	public:
		SceneGraphWidget(void);
		~SceneGraphWidget(void);

		void Reload();
	};

}