#include "TriangleRenderer.h"
#include "Keyboard.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

using namespace myrenderer;

namespace myengine
{
	void TriangleRenderer::onInitialize()
	{
		std::cout << "Triangle Initialised" << std::endl;

		// Vertex Buffer
		positionsVbo = std::make_shared<VertexBuffer>();
		positionsVbo->add(glm::vec3(0.0f, 0.5f, 0.0f));
		positionsVbo->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		positionsVbo->add(glm::vec3(0.5f, -0.5f, 0.0f));

		// Vertex Arrray
		vao = std::make_shared<VertexArray>();
		vao->setBuffer(0, positionsVbo);

		// Shader Sources
		// TODO: Pass through function, or read in from text file
		const GLchar* vertexShaderSrc =
			"attribute vec3 in_Position;            " \
			"                                       " \
			"void main()                            " \
			"{                                      " \
			" gl_Position = vec4(in_Position, 1.0); " \
			"}                                      ";

		const GLchar* fragmentShaderSrc =
			"void main()                       " \
			"{                                 " \
			" gl_FragColor = vec4(0, 0, 1, 1); " \
			"}                                 ";

		// Create Shader
		triangleShader = std::make_shared<ShaderProgram>();
		triangleShader->CreateShader(vertexShaderSrc, fragmentShaderSrc);
	}

	void TriangleRenderer::onDisplay()
	{
		//std::cout << "Triangle Display" << std::endl;
		// Draw
		// Instruct opengl to use our shader program and vao
		glUseProgram(triangleShader->getId());
		glBindVertexArray(vao->getId());

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TriangleRenderer::onTick()
	{
		//std::cout << "Triangle Tick" << std::endl;
		
		// Check for UP key press
		if (getKeyboard()->getKeyDown(SDLK_UP))
		{
			// TODO: Add Transform set position here
		}
	}
}
