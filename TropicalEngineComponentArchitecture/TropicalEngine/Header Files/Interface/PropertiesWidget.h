#pragma once
#include <QtWidgets/qtreewidget.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Widget for displaying properties of selected object.
	  */
	#pragma endregion
	class PropertiesWidget : public QTreeWidget
	{
		Q_OBJECT
	public:
		#pragma region documentation
		/**
		  * \brief PropertiesWidget constructor.
		  */
		#pragma endregion
		PropertiesWidget(void);
		#pragma region documentation
		/**
		  * \brief PropertiesWidget destructor.
		  */
		#pragma endregion
		~PropertiesWidget(void);
	public slots:
		void Reload();
	};

}