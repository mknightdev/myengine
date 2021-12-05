#include "PBR.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

#include "stb_image.h"
#include "GL\glew.h"

using namespace myrenderer;

// TODO: move into own class
glm::vec3 cameraPos2 = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront2 = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp2 = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse2 = true;
float yaw2 = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
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
	void PBR::onInitialize()
	{
		std::cout << "Model Renderer Initialised" << std::endl;

		int w = 0;
		int h = 0;

		// Load model and texture
		//vao = std::make_shared<VertexArray>("../resources/models/skeleton/skeleton.obj");
		//texture = std::make_shared<Texture>("../resources/models/skeleton/skeleton_diffuse.png", w, h);

		vao = std::make_shared<VertexArray>("../resources/models/grenade/grenade.obj");
		albedoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_albedo.png", w, h);
		normalMap = std::make_shared<Texture>("../resources/models/grenade/grenade_normal.png", w, h);
		metallicMap = std::make_shared<Texture>("../resources/models/grenade/grenade_metallic.png", w, h);
		roughnessMap = std::make_shared<Texture>("../resources/models/grenade/grenade_roughness.png", w, h);
		aoMap = std::make_shared<Texture>("../resources/models/grenade/grenade_mixed_ao.png", w, h);
		emissiveMap = std::make_shared < Texture>("../resources/models/grenade/grenade_emissive.png", w, h);

		// Create Shader
		shader = std::make_shared<ShaderProgram>();
		//shader->CreateShader("../resources/shaders/ambientVert.txt", "../resources/shaders/ambientFrag.txt");
		//shader->CreateShader("../resources/shaders/diffuseVert.txt", "../resources/shaders/diffuseFrag.txt");
		//shader->CreateShader("../resources/shaders/specularVert.txt", "../resources/shaders/specularFrag.txt");
		//shader->CreateShader("../resources/shaders/materialVert.txt", "../resources/shaders/materialFrag.txt");
		//shader->CreateShader("../resources/shaders/multiLightVert.txt", "../resources/shaders/multiLightFrag.txt");
		//shader->CreateShader("../resources/shaders/pbrVert.txt", "../resources/shaders/pbrFrag.txt");
		shader->CreateShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbr/pbrTexFrag.txt");

		cubemapShader = std::make_shared<ShaderProgram>();
		cubemapShader->CreateShader("../resources/shaders/pbr/cubemapVert.txt", "../resources/shaders/pbr/equirectangular_to_cubemapFrag.txt");

		backgroundShader = std::make_shared<ShaderProgram>();
		backgroundShader->CreateShader("../resources/shaders/pbr/backgroundVert.txt", "../resources/shaders/pbr/backgroundFrag.txt");

		backgroundShader->use();
		backgroundShader->setInt("environmentMap", 0);

		shader->use();
		shader->setInt("albedoMap", 0);
		shader->setInt("normalMap", 1);
		shader->setInt("metallicMap", 2);
		shader->setInt("roughnessMap", 3);
		shader->setInt("aoMap", 4);
		shader->setInt("emissiveMap", 5);

		// Setup framebuffer
		unsigned int captureFBO;
		unsigned int captureRBO;
		glGenFramebuffers(1, &captureFBO);
		glGenRenderbuffers(1, &captureRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

		// Load HDR environment map
		//-------------------------
		stbi_set_flip_vertically_on_load(true);
		int width, height, nrComponents;
		float* data = stbi_loadf("../resources/shaders/pbr/Factory_Catwalk_Env.hdr", &width, &height, &nrComponents, 0);
		unsigned int hdrTexture;
		if (data)
		{
			glGenTextures(1, &hdrTexture);
			glBindTexture(GL_TEXTURE_2D, hdrTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);

			std::cout << "Image loaded" << std::endl;
		}
		else
		{
			std::cout << "Failed to load HDR image" << std::endl;
		}

		// Setup cubemap to render to and attach to framebuffer
		envCubeMap;
		glGenTextures(1, &envCubeMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
		for (unsigned int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Setup projection for capturing data onto the 6 cubemap face directions---
		captureProjection = perspective(radians(90.0f), 1.0f, 0.1f, 10.0f);

		// PBR convert HDR equirectangular environment map to cubemap equivalent 
		cubemapShader->use();
		cubemapShader->setInt("equirectangularMap", 0);
		cubemapShader->setMat4("projection", captureProjection);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, hdrTexture);

		glViewport(0, 0, 512, 512);	// don't forget to configure the viewport to capture dimensions
		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		for (unsigned int i = 0; i < 6; ++i)
		{
			cubemapShader->setMat4("view", captureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubeMap, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			renderCube();
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// initialise static shader uniforms before rendering
		projection = perspective(radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);
		shader->use();
		shader->setMat4("projection", projection);
		backgroundShader->use();
		backgroundShader->setMat4("projection", projection);

		// before rendering, configure the viewport to the original framebuffer's screen dimensions
		glViewport(0, 0, 1280, 720);

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

		glDepthFunc(GL_LEQUAL);
	}

	/**
	* \brief Draws the model.
	*
	* Updates and draws the model loaded.
	*
	* \warning Can throw several exceptions if it can find the model, projection,
	* or view locations.
	*/
	void PBR::onDisplay()
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

		// Skybox
		backgroundShader->use();
		backgroundShader->setMat4("view", view);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
		renderCube();

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
	void PBR::onTick(float _deltaTime)
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
	* Updates the mouse position to move the camera.
	*/
	void PBR::mouseUpdate()
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

	// renderCube() renders a 1x1 3D cube in NDC.
	// -------------------------------------------------
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	void PBR::renderCube()
	{
		// initialize (if necessary)
		if (cubeVAO == 0)
		{
			float vertices[] = {
				// back face
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};
			glGenVertexArrays(1, &cubeVAO);
			glGenBuffers(1, &cubeVBO);
			// fill buffer
			glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			// link vertex attributes
			glBindVertexArray(cubeVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		// render Cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
}
