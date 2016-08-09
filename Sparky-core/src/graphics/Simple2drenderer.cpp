#include "simple2drenderer.h"

namespace sparky{

	namespace graphics{

		void Simple2DRenderer::submit(const Renderable2D* renderable){
			m_RenderableQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush(){

			while(!m_RenderableQueue.empty()){

				const Renderable2D* renderable = m_RenderableQueue.front();

				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", maths::Mat4::translation(renderable->getPosition()));

				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getVAO()->unbind();
				renderable->getIBO()->bind();

				m_RenderableQueue.pop_front();

			}

		}

	}

}