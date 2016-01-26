#pragma once
#include <GL/glew.h>
#include <glm.hpp>

#include <QtCore/qobject.h>
#include <QtCore/qtime>

namespace TropicalEngine
{

	class OglDevTut03///TODO: Get rid of this class.
	{
	public:
		static class Level* level;

		void InitializeLevel(class Scene* scene);
	};

}