#pragma once
#include <QtWidgets/qapplication.h>

#include <Utills/Singleton.h>

namespace TropicalEngine
{

	#pragma region documenation
	/**
	  * \brief Class for managing visual style of user interface.
	  */
	#pragma endregion
	class GuiStyleManager : public Singleton<GuiStyleManager>
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		GuiStyleManager(void)	{}
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~GuiStyleManager(void)	{}

		#pragma region documentation
		/**
		  * \brief Changes style of application.
		  *
		  * @param application Application to change user interface style.
		  * @param filename Path to css file defining style of interface.
		  */
		#pragma endregion
		void ChangeStyle(QApplication& application, QString filename);
		#pragma region documentation
		/**
		  * \biref Changes style of widget.
		  *
		  * @param widget Widget to changer user interface style.
		  * @param filename Path to css file defining style of interface.
		  */
		#pragma endregion
		void ChangeStyle(QWidget& widget, QString filename);
	};

}