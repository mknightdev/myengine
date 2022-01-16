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

		// Create Shader
		shader = std::make_shared<myrenderer::ShaderProgram>();
		shader->CreateShader("resources/shaders/multiLightVert.txt", "resources/shaders/multiLightFrag.txt");

		shader->use();
		shader->setInt("material.diffuse", 0);

		//============
		// LIGHT CUBE
		//============
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

		shader->setVec3("viewPos", getCamera()->getCameraPos());
		shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader->setFloat("material.shininess", 64.0f);

		// directional light
		shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		// point light 1
		shader->setVec3("pointLights[0].position", pointLightPositions[0]);
		shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		shader->setFloat("pointLights[0].constant", 1.0f);
		shader->setFloat("pointLights[0].linear", 0.09);
		shader->setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		shader->setVec3("pointLights[1].position", pointLightPositions[1]);
		shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		shader->setFloat("pointLights[1].constant", 1.0f);
		shader->setFloat("pointLights[1].linear", 0.09);
		shader->setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		shader->setVec3("pointLights[2].position", pointLightPositions[2]);
		shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		shader->setFloat("pointLights[2].constant", 1.0f);
		shader->setFloat("pointLights[2].linear", 0.09);
		shader->setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		shader->setVec3("pointLights[3].position", pointLightPositions[3]);
		shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		shader->setFloat("pointLights[3].constant", 1.0f);
		shader->setFloat("pointLights[3].linear", 0.09);
		shader->setFloat("pointLights[3].quadratic", 0.032);

		// Light
		vec3 lightColour;
		lightColour.x = 1.0f;
		lightColour.y = 1.0f;
		lightColour.z = 1.0f;
		vec3 diffuseColour = lightColour * vec3(0.5f);
		vec3 ambientColour = lightColour * vec3(0.2f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, albedoMap->GetId());
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

	void MeshRenderer::setRadius(float _radius)
	{
		radius = _radius;
	}

	float MeshRenderer::getRadius()
	{
		return radius;
	}
}