#pragma once
#include <QtCore/qset.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing Scenes.
	  */
	#pragma endregion
	class SceneManager : public Singleton<SceneManager>
	{
	public:
		friend class Scene;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		SceneManager()	{};
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~SceneManager()	{};

	protected:
		#pragma region documentation
		/**
		  * \brief Set of Scenes currently in engine.
		  */
		#pragma endregion
		QSet<class Scene*> scenes;
	};

}