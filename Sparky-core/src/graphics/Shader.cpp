#include "shader.h"

namespace sparky{

	namespace graphics{

		Shader::Shader(const char* vertexPath, const char* fragmentPath) : m_VertexPath(vertexPath), m_FragmentPath(fragmentPath){

			m_ShaderID = load();

		}

		GLuint Shader::load(){

			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			const char* vertexSource = read_file(m_VertexPath).c_str();
			const char* fragmentSource = read_file(m_FragmentPath).c_str();

			glShaderSource(vertex, 1, &vertexSource, NULL);

			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if(result == GL_FALSE){

				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				
				return 0;
			}

			glShaderSource(fragment, 1, &fragmentSource, NULL);

			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if(result == GL_FALSE){

				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;

		}

		void Shader::enable() const{

			glUseProgram(m_ShaderID);

		}

		void Shader::disable() const{

			glUseProgram(0);

		}

	}

}