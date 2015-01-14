#pragma once

#include <QtWidgets\qwidget.h>
#include <QtCore\qpoint.h>

class TitleBar : public QWidget
{
	Q_OBJECT
private:
	QWidget* rootParent;
	bool isGrabbed = false;
	QPoint mousePositionOffset;
	QPoint previousPosition;
	QSize previousSize;
	bool isMaximized = false;
	bool isSided = false;

public:
	TitleBar(QWidget* rootParent, QWidget* parent = 0);
	~TitleBar();
protected:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseDoubleClickEvent(QMouseEvent* e) override;
public slots:
	//void setPreviousSize();
	void toggleMaximize();
};

