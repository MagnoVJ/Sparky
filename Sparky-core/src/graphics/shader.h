#pragma once

#include "../utils/fileutils.h"
#include "../maths/maths.h"
#include <GL/glew.h>
#include <iostream>
#include <vector>

namespace sparky{

	namespace graphics{

		class Shader{

		//Attributes
		private:
			GLuint m_ShaderID;
			const char* m_VertexPath;
			const char* m_FragmentPath;

		//Methods
		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);

		//Methods
		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			void setUniform1f(const GLchar* name, const float& value);
			void setUniform1fv(const GLchar* name, float* value, int count);
			void setUniform1i(const GLchar* name, const int& value);
			void setUniform1iv(const GLchar* name, int* value, int count);
			void setUniform2f(const GLchar* name, const maths::Vec2& vector);
			void setUniform3f(const GLchar* name, const maths::Vec3& vector);
			void setUniform4f(const GLchar* name, const maths::Vec4& vector);

			void setUniformMat4(const GLchar* name, const maths::Mat4& matrix);

			void enable() const;
			void disable() const;

		};

	}

}