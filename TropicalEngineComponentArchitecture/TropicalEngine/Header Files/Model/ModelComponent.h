#pragma once
#include <Rendering\RenderComponent.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Component for rendering models.
	  */
	#pragma endregion
	class ModelComponent : public RenderComponent
	{
	public:
		TYPENAME(ModelComponent)

		#pragma region documentation
		/**
		  * \brief Model used for this component.
		  */
		#pragma endregion
		class Model* model;

		#pragma region documentation
		/**
		  * \brief Constructor of ModelComponent.
		  *
		  * @param owner Entity object to which ModelComponent will be attached to.
		  * @param material Material to be set for this component.
		  * @param model Model to be drawn with this component.
		  * @param castingShadows Decides if this model should cast shadows.
		  */
		#pragma endregion
		ModelComponent(class Entity* owner, class Material* material, class Model* model, bool castingShadows = false);
		#pragma region documentation
		/**
		  * \brief Default destructor
		  */
		#pragma endregion
		~ModelComponent(void);

		static ModelComponent InitializeType();

		#pragma region documentation
		/**
		  * \brief Get names of shader passes used by this ModelComponent.
		  *
		  * @return Set of names of used shader passes.
		  */
		#pragma endregion
		virtual QSet<QString> getShaderPasses() override;

		void Evaluate() override;

		#pragma region documentation
		/**
		  * \brief Draws the Component.
		  *
		  * @param Draws from perspective of this camera.
		  */
		#pragma endregion
		void Draw(class CameraComponent* viewer, QString shaderPass = "Default") override;

		#pragma region documentation
		/**
		  * \brief Gets information if this model is casting shadows.
		  *
		  * @return Information if this model is casting shadows.
		  */
		#pragma endregion
		bool isCastingShadows();
		#pragma region documentation
		/**
		  * \brief Sets if this model should cast shadows.
		  *
		  * @param isCastingShadows If this model should cast shadows.
		  */
		#pragma endregion
		void isCastingShadows(bool isCastingShadows);

		#pragma region documentation
		/**
		  * \brief Serializes ModelComponent to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes ModelComponent from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return ModelComponent object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		#pragma region documentation
		/**
		  * \brief Constructor used for deserialization.
		  */
		#pragma endregion
		ModelComponent();

		void InitializeComponentType() override;

	private:
		bool castingShadows;

		static ModelComponent templateObject;
	};

}