#pragma once

#include "buffer.h"
#include <GL/glew.h>
#include <vector>

namespace sparky{

	namespace graphics{

		class VertexArray{

		private:
			GLuint m_VertexArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);

			void bind() const;
			void unbind() const;

		};

	}

}