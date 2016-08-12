#pragma once

#include <GL/glew.h>

namespace sparky{

	namespace graphics{

		class IndexBuffer{

		private:
			GLuint m_IndexBufferID;
			GLsizei m_Count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLsizei getCount() const{ return m_Count;}

		};

	}

}