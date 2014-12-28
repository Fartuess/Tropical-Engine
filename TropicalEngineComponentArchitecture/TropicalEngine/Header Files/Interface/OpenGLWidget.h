#pragma once
#include <QtWidgets\qwidget.h>
#include <QtOpenGL\QGLWidget>

class OglDevTut03;

class OpenGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	OpenGLWidget(void);
	~OpenGLWidget(void);
protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();

	void keyPressEvent(QKeyEvent* keyEvent);
	void mouseMoveEvent(QMouseEvent* mouseEvent);

signals:
	void initializeSignal();
	void reshapeSignal(int width, int height);
	void drawSignal();
};