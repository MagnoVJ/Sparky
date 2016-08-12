#include "src\utils\timer.h"

#include "src\maths\maths.h"

#include "src\graphics\window.h"
#include "src\graphics\shader.h"

#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderable2d.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\batchrenderer2d.h"
#include "src\graphics\static_sprite.h"
#include "src\graphics\sprite.h"
#include "src\graphics\layers\tilelayer.h"

#include <string>
#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

int main(){

	using namespace sparky::maths;
	using namespace sparky::graphics;
	using sparky::Timer;

	Window window("Sparky Engine", 960, 540);

	//glClearColor(0.0, 0.0, 0.0, 1.0f);

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
	Shader shader2("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");

	shader.enable();
	shader2.enable();

	shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));
	shader2.setUniform2f("light_pos", Vec2(4.0f, 1.5f));

	TileLayer layer1(&shader);

	for(float y = -9.0; y < 9.0f; y+=.2f)
		for(float x = -16.0f; x < 16.0f; x+=.2f)
			layer1.add(new Sprite(x, y, 0.18f, 0.18f, Vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));

	TileLayer layer2(&shader2);

	layer2.add(new Sprite(-2, -2, 4, 4, Vec4(1, 0, 1, 1)));

	srand(time(NULL));

	Timer timerFPS;
	unsigned int counter = 0, frames = 0;

	while(!window.closed()){

		/*Mat4 mat = Mat4::translation(Vec3(8, 4.5, 0));
		mat *= Mat4::rotation(timerFPS.elapsed() * 50.0f, Vec3(0, 0, 1));
		mat *= Mat4::translation(Vec3(-8, -4.5, 0));
		shader.setUniformMat4("ml_matrix", mat);*/

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		if((x < 0 || x > window.getM_Width() || _isnan(x)) || (y < 0 || y > window.getM_Height() || _isnan(y))){
			x = 0;
			y = 0;
		}

		shader.enable();
		//shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getM_Width() - 16.0f), (float)(9.0f - y * 18.0f / window.getM_Height())));
		shader.setUniform2f("light_pos", Vec2(-8, -3));

		shader2.enable();
		shader2.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getM_Width() - 16.0f), (float)(9.0f - y * 18.0f / window.getM_Height())));

		layer1.render();
		layer2.render();

		window.update();

		counter++;
		if(timerFPS.elapsed() * 1000.0f >= 1000){
			timerFPS.reset();
			frames = counter;
			counter = 0;
		}
		
		printf("%d FPS\n", frames==0?counter:frames);

	}

}