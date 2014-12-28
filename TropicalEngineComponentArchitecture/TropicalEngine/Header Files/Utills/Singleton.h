#pragma once

template <typename T>
class Singleton
{
protected:
	static T* instance;
public:
	Singleton(void)
	{
		if(!instance)
			instance = static_cast< T* >( this );
	}
public:
	virtual ~Singleton(void)
	{
		if(instance)
			instance = nullptr;
	}

	static T& Instance()
	{
		if(instance == nullptr)
			instance = new T();
		return (*instance);
	}
};

template <typename T>
T* Singleton<T>::instance = nullptr;