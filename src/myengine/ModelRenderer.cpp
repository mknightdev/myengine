#include "ModelRenderer.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

#include "stb_image.h"

using namespace myrenderer;

// TODO: Move into own class
glm::vec3 cameraPos2 = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront2 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse2 = true;
float yaw2 = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially Rotate a bit to the left.
float pitch2 = 0.0f;
float lastX2 = 1280.0f / 2.0;
float lastY2 = 720.0f / 2.0;
float fov2 = 45.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

namespace myengine
{
	/**
	* \brief Initialises the model. 
	* 
	* Loads the model and texture, alongside the shaders to be used with it.
	* 
	* \see myrenderer::VertexArray
	* \see myrenderer::VertexBuffer
	* \see myrenderer::ShaderProgram
	* \see myrenderer::Texture
	*/
	void ModelRenderer::onInitialize()
	{
		std::cout << "Model Renderer Initialised" << std::endl;

		int w = 0;
		int h = 0;

		vao = std::make_shared<VertexArray>("../resources/models/grenade/grenade.obj");
		albedoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_albedo.png", w, h);
		normalMap = std::make_shared<Texture>("../resources/models/grenade/grenade_normal.png", w, h);
		metallicMap = std::make_shared<Texture>("../resources/models/grenade/grenade_metallic.png", w, h);
		roughnessMap = std::make_shared<Texture>("../resources/models/grenade/grenade_roughness.png", w, h);
		aoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_mixed_ao.png", w, h);
		emissiveMap = std::make_shared < Texture>("../resources/models/grenade/grenade_emissive.png", w, h);

		// Create Shader
		shader = std::make_shared<ShaderProgram>();
		shader->CreateShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");

		shader->use();
		shader->setInt("albedoMap", 0);
		shader->setInt("normalMap", 1);
		shader->setInt("metallicMap", 2);
		shader->setInt("roughnessMap", 3);
		shader->setInt("aoMap", 4);
		shader->setInt("emissiveMap", 5);

		/*****************************
		*
		*	LIGHT CUBE
		*
		******************************/

		// Vertex Buffer
		positionsVbo = std::make_shared<VertexBuffer>();
		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));

		positionsVbo->add(vec3(-0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, 0.5f));

		positionsVbo->add(vec3(-0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, 0.5f));

		positionsVbo->add(vec3(0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, 0.5f));

		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, -0.5f, -0.5f));

		positionsVbo->add(vec3(-0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, -0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, 0.5f));
		positionsVbo->add(vec3(-0.5f, 0.5f, -0.5f));

		lightVao = std::make_shared<VertexArray>();
		lightVao->setBuffer(0, positionsVbo);

		lightShader = std::make_shared<ShaderProgram>();
		lightShader->CreateShader("../resources/shaders/lightCubeVert.txt", "../resources/shaders/lightCubeFrag.txt");
	}

	/**
	* \brief Draws the model. 
	* 
	* Updates and draws the model loaded.
	* 
	* \warning Can throw several exceptions if it can find the model, projection,
	* or view locations.
	*/
	void ModelRenderer::onDisplay()
	{
		shader->use();
		// Set uniforms
		GLint modelLoc = glGetUniformLocation(shader->getId(), "model");
		GLint projectionLoc = glGetUniformLocation(shader->getId(), "projection");
		GLint viewLoc = glGetUniformLocation(shader->getId(), "view");

		if (modelLoc == -1) { throw std::exception(); }
		if (projectionLoc == -1) { throw std::exception(); }
		if (viewLoc == -1) { throw std::exception(); }

		shader->setVec3("camPos", cameraPos2);

		// Light
		vec3 lightColour;
		lightColour.x = 1.0f;
		lightColour.y = 1.0f;
		lightColour.z = 1.0f;
		vec3 diffuseColour = lightColour * vec3(0.5f);
		vec3 ambientColour = lightColour * vec3(0.2f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, albedoMap->GetId());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap->GetId());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, metallicMap->GetId());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, roughnessMap->GetId());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, aoMap->GetId());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, emissiveMap->GetId());
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
		view = lookAt(cameraPos2, cameraPos2 + cameraFront2, cameraUp2);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));

		// Upload the projection matrix
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, vao->getVertCount());

		/*****************************
		*
		*	LIGHT CUBE
		*
		******************************/

		lightShader->use();
		glBindVertexArray(lightVao->getId());
		
		// Set the cube's colour to match the colour of the light emitting
		lightShader->setVec3("lightCubeColour", lightColour);

		glUniformMatrix4fv(glGetUniformLocation(lightShader->getId(), "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(lightShader->getId(), "view"), 1, GL_FALSE, value_ptr(view));

		for (unsigned int i = 0; i < 4; i++)
		{
			mat4 lightModel = mat4(1.0f);
			lightModel = translate(lightModel, pointLightPositions[i]);
			lightModel = scale(lightModel, vec3(0.2f));

			shader->use();
			shader->setVec3("lightPositions[" + std::to_string(i) + "]", pointLightPositions[i]);
			shader->setVec3("lightColours[" + std::to_string(i) + "]", lightColour);

			lightShader->use();
			glUniformMatrix4fv(glGetUniformLocation(lightShader->getId(), "model"), 1, GL_FALSE, value_ptr(lightModel));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}

	/**
	* \brief The position of the model. 
	* 
	* Moves and updates the position of the model.
	* 
	* \param _deltaTime passed through from Core and is used to multiply the updated position with.
	* \warning Multiplying without _deltaTime may result in some unexpected behaviours.
	* \see Transform
	*/
	void ModelRenderer::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_t))
		{
			getTransform()->Move(vec3(0, 0, 0.5f) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_g))
		{
			getTransform()->Move(vec3(0, 0, -0.5f) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_f))
		{
			getTransform()->Move(vec3(-0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_h))
		{
			getTransform()->Move(vec3(0.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_r))
		{
			getTransform()->Rotate(vec3(0, 1, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_y))
		{
			getTransform()->Rotate(vec3(0, -1, 0) * _deltaTime);
		}

		// Move upwards
		if (getKeyboard()->getKeyDown(SDLK_LSHIFT))
		{
			getTransform()->Move(vec3(0, 0.5f, 0) * _deltaTime);
		}

		// Move downwards
		if (getKeyboard()->getKeyDown(SDLK_LCTRL))
		{
			getTransform()->Move(vec3(0, -0.5f, 0) * _deltaTime);
		}


		// Camera
		const float cameraSpeed = 2.5f * deltaTime();

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
			cameraPos2 -= normalize(cross(cameraFront2, cameraUp2)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos2 += normalize(cross(cameraFront2, cameraUp2)) * cameraSpeed;
		}

		mouseUpdate();

		// TODO:
		/*
			1) Get camera
				a) Go through entity
			2) Set new positions of camera after moving it
		*/
	}

	/**
	* \brief Update mouse position
	* 
	* Updates the mouse position to Move the camera.
	*/
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

		vec3 front;
		front.x = cos(radians(yaw2)) * cos(radians(pitch2));
		front.y = sin(radians(pitch2));
		front.z = sin(radians(yaw2)) * cos(radians(pitch2));
		cameraFront2 = normalize(front);
	}
}
