#pragma once

namespace TropicalEngine
{

	// TODO: Currently this is not exactly singleton but rather lazy initialization and global accessing to first instance.
	#pragma region documentation
	/**
	  *\brief  Template class for Singletons.
	  */
	#pragma endregion
	template <typename T>
	class Singleton
	{
	public:
		// TODO: Temporarily public?
		virtual ~Singleton(void)
		{
			if (instanceObject)
				instanceObject = nullptr;
		}

		#pragma region documentation
		/**
		  * \brief Gets singleton instance of this class.
		  *
		  * @return Singleton instance of this class.
		  */
		#pragma endregion
		static T& instance()
		{
			if (instanceObject == nullptr)
				instanceObject = new T();
			return (*instanceObject);
		}
	protected:
		Singleton(void)
		{
			if (!instanceObject)
				instanceObject = static_cast<T*>(this);
		}
	private:
		static T* instanceObject;
	};

	template <typename T>
	T* Singleton<T>::instanceObject = nullptr;

}