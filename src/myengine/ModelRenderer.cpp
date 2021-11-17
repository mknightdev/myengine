#include "ModelRenderer.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

using namespace myrenderer;

// TODO: move into own class
glm::vec3 cameraPos2 = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront2 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse2 = true;
float yaw2 = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch2 = 0.0f;
float lastX2 = 800.0f / 2.0;
float lastY2 = 600.0 / 2.0;
float fov2 = 45.0f;

namespace myengine
{
	void ModelRenderer::onInitialize()
	{
		std::cout << "Model Renderer Initialised" << std::endl;

		int w = 0;
		int h = 0;

		// Load model and texture
		vao = std::make_shared<VertexArray>("../resources/models/curuthers/curuthers.obj");
		texture = std::make_shared<Texture>("../resources/models/curuthers/Whiskers_diffuse.png", w, h);

		// Create Shader
		shader = std::make_shared<ShaderProgram>();
		shader->CreateShader("../resources/shaders/ambientVert.txt", "../resources/shaders/ambientFrag.txt");
	}

	void ModelRenderer::onDisplay()
	{

		// !!! Temporary deltatime whilst I test things !!!
		unsigned int currTime = SDL_GetTicks();
		unsigned int diffTime = currTime - prevTime;
		deltaTime = (diffTime / 1000.0f);
		// Makes sure it has the latest prev time. Otherwise it will make things go faster and faster
		prevTime = currTime;

		// Draw
		GLint modelLoc = glGetUniformLocation(shader->getId(), "u_Model");
		GLint projectionLoc = glGetUniformLocation(shader->getId(), "u_Projection");
		GLint viewLoc = glGetUniformLocation(shader->getId(), "u_View");

		if (modelLoc == -1) { throw std::exception(); }
		if (projectionLoc == -1) { throw std::exception(); }
		if (viewLoc == -1) { throw std::exception(); }

		// Instruct opengl to use our shader program and vao
		shader->use();
		//glUseProgram(shader->getId());
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindVertexArray(vao->getId());

		// Prepare perspective projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(getTransform()->getModel()));

		//// 3DGP Rotate
		//glm::mat4 view(1.0f);
		////view = glm::rotate(view, glm::radians(rot), glm::vec3(0, 1, 0));
		//view = glm::translate(view, glm::vec3(0, 0, 15));

		// View
		glm::mat4 view(1.0f);
		const float radius = 10.0f;
		float camX = sin(deltaTime * radius);
		float camZ = cos(deltaTime * radius);
		view = glm::lookAt(cameraPos2, cameraPos2 + cameraFront2, cameraUp2);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, vao->getVertCount());
		//glDisable(GL_DEPTH_TEST);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void ModelRenderer::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_t))
		{
			getTransform()->move(glm::vec3(0, 0.5f, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_g))
		{
			getTransform()->move(glm::vec3(0, -0.5f, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_f))
		{
			getTransform()->move(glm::vec3(-0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_h))
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
			cameraPos2 += cameraSpeed * cameraFront2;
		}

		if (getKeyboard()->getKeyDown(SDLK_s))
		{
			cameraPos2 -= cameraSpeed * cameraFront2;
		}

		if (getKeyboard()->getKeyDown(SDLK_a))
		{
			cameraPos2 -= glm::normalize(glm::cross(cameraFront2, cameraUp2)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos2 += glm::normalize(glm::cross(cameraFront2, cameraUp2)) * cameraSpeed;
		}

		mouseUpdate();
	}

	void ModelRenderer::mouseUpdate()
	{
		// Code from learnOpenGL - Camera
		if (firstMouse2)
		{
			lastX2 = getMouse()->getMousePosition().x;
			lastY2 = getMouse()->getMousePosition().y;
			firstMouse2 = false;
		}

		float xoffset = getMouse()->getMousePosition().x - lastX2;
		float yoffset = lastY2 - getMouse()->getMousePosition().y; // reversed since y-coordinates go from bottom to top
		lastX2 = getMouse()->getMousePosition().x;
		lastY2 = getMouse()->getMousePosition().y;

		float sensitivity = 0.1f;; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw2 += xoffset;
		pitch2 += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch2 > 89.0f)
			pitch2 = 89.0f;
		if (pitch2 < -89.0f)
			pitch2 = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw2)) * cos(glm::radians(pitch2));
		front.y = sin(glm::radians(pitch2));
		front.z = sin(glm::radians(yaw2)) * cos(glm::radians(pitch2));
		cameraFront2 = glm::normalize(front);
	}
}
