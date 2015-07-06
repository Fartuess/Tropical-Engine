#pragma once
#include <QtWidgets/qwidget.h>
#include <QtOpenGL/QGLWidget>
#include <QtCore/qpoint.h>

class OglDevTut03;

class OpenGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	OpenGLWidget(void);
	~OpenGLWidget(void);

signals:
	void initializeSignal();
	void reshapeSignal(int width, int height);
	void drawSignal();

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	void keyPressEvent(QKeyEvent* keyEvent) override;
	void keyReleaseEvent(QKeyEvent* keyEvent) override;
	void mousePressEvent(QMouseEvent* mouseEvent) override;
	void mouseReleaseEvent(QMouseEvent* mouseEvent) override;
	void mouseMoveEvent(QMouseEvent* mouseEvent) override;

private:
	QPoint* abstractMousePosition;
	QPoint* screenCenter;
	QPoint* mouseGrabPoint;
	QCursor* previousCursor;
};