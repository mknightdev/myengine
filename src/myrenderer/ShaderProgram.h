#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

namespace myrenderer
{
	/// ShaderProgram struct to bind into a shader program.
	/// 
	/// This struct creates a shader program, returns its id and source. It takes in a vertex shader
	/// and fragment shader. 
	const GLsizei LOG_LENGTH = 512;

	struct ShaderProgram
	{
	public:
		/// Returns the program id. 
		/// 
		/// @returns GLuint 
		GLuint getId();

		/// Returns the shader source.
		/// 
		/// Takes in shader source and the shader type to return its id. 
		/// @returns GLuint
		GLuint GetSource(const GLchar* source, GLuint type);

		/// Creates the shader program. 
		/// 
		/// Takes in both vertex shader and fragment shader to combine into a shader program. 
		/// @param vertSrc The vertex shader. 
		/// @param fragSrc The fragment shader. 
		/// @returns void
		void CreateShader(const GLchar* vertSrc, const GLchar* fragSrc);


		// Activate the shader
		void use()
		{
			glUseProgram(programID);
		}

		void setVec3(const std::string& _name, const glm::vec3& _value) const
		{
			glUniform3fv(glGetUniformLocation(programID, _name.c_str()), 1, &_value[0]);
		}

		void setVec3(const std::string& _name, float _x, float _y, float _z) const
		{
			glUniform3f(glGetUniformLocation(programID, _name.c_str()), _x, _y, _z);
		}

		void setFloat(const std::string& _name, float _value) const
		{
			glUniform1f(glGetUniformLocation(programID, _name.c_str()), _value);
		}

	private:
		GLuint programID;
	};
}