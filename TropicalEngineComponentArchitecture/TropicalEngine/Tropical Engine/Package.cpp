#include "Package.h"


Package::Package(QString name)	//??
{
	this->name = name;
}


Package::~Package(void)	//??
{
}

QString Package::getName()
{
	return name;
}

void Package::setName(QString name)	//??
{
	this->name = name;
}