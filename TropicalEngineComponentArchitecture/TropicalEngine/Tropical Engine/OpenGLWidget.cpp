#include <gl\glew.h>
#include <glm.hpp>
#include <QtGui\qkeyevent>
#include <QtGui\qmouseevent>
#include <QtCore\qdebug.h>
#include "InputController.h"
#include "OglDevTut03.h"
#include "OpenGLWidget.h"

#include <QtWidgets\qapplication.h>
#include <QtCore\qthread.h>
#include "TropicalEngineApplication.h"

OglDevTut03* staticOglDevTut03;// = OglDevTut03();// = new OglDevTut03();

OpenGLWidget::OpenGLWidget(void)
{
	//bool t1 = thread() == TropicalEngineApplication::instance()->thread();
	//bool t2 = staticOglDevTut03->thread() == TropicalEngineApplication::instance()->thread();
	//bool t3 = thread() == staticOglDevTut03->thread();
}


OpenGLWidget::~OpenGLWidget(void)
{
}

void OpenGLWidget::initializeGL()
{
	glewInit();
	//GLclass = new OglDevTut03();
	//GLclass->Initialize();

	connect(this, SIGNAL(initializeSignal()), staticOglDevTut03, SLOT(Initialize()));
	//connect(this, SIGNAL(reshapeSignal()), staticOglDevTut03, SLOT(reshapeSlot()));
	connect(this, SIGNAL(drawSignal()), staticOglDevTut03, SLOT(Draw()));

	emit initializeSignal();
	//timer = new QTimer(this);
	//timer->setInterval(16);
	//timer->start();
	//connect(timer, SIGNAL(timeout()), this, SLOT(paintHandle()));
}

void OpenGLWidget::resizeGL()
{
	emit reshapeSignal();
}

void OpenGLWidget::paintGL()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//GLclass->Draw();

	emit drawSignal();

	this->update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent* keyEvent)
{
	switch ( keyEvent->key() ) {
		case Qt::Key_W:
			qDebug("W pressed");
			InputController::Instance().pressedKeys.W = true;
			OglDevTut03::cameraPosition.y += 0.01f;
			break;
		case Qt::Key_S:
			qDebug("S pressed");
			InputController::Instance().pressedKeys.S = true;
			OglDevTut03::cameraPosition.y -= 0.01f;
			break;
		case Qt::Key_A:
			qDebug("A pressed");
			InputController::Instance().pressedKeys.A = true;
			OglDevTut03::cameraPosition.x -= 0.01f;
			//qDebug() << OglDevTut03::cameraPosition.x;
			break;
		case Qt::Key_D:
			qDebug("D pressed");
			InputController::Instance().pressedKeys.D = true;
			OglDevTut03::cameraPosition.x += 0.01f;
			break;
		}
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* mouseEvent)
{
	qDebug() << "X: " << mouseEvent->x() << " Y: " << mouseEvent->y();
	InputController::Instance().mousePosition = glm::vec2(mouseEvent->x(), mouseEvent->y());
}
