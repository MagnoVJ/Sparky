#include "simple2drenderer.h"

namespace sparky{

	namespace graphics{

		void Simple2DRenderer::submit(const Renderable2D* renderable){
			m_RenderableQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush(){

			while(!m_RenderableQueue.empty()){

				const StaticSprite* sprite = m_RenderableQueue.front();

				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", maths::Mat4::translation(sprite->getPosition()));

				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getVAO()->unbind();
				sprite->getIBO()->bind();

				m_RenderableQueue.pop_front();

			}

		}

	}

}