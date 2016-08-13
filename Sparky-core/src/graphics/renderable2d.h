#pragma once

#include "../maths/maths.h"
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "shader.h"
#include "renderer2d.h"

namespace sparky{

	namespace graphics{

		struct VertexData{
			maths::Vec3 vertex;
			//maths::Vec4 color;
			unsigned int color;
		};

		class Renderable2D{

		//Attributes
		protected:
			maths::Vec3 m_Position;
			maths::Vec2 m_Size;
			maths::Vec4 m_Color;

		//Methods
		public:
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) :
				m_Position(position), m_Size(size), m_Color(color){ }

			Renderable2D(){}

			virtual ~Renderable2D(){ }

			inline const maths::Vec3& getPosition() const {return m_Position;}
			inline const maths::Vec2& getSize() const {return m_Size;}
			inline const maths::Vec4& getColor() const {return m_Color;}

			virtual void submit(Renderer2D* renderer) const{
				renderer->submit(this);
			}

		};

	}

}