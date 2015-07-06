#pragma once

#include <QtWidgets/qapplication.h>

class GuiStyleManager
{
public:
	GuiStyleManager(void);
	~GuiStyleManager(void);

	void ChangeStyle(QApplication& application, QString filename);
	void ChangeStyle(QWidget& widget, QString filename);
};

