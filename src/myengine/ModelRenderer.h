#include "Component.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct ModelRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		void mouseUpdate();

	private:
		friend struct myengine::Core;

		/**
		* Used for storing the Core and navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* \brief Shader to create and use.
		* 
		* Creates a shader program using the linked paths for the vertex and fragment shaders.
		* \attention This one is used for the model.
		*/
		std::shared_ptr<myrenderer::ShaderProgram> shader;

		/**
		* \brief Shader to create and use.
		* 
		* Creates a shader program using the linked paths for the vertex and fragment shaders. 
		* \attention This one is used for the light box that is within the scene.
		*/
		std::shared_ptr<myrenderer::ShaderProgram> lightShader;

		/**
		* \brief The VAO to load the model with.
		* 
		* Creates a VertexArray object for the main model.
		* 
		* \see myrenderer::VertexArray
		*/
		std::shared_ptr<myrenderer::VertexArray> vao;

		/**
		* \brief The VAO for the light.
		* 
		* Creates a VertexArray object for the light box.
		* \see myrenderer::VertexArray
		*/
		std::shared_ptr<myrenderer::VertexArray> lightVao;

		/**
		* \brief The positions VBO for the light box.
		* 
		* Creates a VertexBuffer for the light box, that holds all the positions for each vertex of the object.
		*/
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;

		/**
		* \brief The textures VBO.
		* 
		* Creates a VertexBuffer object for the textures of the object.
		* 
		* \see TriangleRenderer
		*/
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;

		/**
		* \brief The model's texture
		* 
		* Stores texture and gets used to bind with the VAO when drawing it.
		*/
		std::shared_ptr<myrenderer::Texture> texture;
	};
}