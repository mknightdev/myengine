#include "TriangleRenderer.h"
#include "Keyboard.h"
#include "Transform.h"
#include "Mouse.h"
#include "Core.h"
#include "Environment.h"
#include "mymath.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

using namespace myrenderer;

// TODO: move into own class
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float _yaw	= -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float _pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov	= 45.0f;

namespace myengine
{
	/**
	* \brief Initialises the triangle.
	*
	* Creates the triangle and texture, alongside the shaders to be used with it.
	*
	* \see myrenderer::VertexArray
	* \see myrenderer::VertexBuffer
	* \see myrenderer::ShaderProgram
	* \see myrenderer::Texture
	*/
	void TriangleRenderer::onInitialize()
	{
		std::cout << "Triangle Initialised" << std::endl;

		// Vertex Buffer
		positionsVbo = std::make_shared<VertexBuffer>();
		positionsVbo->add(vec3(0.0f, 0.5f, 0.0f));
		positionsVbo->add(vec3(-0.5f, -0.5f, 0.0f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.0f));

		texturesVbo = std::make_shared<VertexBuffer>();

		texturesVbo->add(vec2(0.0f, 0.0f));
		texturesVbo->add(vec2(1.0f, 0.0f));
		texturesVbo->add(vec2(0.0f, -1.0f));
		texturesVbo->add(vec2(1.0f, -1.0f));
		texturesVbo->add(vec2(1.0f, 0.0f));
		texturesVbo->add(vec2(0.0f, -1.0f));

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

	/**
	* \brief Draws the triangle.
	*
	* Updates and draws the triangle created.
	*
	* \warning Can throw several exceptions if it can find the model, projection,
	* or view locations.
	*/
	void TriangleRenderer::onDisplay()
	{
		// Draw
		GLint modelLoc = glGetUniformLocation(triangleShader->getId(), "u_Model");
		GLint projectionLoc = glGetUniformLocation(triangleShader->getId(), "u_Projection");
		GLint viewLoc = glGetUniformLocation(triangleShader->getId(), "u_View");

		// Instruct opengl to use our shader program and vao
		glUseProgram(triangleShader->getId());
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindVertexArray(vao->getId());

		// Prepare perspective projection matrix
		mat4 projection = perspective(radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		// Upload the model matrix
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(getTransform()->getModel()));

		// View
		mat4 view(1.0f);
		const float radius = 10.0f;
		float camX = sin(deltaTime() * radius);
		float camZ = cos(deltaTime() * radius);
		view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}

	/**
	* \brief The position of the triangle.
	*
	* Moves and updates the position of the triangle.
	*
	* \param _deltaTime passed through from Core and is used to multiply the updated position with.
	* \warning Multiplying without _deltaTime may result in some unexpected behaviours.
	* \see Transform
	*/
	void TriangleRenderer::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_UP))
		{
			getTransform()->Move(vec3(0, 0.5f, 0) * _deltaTime);
		}
		
		if (getKeyboard()->getKeyDown(SDLK_DOWN))
		{
			getTransform()->Move(vec3(0, -0.5f, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_LEFT))
		{
			getTransform()->Move(vec3(-0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_RIGHT))
		{
			getTransform()->Move(vec3(0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_r))
		{
			getTransform()->Rotate(vec3(0, 0.5f, 0) * _deltaTime);
		}

		// Camera
		const float cameraSpeed = 2.5f * deltaTime();

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
			cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		mouseUpdate();
	}

	/**
	* \brief Update mouse position
	*
	* Updates the mouse position to move the camera.
	*/
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

		_yaw += xoffset;
		_pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		vec3 front;
		front.x = cos(radians(_yaw)) * cos(radians(_pitch));
		front.y = sin(radians(_pitch));
		front.z = sin(radians(_yaw)) * cos(radians(_pitch));
		cameraFront = normalize(front);
	}
}
