#pragma once
#include <QtWidgets/qwidget.h>
#include <QtOpenGL/QGLWidget>
#include <QtCore/qpoint.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Widget for rendering OpenGL Scene.
	  */
	#pragma endregion
	class OpenGLWidget : public QGLWidget
	{
		Q_OBJECT
	public:
		#pragma region documentation
		/**
		  * \brief OpenGLWidget counstructor which doesn't bind any Scene.
		  */
		#pragma endregion
		OpenGLWidget(void);
		#pragma region documentation
		/**
		  * \brief OpenGLWidgets constructor which binds Scene.
		  *
		  * @param scene Scene to bind.
		  */
		#pragma endregion
		OpenGLWidget(class Scene* scene);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~OpenGLWidget(void)	{}

		#pragma region documentation
		/**
		  * \brief Gets pointer to Scene OpenGLWidget is drawing.
		  *
		  * @return Scene OpenGLWidget is drawing.
		  */
		#pragma endregion
		class Scene* getScene()	{ return drawnScene; }
		#pragma region documentation
		/**
		  * \brief Sets Scene to draw for OpenGLWidget.
		  *
		  * @param scene Scene to bind.
		  */
		#pragma endregion
		void setScene(class Scene* scene)	{ drawnScene = scene; }

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

		int isMousePressed = 0;

		class Scene* drawnScene = nullptr;

		/// TODO: Remove testing code.
		class RenderTexture* widgetFramebuffer;
	};

}