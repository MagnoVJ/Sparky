#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace sparky{

	namespace graphics{

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

		class Window{

		//Attributes
		private:
			const char* m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			double m_X, m_Y;

		//Methods
		private:
			bool init();
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		public:
			Window(const char* title, int width, int height);
			~Window();
			void update();
			bool closed() const;
			void clear() const;

			int getM_Width() const{ return m_Width;}
			int getM_Height() const{ return m_Height;}

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

			void setWidth(int width){ m_Width = width;}
			void setHeight(int height){m_Height = height;}

		};

	}

}