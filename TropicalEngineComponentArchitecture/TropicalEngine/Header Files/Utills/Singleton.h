#pragma once

namespace TropicalEngine
{

	/// TODO: Currently this is not exactly singleton but rather lazy initialization and global accessing to first instance. 
	/**
	  * Template class for Singletons.
	  */
	template <typename T>
	class Singleton
	{
	protected:
		static T* instance;
	public:
		Singleton(void)
		{
			if (!instance)
				instance = static_cast<T*>(this);
		}
	public:
		virtual ~Singleton(void)
		{
			if (instance)
				instance = nullptr;
		}

		/**
		  * \brief Gets singleton instance of this class.
		  *
		  * @return Singleton instance of this class.
		  */
		static T& Instance()
		{
			if (instance == nullptr)
				instance = new T();
			return (*instance);
		}
	};

	template <typename T>
	T* Singleton<T>::instance = nullptr;

}