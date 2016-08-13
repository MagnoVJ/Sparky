#pragma once

#include <vector>
#include <GL/glew.h>
#include "../maths/maths.h"

namespace sparky{

	namespace graphics{

		class Renderable2D;

		class Renderer2D{

		//Attributes
		protected:
			std::vector<const maths::Mat4> m_TransformationStack;
			const maths::Mat4* m_TransformationBack;

		//Methods	
		protected:
			Renderer2D(){
				m_TransformationStack.push_back(maths::Mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}

		public:
			void push(const maths::Mat4& matrix, bool overrideFlag = false){

				if(overrideFlag)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationBack = &m_TransformationStack.back();

			}

			void pop(){

				if(m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationBack = &m_TransformationStack.back();

			}

		public:
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
			virtual void begin(){}
			virtual void end(){}

		};

	}

}