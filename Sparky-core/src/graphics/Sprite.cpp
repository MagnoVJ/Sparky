#include "sprite.h"

namespace sparky{

	namespace graphics{

		Sprite::Sprite(float x, float y, float width, float height, const maths::Vec4& color)
			: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, height), color){ 
				m_Texture = nullptr;
			
		} 

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, height), maths::Vec4(1, 0, 1, 1)){
				m_Texture = texture;
		}

	}

}