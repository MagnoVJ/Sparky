#pragma once

#include "renderable2d.h"

namespace sparky{

	namespace graphics{

		class StaticSprite : public Renderable2D{

		private:
			IndexBuffer* m_IndexBuffer;
			VertexArray* m_VertexArray;

			Shader& m_Shader;

		public:
			StaticSprite(float x, float y, float width, float height, const maths::Vec4& color, Shader& shader);
			~StaticSprite();

			inline Shader& getShader() const {return m_Shader;}

			inline const VertexArray* getVAO() const {return m_VertexArray;}
			inline const IndexBuffer* getIBO() const {return m_IndexBuffer;}

		};

	}

}