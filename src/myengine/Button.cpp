#include "Button.h"
#include "Mouse.h"

#include <iostream>
#include <stb_image.h>
#include <myrenderer/myrenderer.h>
#include "mymath.h"

namespace myengine
{
	void Button::onInitialize()
	{
		std::cout << "Button Init" << std::endl;

		positionsVbo = std::make_shared<myrenderer::VertexBuffer>();

		// Added to data vector (floats)
		// Tri 1
		positionsVbo->add(glm::vec3(-0.5f, -0.5f, 0.0f));	// Bottom Left
		positionsVbo->add(glm::vec3(0.5f, -0.5f, 0.0f));	// Bottom Right
		positionsVbo->add(glm::vec3(-0.5f, 0.5f, 0.0f));	// Top Right

		// Tri 2
		positionsVbo->add(glm::vec3(0.5f, 0.5f, 0.0f));		// Top Right
		positionsVbo->add(glm::vec3(0.5f, -0.5f, 0.0f));	// Bottom Right
		positionsVbo->add(glm::vec3(-0.5f, 0.5f, 0.0f));	// Top Left

		texturesVbo = std::make_shared<myrenderer::VertexBuffer>();

		texturesVbo->add(glm::vec2(0.0f, 0.0f));
		texturesVbo->add(glm::vec2(1.0f, 0.0f));
		texturesVbo->add(glm::vec2(0.0f, -1.0f));
		texturesVbo->add(glm::vec2(1.0f, -1.0f));
		texturesVbo->add(glm::vec2(1.0f, 0.0f));
		texturesVbo->add(glm::vec2(0.0f, -1.0f));

		vao = std::make_shared<myrenderer::VertexArray>();
		vao->setBuffer(0, positionsVbo);
		vao->setBuffer(1, texturesVbo);

		int w = 0;
		int h = 0;
		texture = std::make_shared<myrenderer::Texture>(stbi_load("resources/textures/add.png", &w, &h, NULL, 4), w, h);

		shader = std::make_shared<myrenderer::ShaderProgram>();
		shader->CreateShader("resources/shaders/uiVert.txt", "resources/shaders/uiFrag.txt");
	}

	void Button::onDisplay() 
	{
		//shader->use();
		GLint modelLocUI = glGetUniformLocation(shader->getId(), "u_Model");
		GLint projectionLocUI = glGetUniformLocation(shader->getId(), "u_Projection");

		if (modelLocUI == -1)
		{
			throw std::exception();
		}
		if (projectionLocUI == -1)
		{
			throw std::exception();
		}

	
		glUseProgram(shader->getId());
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
		glBindVertexArray(vao->getId());

		// Drawing
		//mat4 projection = perspective(radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

		mat4 projection = ortho(0.0f, (float)1280, 0.0f, (float)720, 0.0f, 1.0f);

		mat4 UIModel(1.0f);
		UIModel = translate(UIModel, vec3(100, 720 - 100, 0));
		UIModel = scale(UIModel, vec3(100, 100, 1));

		glUniformMatrix4fv(modelLocUI, 1, GL_FALSE, value_ptr(UIModel));
		glUniformMatrix4fv(projectionLocUI, 1, GL_FALSE, value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, vao->getVertCount());

		//std::shared_ptr<myrenderer::Model> button = std::make_shared<myrenderer::Model>();
		////button->Bind(texture->GetId(), vao->getId());
		//glBindTexture(GL_TEXTURE_2D, texture->GetId());
		//glBindVertexArray(vao->getId());
		//button->SetPosition(1280 / 2, 720 / 2, 0);
		//button->SetScale(50, 50, 1);
		//button->Draw(modelLocUI, projectionLocUI, projection, 6);
	}

	void Button::onTick() 
	{
		// X and Y needs to have 25 subtracted from it
		if (intersect(getMouse()->getMousePosition(), vec4(615, 335, 50, 50)) && getMouse()->isButtonDown())
		{
			std::cout << "Intersecting" << std::endl;
		}
	}
	void Button::onTick(float _deltaTime) {}

	void Button::setTexture(std::string _fileName)
	{
		int w, h = 0;
		std::cout << _fileName.c_str() << std::endl;
		texture = std::make_shared<myrenderer::Texture>(stbi_load(_fileName.c_str(), &w, &h, NULL, 4), w, h);
	}

	void Button::setShader(const GLchar* _vert, const GLchar* _frag)
	{
		shader = std::make_shared<myrenderer::ShaderProgram>();
		std::cout << _vert << ", " << _frag << std::endl;
		shader->CreateShader(_vert, _frag);
	}

	bool Button::intersect(vec2 _mouse, vec4 _rectangle)
	{
		if (_mouse.x < _rectangle.x)
		{
			return false;
		}

		if (_mouse.x > _rectangle.x + _rectangle.z)
		{
			return false;
		}

		if (_mouse.y < _rectangle.y)
		{
			return false;
		}

		// W is for vec4 height
		if (_mouse.y > _rectangle.y + _rectangle.w)
		{
			return false;
		}
		return true;
	}
}