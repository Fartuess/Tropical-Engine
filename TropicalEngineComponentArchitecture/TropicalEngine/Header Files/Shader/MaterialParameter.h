#pragma once

namespace TropicalEngine
{

	// TODO: figure out if additional level of abstraction is usefull
	#pragma region documentation
	/**
	  * \brief Class for containg Material Parameter data in nicer way than void* .
	  */
	#pragma endregion
	class MaterialParameter
	{
	public:
		#pragma region documentation
		/**
		  * \brief Pointer to value of this parameter.
		  */
		#pragma endregion
		void* data;

		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		MaterialParameter()	{}
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~MaterialParameter()	{}

		#pragma region documentation
		/**
		  * \brief Sets value for this MaterialParameter.
		  *
		  * @param data Pointer to data which will be set as value for this parameter.
		  * @return MaterialParameter with value assigned.
		  */
		#pragma endregion
		MaterialParameter& operator=(void* data);
		#pragma region documentation
		/**
		  * \brief Gets pointer to value of this MaterialParameter.
		  *
		  * @return Pointer to value of this MaterialParameter.
		  */
		#pragma endregion
		void* operator*();
	};

}