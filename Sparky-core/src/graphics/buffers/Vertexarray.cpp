#include "vertexarray.h"

namespace sparky{

	namespace graphics{

		VertexArray::VertexArray(){

			glGenVertexArrays(1, &m_VertexArrayID);

		}

		VertexArray::~VertexArray(){

			for(int i = 0; i < m_Buffers.size(); i++)
				delete m_Buffers[i];

			glDeleteVertexArrays(1, &m_VertexArrayID);

		}

		void VertexArray::addBuffer(Buffer* buffer, GLuint index){

			bind();
			buffer->bind();

			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(index);

			buffer->unbind();
			unbind();

		}

		void VertexArray::bind() const{
			glBindVertexArray(m_VertexArrayID);
		}

		void VertexArray::unbind() const{
			glBindVertexArray(0);
		}

	}

}