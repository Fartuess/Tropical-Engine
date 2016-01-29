#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Material.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing Materials.
	  */
	#pragma endregion
	class MaterialManager
	{
	public:
		friend class Texture;
		friend class TextureManager;
		friend class Material;

		#pragma region documentation
		/**
		  * \brief MaterialManager constructor.
		  */
		#pragma endregion
		MaterialManager(void);
		#pragma region documentation
		/**
		  * \brief MaterialManager destructor.
		  */
		#pragma endregion
		~MaterialManager(void);

		#pragma region documentation
		/**
		  * \brief Gets Material with given name.
		  *
		  * @param name Name of the Material to look for.
		  * @return Found Material.
		  */
		#pragma endregion
		Material* operator[](QString name)	{ return materials[name]; };
		#pragma region documentation
		/**
		  * \brief Gets Material with given name.
		  *
		  * @param name Name of the Material to look for.
		  * @return Found Material.
		  */
		#pragma endregion
		const Material* operator[](QString name) const	{ return materials[name]; };

		// TODO: Rethink Load method. Maybe change name to 'Create'.
		#pragma region documentation
		/**
		  * \brief Creates new Material.
		  *
		  * This method needs chaning since Materials are now more focused on ShaderTechniques!
		  */
		#pragma endregion
		Material* Load(class Shader* shader, QString name);	//temporal declaration

		#pragma region documentation
		/**
		 * \brief Method for use in renderable objects to set up drawing with this Material.
		 *
		 * @param name Name of Material to use.
		 */
		#pragma endregion
		void UseMaterial(QString name);
		#pragma region documentation
		/**
		  * \brief Method for use in renderable objects to set up drawing with this Material.
		  *
		  * @param material Material to use.
		  */
		#pragma endregion
		void UseMaterial(Material* material);

	private:
		QHash<QString, Material*> materials;	// TODO: Figure out if QHash or QMap. In some border cases materials might be created every frame.

		void FlushMaterial(QString name, bool forced = false);
	};

}