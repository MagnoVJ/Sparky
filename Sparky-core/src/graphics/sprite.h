#pragma once

#include "renderable2d.h"

namespace sparky{

	namespace graphics{

		class Sprite : public Renderable2D{

		public:
			Sprite(float x, float y, float width, float height, const maths::Vec4& color);
			Sprite(float x, float y, float width, float height, Texture* texture);
		};

	}

}