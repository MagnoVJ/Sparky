#pragma once

#include "../utils/fileutils.h"
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

		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			~Shader();

			void enable() const;
			void disable() const;

		};

	}

}