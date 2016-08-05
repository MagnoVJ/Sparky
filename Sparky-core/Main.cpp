#include "src\maths\maths.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"

#include <string>

int main(){

	using sparky::graphics::Window;
	//using sparky::graphics::Shader;
	using namespace sparky::maths;

	Window window("Sparky Engine", 960, 540);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	while(!window.closed()){

		window.clear();

		//HERE

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

		window.update();
	}

}