#include "TriangleRenderer.h"
#include "Keyboard.h"
#include "Entity.h"
#include "Transform.h"
#include "Mouse.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

using namespace myrenderer;


// TODO: move into own class
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw	= -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov	= 45.0f;

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

		texturesVbo = std::make_shared<VertexBuffer>();

		texturesVbo->add(glm::vec2(0.0f, 0.0f));
		texturesVbo->add(glm::vec2(1.0f, 0.0f));
		texturesVbo->add(glm::vec2(0.0f, -1.0f));
		texturesVbo->add(glm::vec2(1.0f, -1.0f));
		texturesVbo->add(glm::vec2(1.0f, 0.0f));
		texturesVbo->add(glm::vec2(0.0f, -1.0f));

		// Vertex Arrray
		vao = std::make_shared<VertexArray>();
		vao->setBuffer(0, positionsVbo);
		vao->setBuffer(1, texturesVbo);
	
		int w = 0;
		int h = 0;

		texture = std::make_shared<Texture>("../resources/textures/container001-blue.png", w, h);

		// Create Shader
		triangleShader = std::make_shared<ShaderProgram>();
		triangleShader->CreateShader("../resources/shaders/noLightVert.txt", "../resources/shaders/noLightFrag.txt");
	}

	void TriangleRenderer::onDisplay()
	{
		//std::cout << "Triangle Display" << std::endl;

		//glEnable(GL_DEPTH_TEST);

		// !!! Temporary deltatime whilst I test things !!!
		unsigned int currTime = SDL_GetTicks();
		unsigned int diffTime = currTime - prevTime;
		deltaTime = (diffTime / 1000.0f);
		// Makes sure it has the latest prev time. Otherwise it will make things go faster and faster
		prevTime = currTime;

		// Draw
		GLint modelLoc = glGetUniformLocation(triangleShader->getId(), "u_Model");
		GLint projectionLoc = glGetUniformLocation(triangleShader->getId(), "u_Projection");
		GLint viewLoc = glGetUniformLocation(triangleShader->getId(), "u_View");

		// Instruct opengl to use our shader program and vao
		glUseProgram(triangleShader->getId());
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindVertexArray(vao->getId());

		// Prepare perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(getTransform()->getModel()));

		// View
		glm::mat4 view(1.0f);
		const float radius = 10.0f;
		float camX = sin(deltaTime * radius);
		float camZ = cos(deltaTime * radius);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		// 3DGP Rotate
		//view = glm::rotate(view, glm::radians(rot), glm::vec3(0, 1, 0));
		//view = glm::translate(view, glm::vec3(0, 0, 4));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDisable(GL_DEPTH_TEST);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TriangleRenderer::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_UP))
		{
			getTransform()->move(glm::vec3(0, 0.5f, 0) * _deltaTime);
		}
		
		if (getKeyboard()->getKeyDown(SDLK_DOWN))
		{
			getTransform()->move(glm::vec3(0, -0.5f, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_LEFT))
		{
			getTransform()->move(glm::vec3(-0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_RIGHT))
		{
			getTransform()->move(glm::vec3(0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_r))
		{
			getTransform()->rotate(glm::vec3(0, 0.5f, 0) * _deltaTime);
		}

		// Camera
		const float cameraSpeed = 2.5f * deltaTime;

		if (getKeyboard()->getKeyDown(SDLK_w))
		{
			cameraPos += cameraSpeed * cameraFront;
		}

		if (getKeyboard()->getKeyDown(SDLK_s))
		{
			cameraPos -= cameraSpeed * cameraFront;
		}

		if (getKeyboard()->getKeyDown(SDLK_a))
		{
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		mouseUpdate();
	}

	void TriangleRenderer::mouseUpdate()
	{
		// Code from learnOpenGL - Camera
		if (firstMouse)
		{
			lastX = getMouse()->getMousePosition().x;
			lastY = getMouse()->getMousePosition().y;
			firstMouse = false;
		}

		float xoffset = getMouse()->getMousePosition().x -lastX;
		float yoffset = lastY - getMouse()->getMousePosition().y; // reversed since y-coordinates go from bottom to top
		lastX = getMouse()->getMousePosition().x;
		lastY = getMouse()->getMousePosition().y;

		float sensitivity = 0.1f;; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}
