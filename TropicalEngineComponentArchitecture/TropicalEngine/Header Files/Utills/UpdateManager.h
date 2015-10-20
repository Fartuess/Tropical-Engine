#pragma once
#include <QtCore/qmap.h>
#include <QtCore/qtime>

class UpdateManager
{
public:
	friend class IUpdateable;

	UpdateManager();
	~UpdateManager();

	void UpdateAll();
	void Update(class IUpdateable* object);	//it makes mess with delta times

private:
	QMultiMap<int, IUpdateable*> objects;
	QTime time;
};

