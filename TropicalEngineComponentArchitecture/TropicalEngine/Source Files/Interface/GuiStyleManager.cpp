#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qwidget.h>

#include <QtCore/qdebug.h>

#include <Interface/GuiStyleManager.h>


GuiStyleManager::GuiStyleManager(void)
{
}


GuiStyleManager::~GuiStyleManager(void)
{
}


void GuiStyleManager::ChangeStyle(QApplication& application, QString filename)
{
	
	QFile f(filename);
	if (!f.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << f.errorString();
	}
    QTextStream in(&f);
	QString fileString = in.readAll();

	application.setStyleSheet(fileString);
}

void GuiStyleManager::ChangeStyle(QWidget& widget, QString filename)
{

	QFile f(filename);
	if (!f.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << f.errorString();
	}
	QTextStream in(&f);
	QString fileString = in.readAll();

	widget.setStyleSheet(fileString);
}
