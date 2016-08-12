#pragma once

#include "../renderer2d.h"
#include "../renderable2d.h"

namespace sparky{

	namespace graphics{

		class Layer{

		//Attributes
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader* m_Shader;
			maths::Mat4 m_ProjectionMatrix;

		//Methods
		protected:
			Layer(Renderer2D* renderer, Shader* shader, maths::Mat4 projectionMatrix);

		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

		};

	}

}