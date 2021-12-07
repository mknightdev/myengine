#include "MeshRenderer.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"
#include "Mesh.h"
#include "Texture.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

// TODO: move into own class
glm::vec3 cameraPos3 = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront3 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp3 = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse3 = true;
float yaw3 = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch3 = 0.0f;
float lastX3 = 1280.0f / 2.0;
float lastY3 = 720.0f / 2.0;
float fov3 = 45.0f;

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

		// Load model and texture
		//vao = std::make_shared<VertexArray>("../resources/models/skeleton/skeleton.obj");
		//texture = std::make_shared<Texture>("../resources/models/skeleton/skeleton_diffuse.png", w, h);


		//albedoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_albedo.png", w, h);
		normalMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_normal.png", w, h);
		metallicMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_metallic.png", w, h);
		roughnessMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_roughness.png", w, h);
		aoMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_mixed_ao.png", w, h);
		emissiveMap = std::make_shared<myrenderer::Texture>("resources/models/grenade/grenade_emissive.png", w, h);

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
		shader->setInt("emissiveMap", 5);


		//shader->setInt("material.diffuse", 0);
		//shader->setInt("diffuse", 0);
		//shader->setVec3("albedo", 0.5f, 0.0f, 0.0f);
		//shader->setFloat("ao", 1.0f);
		//shader->setFloat("metallic", 0.0f);
		//shader->setFloat("roughness", 0.0f);

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

		//shader->setVec3("light.position", lightPos);
		shader->setVec3("camPos", cameraPos3);

		//shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		//shader->setFloat("material.shininess", 64.0f);

		//// directional light
		//shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		//shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		//shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		//shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

  //      // point light 1
  //      shader->setVec3("pointLights[0].position", pointLightPositions[0]);
  //      shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
  //      shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
  //      shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
  //      shader->setFloat("pointLights[0].constant", 1.0f);
  //      shader->setFloat("pointLights[0].linear", 0.09);
  //      shader->setFloat("pointLights[0].quadratic", 0.032);
  //      // point light 2
  //      shader->setVec3("pointLights[1].position", pointLightPositions[1]);
  //      shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
  //      shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
  //      shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
  //      shader->setFloat("pointLights[1].constant", 1.0f);
  //      shader->setFloat("pointLights[1].linear", 0.09);
  //      shader->setFloat("pointLights[1].quadratic", 0.032);
  //      // point light 3
  //      shader->setVec3("pointLights[2].position", pointLightPositions[2]);
  //      shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
  //      shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
  //      shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
  //      shader->setFloat("pointLights[2].constant", 1.0f);
  //      shader->setFloat("pointLights[2].linear", 0.09);
  //      shader->setFloat("pointLights[2].quadratic", 0.032);
  //      // point light 4
  //      shader->setVec3("pointLights[3].position", pointLightPositions[3]);
  //      shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
  //      shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
  //      shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
  //      shader->setFloat("pointLights[3].constant", 1.0f);
  //      shader->setFloat("pointLights[3].linear", 0.09);
  //      shader->setFloat("pointLights[3].quadratic", 0.032);

		// Light
		vec3 lightColour;
		lightColour.x = 1.0f;
		lightColour.y = 1.0f;
		lightColour.z = 1.0f;
		vec3 diffuseColour = lightColour * vec3(0.5f);
		vec3 ambientColour = lightColour * vec3(0.2f);

		//shader->setVec3("pointLight.ambient", ambientColour);
		//shader->setVec3("pointLight.diffuse", diffuseColour);
		//shader->setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);

		// world transformation
		//glm::mat4 model = glm::mat4(1.0f);
		//shader->setMat4("model", model);

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
		view = lookAt(cameraPos3, cameraPos3 + cameraFront3, cameraUp3);
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
			cameraPos3 += cameraSpeed * cameraFront3;
		}

		if (getKeyboard()->getKeyDown(SDLK_s))
		{
			cameraPos3 -= cameraSpeed * cameraFront3;
		}

		if (getKeyboard()->getKeyDown(SDLK_a))
		{
			cameraPos3 -= normalize(cross(cameraFront3, cameraUp3)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos3 += normalize(cross(cameraFront3, cameraUp3)) * cameraSpeed;
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
	* Updates the mouse position to move the camera.
	*/
	void MeshRenderer::mouseUpdate()
	{
		// Code from learnOpenGL - Camera
		if (firstMouse3)
		{
			lastX3 = getMouse()->getMousePosition().x;
			lastY3 = getMouse()->getMousePosition().y;
			firstMouse3 = false;
		}

		float xoffset = getMouse()->getMousePosition().x - lastX3;
		float yoffset = lastY3 - getMouse()->getMousePosition().y; // reversed since y-coordinates go from bottom to top
		lastX3 = getMouse()->getMousePosition().x;
		lastY3 = getMouse()->getMousePosition().y;

		float sensitivity = 0.1f;; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw3 += xoffset;
		pitch3 += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch3 > 89.0f)
			pitch3 = 89.0f;
		if (pitch3 < -89.0f)
			pitch3 = -89.0f;

		vec3 front;
		front.x = cos(radians(yaw3)) * cos(radians(pitch3));
		front.y = sin(radians(pitch3));
		front.z = sin(radians(yaw3)) * cos(radians(pitch3));
		cameraFront3 = normalize(front);
	}

	void MeshRenderer::setMesh(std::shared_ptr<Mesh> _mesh)
	{
		vao = _mesh->vao;

		// Meshrender storing a mesh, not the vao
		// whereever vao use _mesh->vao
	}

	void MeshRenderer::setTexture(std::shared_ptr<Texture> _texture)
	{
		int w, h = 0;
		albedoMap = _texture->texture;
	}
}