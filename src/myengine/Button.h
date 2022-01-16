#include "Component.h"
#include <myrenderer/myrenderer.h>
#include <myengine/myengine.h>

namespace myengine
{
	struct Button : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		// Button Properties
		void setTexture(std::string _fileName);
		void setShader(const GLchar* _vert, const GLchar* _frag);

		// Button Interaction
		bool intersect(vec2 _mouse, vec4 _rectangle);

	private:
		/**
		* \brief Shader to create and use.
		*
		* Creates a shader program using the linked paths for the vertex and fragment shaders.
		* \attention This one is used for the model.
		*/
		std::shared_ptr<myrenderer::ShaderProgram> shader;

		/**
		* \brief The VAO to create the Button.
		*
		* Creates a VertexArray object for the main model.
		*
		* \see myrenderer::VertexArray
		*/
		std::shared_ptr<myrenderer::VertexArray> vao;

		/**
		* \brief The positions VBO.
		*
		* Creates a VertexBuffer, that holds all the positions for each vertex of the object.
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