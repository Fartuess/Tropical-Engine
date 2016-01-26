#pragma once

#include <QtCore/qset.h>

namespace TropicalEngine
{

	class SceneManager
	{
	public:
		friend class Scene;

		SceneManager();
		~SceneManager();

	protected:
		QSet<class Scene*> scenes;
	};

}