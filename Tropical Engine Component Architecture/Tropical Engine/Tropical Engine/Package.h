#pragma once
#include <QtCore\qstring.h>
#include <QtCore\qpair.h>
#include <QtCore\qmap.h>
class Package
{
private:
	typedef QPair<QString, void*> Asset;	//type and asset itself

	QMap<QString, Asset> assets;
	QString name;
public:
	Package(QString name);
	~Package(void);

	QString getName();
	void setName(QString name);
};

