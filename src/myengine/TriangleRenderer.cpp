#include <myrenderer\myrenderer.h>
#include "TriangleRenderer.h"
#include <SDL2\SDL.h>

#include <iostream>

using namespace myrenderer;

namespace myengine
{
	void TriangleRenderer::onInitialize()
	{
		std::cout << "Triangle Initialised" << std::endl;

		// Create OpenGL vertex buffer, vertex array and shader capable of drawing a triangle

		// Raw Code Attempt
		/*
		/// <summary>
		/// Vertex Buffer
		/// </summary>
		const GLfloat positions[] = {
			  0.0f, 0.5f, 0.0f,
			  -0.5f, -0.5f, 0.0f,
			  0.5f, -0.5f, 0.0f
		};

		GLuint positionsVboId = 0;

		// Create a new VBO on the GPU and bind it
		glGenBuffers(1, &positionsVboId);

		if (!positionsVboId)
		{
			throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

		// Upload a copy of the data from memory into the new VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		// Reset the state
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/// <summary>
		/// Vertex Array
		/// </summary>

		GLuint vaoId = 0;

		// Create a new VAO on the GPU and bind it
		glGenVertexArrays(1, &vaoId);

		if (!vaoId)
		{
			throw std::exception();
		}

		glBindVertexArray(vaoId);

		// Bind the position VBO, assign it to position 0 on the bound VAO
		// and flag it to be used
		glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			3 * sizeof(GLfloat), (void*)0);

		glEnableVertexAttribArray(0);

		// Reset the state
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/// <summary>
		/// Vertex Shader
		/// </summary>
		const GLchar* vertexShaderSrc =
			"attribute vec3 in_Position;            " \
			"                                       " \
			"void main()                            " \
			"{                                      " \
			" gl_Position = vec4(in_Position, 1.0); " \
			"}                                      ";

		// Create a new vertex shader, attach source code, compile it and
		// check for errors.
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
		glCompileShader(vertexShaderId);
		GLint success = 0;
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		/// <summary>
		/// Fragment Shader
		/// </summary>
		const GLchar* fragmentShaderSrc =
			"void main()                       " \
			"{                                 " \
			" gl_FragColor = vec4(0, 0, 1, 1); " \
			"}                                 ";

		// Create a new fragment shader, attach source code, compile it and
		// check for errors.
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
		glCompileShader(fragmentShaderId);
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}
		
		/// <summary>
		/// Shader Program
		/// </summary>
		// Create new shader program and attach our shader objects
		GLuint programId = glCreateProgram();
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		// Ensure the VAO "position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(programId, 0, "in_Position");

		// Perform the link and check for failure
		glLinkProgram(programId);
		glGetProgramiv(programId, GL_LINK_STATUS, &success);

		if (!success)
		{
			throw std::exception();
		}

		// Detach and destroy the shader objects. These are no longer needed
		// because we now have a complete shader program.
		glDetachShader(programId, vertexShaderId);
		glDeleteShader(vertexShaderId);
		glDetachShader(programId, fragmentShaderId);
		glDeleteShader(fragmentShaderId);

		/// <summary>
		/// Submit for Drawing
		/// </summary>
		
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glUseProgram(0);
		*/

		// Render Library Attempt
		// Vertex Buffer
		std::shared_ptr<VertexBuffer> positionsVbo = std::make_shared<VertexBuffer>();
		positionsVbo->add(glm::vec3(0.0f, 0.5f, 0.0f));
		positionsVbo->add(glm::vec3(-0.5f, -0.5f, 0.0f));
		positionsVbo->add(glm::vec3(0.5f, -0.5f, 0.0f));

		// Vertex Arrray
		std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
		vao->setBuffer(0, positionsVbo);
		vaoId = vao->getId();

		// Shader Sources
		// TODO: Pass through function, or read in from text file
		const GLchar* vertexShaderSrc =
			"attribute vec3 in_Position;            " \
			"                                       " \
			"void main()                            " \
			"{                                      " \
			" gl_Position = vec4(in_Position, 1.0); " \
			"}                                      ";

		const GLchar* fragmentShaderSrc =
			"void main()                       " \
			"{                                 " \
			" gl_FragColor = vec4(0, 0, 1, 1); " \
			"}                                 ";

		// Create Shader
		std::shared_ptr<ShaderProgram> triangleShader = std::make_shared<ShaderProgram>();
		triangleShader->CreateShader(vertexShaderSrc, fragmentShaderSrc);
		programId = triangleShader->getId();
	}

	void TriangleRenderer::onDisplay()
	{
		std::cout << "Triangle Display" << std::endl;
	}

	void TriangleRenderer::onTick()
	{
		// Draw
		// Instruct opengl to use our shader program and vao
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		// Draw 3 vertices
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);

		glBindVertexArray(0);
		glUseProgram(0);
	}

}