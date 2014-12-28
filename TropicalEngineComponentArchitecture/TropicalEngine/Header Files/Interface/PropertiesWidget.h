#pragma once
#include <QtWidgets\qtreewidget.h>

class PropertiesWidget : public QTreeWidget
{
	Q_OBJECT
public:
	PropertiesWidget(void);
	~PropertiesWidget(void);
public slots:
	void Reload();
};

