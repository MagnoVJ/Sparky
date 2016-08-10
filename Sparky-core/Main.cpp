#include "src\maths\maths.h"
#include "src\graphics\window.h"
#include "src\graphics\shader.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderable2d.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\static_sprite.h"

#include <string>

int main(){

	using namespace sparky::maths;
	using namespace sparky::graphics;

	Window window("Sparky Engine", 960, 540);

	glClearColor(0.0, 0.0, 0.0, 1.0f);

	//GLushort indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};
	//GLfloat vertices[] = {
	//	0, 0, 0,
	//	0, 3, 0,
	//	8, 3, 0,
	//	8, 0, 0
	//};
	//GLfloat colorsA[] = {
	//	1, 0, 1, 1,
	//	1, 0, 1, 1,
	//	1, 0, 1, 1,
	//	1, 0, 1, 1
	//};
	//GLfloat colorsB[] = {
	//	.2f, .3f, .8f, 1,
	//	.2f, .3f, .8f, 1,
	//	.2f, .3f, .8f, 1,
	//	.2f, .3f, .8f, 1
	//};
	//IndexBuffer ibo(indices, 2 * 3);
	//VertexArray sprite1, sprite2;
	//sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	//sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);
	//sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	//sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 4), 1);

	Shader shader("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");
	shader.enable();

	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0);

	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", Mat4::translation(Vec3(8.0, 3.0f, 0.0f)));
	shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));
	//shader.setUniform4f("colour", Vec4(0.2f, 0.3f, 0.8f, 1.0f));

	StaticSprite sprite(5.0f, 5.0f, 4.0f, 4.0f, Vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	StaticSprite sprite2(7.0f, 1.0f, 2.0f, 3.0f, Vec4(0.2f, 0.0f, 1.0f, 1.0f), shader);

	Simple2DRenderer renderer;

	while(!window.closed()){

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		shader.setUniform2f("light_pos", Vec2((float)(x * (16.0f / window.getM_Width())), (float)(9.0f - y * (9.0f / window.getM_Height()))));

		renderer.submit(&sprite);
		renderer.submit(&sprite2);

		renderer.flush();

		window.update();
	}

}