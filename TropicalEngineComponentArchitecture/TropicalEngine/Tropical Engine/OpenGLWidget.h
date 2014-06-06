#pragma once
//#include <QtCore\qmetaobject.h>
#include <QtWidgets\qwidget.h>
#include <QtOpenGL\QGLWidget>
//#include <QtCore\qtimer.h>

class OglDevTut03;

extern OglDevTut03* staticOglDevTut03;

class OpenGLWidget : public QGLWidget
{
	Q_OBJECT
private:
	//OglDevTut03* GLclass;
	//QTimer* timer;
public:
	OpenGLWidget(void);
	~OpenGLWidget(void);
protected:
	void initializeGL();
	void resizeGL();
	void paintGL();

	void keyPressEvent(QKeyEvent* keyEvent);
	void mouseMoveEvent(QMouseEvent* mouseEvent);

signals:
	void initializeSignal();
	void reshapeSignal();
	void drawSignal();
};