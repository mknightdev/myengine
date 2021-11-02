#include "TriangleRenderer.h"
#include "Keyboard.h"
#include "Entity.h"
#include "Transform.h"

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
	
		// Create Shader
		triangleShader = std::make_shared<ShaderProgram>();
		triangleShader->CreateShader("../resources/shaders/vertexShader.txt", "../resources/shaders/fragmentShader.txt");
	}

	void TriangleRenderer::onDisplay()
	{
		//std::cout << "Triangle Display" << std::endl;

		// Draw
		// Instruct opengl to use our shader program and vao
		glUseProgram(triangleShader->getId());
		glBindVertexArray(vao->getId());

		// Prepare the perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)800 / (float)600, 0.1f, 100.0f);

		// TODO:
		// Look at 3DGP work and compare to get triangle moving
		// Model Matrix

		// Upload the model matrix
		glUniformMatrix4fv(triangleShader->getId(), 1, GL_FALSE, glm::value_ptr(getEntity()->getTransform()->getModel()));

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
			std::cout << "Triangle: Arrow Key Pressed" << std::endl;

			// TODO: Add Transform set position here
			getEntity()->getTransform()->setPosition(glm::vec3(0, 0.5f, 0));


		}
	}
}
