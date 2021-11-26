#include "ShaderProgram.h"
#include "myengine/Exception.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace myrenderer
{
	GLuint ShaderProgram::getId()
	{
		return programID;
	}

	void ShaderProgram::CreateShader(const GLchar* vertSrc, const GLchar* fragSrc)
	{
		// Read in from file
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		
		// Ensure the objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open files
			vShaderFile.open(vertSrc);
			fShaderFile.open(fragSrc);
			std::stringstream vShaderStream, fShaderStream;

			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// Close file handlers
			vShaderFile.close();
			fShaderFile.close();
			
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		GLuint vertex, fragment;
		int success;
		char infoLog[512];

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		// Print errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		// Print errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
		}

		// Shader Program
		programID = glCreateProgram();

		// Attach shaders to the programm
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);

		// Link the program
		glLinkProgram(programID);

		// Print linking errors if any
		glGetProgramiv(programID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(programID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// Delete the shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		// Set the current program to be used.
		glUseProgram(programID);
	}

	GLuint ShaderProgram::GetSource(const GLchar* source, GLuint type)
	{
		GLuint id = glCreateShader(type);
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		// Error checking
		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		// If result is false, it didn't compile successfully. 
		if (!success)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char message[LOG_LENGTH];
			glGetShaderInfoLog(id, LOG_LENGTH, NULL, message);

			// Display error
			if (type == GL_VERTEX_SHADER)
			{
				std::cout << "Failed to compile VERTEX shader" << std::endl;
				std::cout << message << std::endl;
			}
			else
			{
				std::cout << "Failed to compile FRAGMENT shader" << std::endl;
				std::cout << message << std::endl;
			}
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	void ShaderProgram::use()
	{
		glUseProgram(programID);
	}

	void ShaderProgram::setVec3(const std::string& _name, const glm::vec3& _value) const
	{
		glUniform3fv(glGetUniformLocation(programID, _name.c_str()), 1, &_value[0]);

		if (glGetUniformLocation(programID, _name.c_str()) == -1) { throw myengine::Exception("ShaderProgram::setVec3, vec3: Uniform location is -1"); }
	}

	void ShaderProgram::setVec3(const std::string& _name, float _x, float _y, float _z) const
	{
		glUniform3f(glGetUniformLocation(programID, _name.c_str()), _x, _y, _z);

		if (glGetUniformLocation(programID, _name.c_str()) == -1) { throw myengine::Exception("ShaderProgram::setVec3, float: Uniform location is -1"); }
	}

	void ShaderProgram::setFloat(const std::string& _name, float _value) const
	{
		glUniform1f(glGetUniformLocation(programID, _name.c_str()), _value);

		if (glGetUniformLocation(programID, _name.c_str()) == -1) { throw myengine::Exception("ShaderProgram::setFloat: Uniform location is -1"); }
	}

	void ShaderProgram::setInt(const std::string& _name, int _value) const
	{
		glUniform1i(glGetUniformLocation(programID, _name.c_str()), _value);

		if (glGetUniformLocation(programID, _name.c_str()) == -1) { throw myengine::Exception("ShaderProgram::setInt: Uniform location is -1"); }
	}

	void ShaderProgram::setMat4(const std::string& _name, const glm::mat4& _mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programID, _name.c_str()), 1, GL_FALSE, &_mat[0][0]);

		if (glGetUniformLocation(programID, _name.c_str()) == -1) { throw myengine::Exception("ShaderProgram::setMat4: Uniform location is -1"); }
	}
}