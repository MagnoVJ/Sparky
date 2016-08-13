#include "group.h"

namespace sparky{

	namespace graphics{

		Group::Group(const maths::Mat4& transformationMatrix)
			: m_TransformationMatrix(transformationMatrix){


		}

		void Group::add(Renderable2D* renderable){
			m_Renderables.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const {

			renderer->push(m_TransformationMatrix);

			for(const Renderable2D* renderable : m_Renderables)
				renderable->submit(renderer);

			renderer->pop();

		}



	}


}