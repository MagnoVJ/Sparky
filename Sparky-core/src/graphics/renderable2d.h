#pragma once

#include "../maths/maths.h"
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "shader.h"

namespace sparky{

	namespace graphics{

		class Renderable2D{

		//Attributes
		protected:
			maths::Vec3 m_Position;
			maths::Vec2 m_Size;
			maths::Vec4 m_Color;

			IndexBuffer* m_IndexBuffer;
			VertexArray* m_VertexArray;

			Shader& m_Shader;

		//Methods
		public:
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color, Shader& shader) :
				m_Position(position), m_Size(size), m_Color(color), m_Shader(shader){

					GLushort indices[] = {0, 1, 2, 2, 3, 0};

					m_IndexBuffer = new IndexBuffer(indices, 6);
					
					m_VertexArray = new VertexArray();

					GLfloat vertices[] = {
						0, 0, 0,
						0, size.y, 0,
						size.x, size.y, 0,
						size.x, 0, 0
					};

					GLfloat colors[] = {
						color.x, color.y, color.z, color.w,
						color.x, color.y, color.z, color.w,
						color.x, color.y, color.z, color.w,
						color.x, color.y, color.z, color.w
					};

					m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
					m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			}

			virtual ~Renderable2D(){
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const maths::Vec3& getPosition() const {return m_Position;}
			inline const maths::Vec2& getSize() const {return m_Size;}
			inline const maths::Vec4& getColor() const {return m_Color;}

			inline Shader& getShader() const {return m_Shader;}

			inline const VertexArray* getVAO() const {return m_VertexArray;}
			inline const IndexBuffer* getIBO() const {return m_IndexBuffer;}

		};

	}

}