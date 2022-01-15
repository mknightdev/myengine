#include "MeshRenderer.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Core.h"
#include "Entity.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

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
	void MeshRenderer::onInitialize()
	{
		std::cout << "Model Renderer Initialised" << std::endl;

		int w = 0;
		int h = 0;

		//albedoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_albedo.png", w, h);
		normalMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_normal.png", w, h);
		metallicMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_metallic.png", w, h);
		roughnessMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_roughness.png", w, h);
		aoMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_mixed_ao.png", w, h);

		// Create Shader
		shader = std::make_shared<myrenderer::ShaderProgram>();
		//shader->CreateShader("../resources/shaders/ambientVert.txt", "../resources/shaders/ambientFrag.txt");
		//shader->CreateShader("../resources/shaders/diffuseVert.txt", "../resources/shaders/diffuseFrag.txt");
		//shader->CreateShader("../resources/shaders/specularVert.txt", "../resources/shaders/specularFrag.txt");
		//shader->CreateShader("../resources/shaders/materialVert.txt", "../resources/shaders/materialFrag.txt");
		//shader->CreateShader("../resources/shaders/multiLightVert.txt", "../resources/shaders/multiLightFrag.txt");
		//shader->CreateShader("../resources/shaders/pbrVert.txt", "../resources/shaders/pbrFrag.txt");
		shader->CreateShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag.txt");

		shader->use();
		shader->setInt("albedoMap", 0);
		shader->setInt("normalMap", 1);
		shader->setInt("metallicMap", 2);
		shader->setInt("roughnessMap", 3);
		shader->setInt("aoMap", 4);

		/*****************************
		*
		*	LIGHT CUBE
		*
		******************************/

		// Vertex Buffer
		positionsVbo = std::make_shared<myrenderer::VertexBuffer>();
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

		lightVao = std::make_shared<myrenderer::VertexArray>();
		lightVao->setBuffer(0, positionsVbo);

		lightShader = std::make_shared<myrenderer::ShaderProgram>();
		lightShader->CreateShader("resources/shaders/lightCubeVert.txt", "resources/shaders/lightCubeFrag.txt");
	}

	/**
	* \brief Draws the model.
	*
	* Updates and draws the model loaded.
	*
	* \warning Can throw several exceptions if it can find the model, projection,
	* or view locations.
	*/
	void MeshRenderer::onDisplay()
	{
		shader->use();
		// Set uniforms
		GLint modelLoc = glGetUniformLocation(shader->getId(), "model");
		GLint projectionLoc = glGetUniformLocation(shader->getId(), "projection");
		GLint viewLoc = glGetUniformLocation(shader->getId(), "view");

		if (modelLoc == -1) { throw std::exception(); }
		if (projectionLoc == -1) { throw std::exception(); }
		if (viewLoc == -1) { throw std::exception(); }

		shader->setVec3("camPos", getCamera()->getCameraPos());

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

		// TODO: 
		// getCameraPos, getCameraFront, getCameraUp

		//DEBUGGING
		//std::cout << getCamera()->getCameraPos().x << ", " << getCamera()->getCameraPos().y << ", " << getCamera()->getCameraPos().z << std::endl;
		//view = lookAt(getCamera()->getCameraPos(), getCamera()->getCameraPos() + getCamera()->getCameraFront(), getCamera()->getCameraUp());
		
		view = lookAt(getCamera()->getCameraPos(), getCamera()->getCameraPos() + getCamera()->getCameraFront(), getCamera()->getCameraUp());
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
	void MeshRenderer::onTick(float _deltaTime)
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
			getTransform()->Move(vec3(-1.5f, 0, 0) * _deltaTime);
		}

		if (getKeyboard()->getKeyDown(SDLK_h))
		{
			getTransform()->Move(vec3(0.5f, 0, 0) * _deltaTime);
		}

		// Rotate Left
		if (getKeyboard()->getKeyDown(SDLK_r))
		{
			getTransform()->Rotate(vec3(0, 1, 0) * _deltaTime);
		}

		// Rotate Right
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

		// TODO:
		/*
			1) Get camera
				a) Go through entity
			2) Set new positions of camera after moving it
		*/
	}

	/**
	* \brief Sets the Mesh
	* 
	* Used for defining the mesh to load and stores it.
	*/
	void MeshRenderer::setMesh(std::shared_ptr<Mesh> _mesh)
	{
		vao = _mesh->vao;

		// Meshrender storing a mesh, not the vao
		// whereever vao use _mesh->vao
	}

	/**
	* \brief Sets the texture
	* 
	* Used for setting the albedo map of the model.
	*/
	void MeshRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		int w, h = 0;
		albedoMap = _texture->texture;
	}
}