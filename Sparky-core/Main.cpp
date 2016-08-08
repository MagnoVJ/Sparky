#include "src\maths\maths.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include <string>

int main(){

	using namespace sparky::maths;
	using sparky::graphics::Window;
	using sparky::graphics::Shader;

	Window window("Sparky Engine", 960, 540);

	glClearColor(0.0, 0.0, 0.0, 1.0f);

	GLfloat vertices[] = {

		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0

	};

	GLuint vbo;
	glGenBuffers(1, &vbo); //Generate buffer object names
	glBindBuffer(GL_ARRAY_BUFFER, vbo); //Bind a named buffer object | GL_ARRAY_BUFFER = Vertex attributes
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Creates and initializes a buffer object's data store
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);//Define an array of generic vertex attribute data
	glEnableVertexAttribArray(0); //Enable or disable a generic vertex attribute array

	Shader shader("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");
	shader.enable();

	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0);

	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Mat4::translation(Vec3(4.0, 3.0f, 0.0f)));
	shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", Vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while(!window.closed()){

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		shader.setUniform2f("light_pos", Vec2((float)(x * (16.0f / window.getM_Width())), (float)(9.0f - y * (9.0f / window.getM_Height()))));
		
		/* render primitives from array data void glDrawArrays(GLenum mode, GLint first, GLsizei count);
		mode = Specifies what kind of primitives to render. Symbolic constants
		first = Specifies the starting index in the enabled arrays
		count = Specifies the number of indices to be rendered*/
		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

}