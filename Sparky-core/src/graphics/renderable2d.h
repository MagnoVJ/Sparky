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
			maths::Vec2 uv;
			unsigned int color;
		};

		class Renderable2D{

		private:
			void setUVDefaults(){
				m_UV.push_back(maths::Vec2(0, 0));
				m_UV.push_back(maths::Vec2(0, 1));
				m_UV.push_back(maths::Vec2(1, 1));
				m_UV.push_back(maths::Vec2(1, 0));
			}

		//Attributes
		protected:
			maths::Vec3 m_Position;
			maths::Vec2 m_Size;
			maths::Vec4 m_Color;
			std::vector<maths::Vec2> m_UV;
		//Methods
		public:
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) :
				m_Position(position), m_Size(size), m_Color(color){ 
					setUVDefaults();
			}

			Renderable2D(){
				setUVDefaults();
			}

			virtual ~Renderable2D(){ }

			inline const maths::Vec3& getPosition() const {return m_Position;}
			inline const maths::Vec2& getSize() const {return m_Size;}
			inline const maths::Vec4& getColor() const {return m_Color;}
			inline const std::vector<maths::Vec2>& getUV() const {return m_UV;}

			virtual void submit(Renderer2D* renderer) const{
				renderer->submit(this);
			}

		};

	}

}