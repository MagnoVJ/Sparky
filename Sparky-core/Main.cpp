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
	shader.enable();

	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0);

	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));
	//shader.setUniform4f("colour", Vec4(0.2f, 0.3f, 0.8f, 1.0f));

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

#if BATCH_RENDERER
	Sprite sprite(5.0f, 5.0f, 4.0f, 4.0f, Vec4(1.0f, 0.0f, 1.0f, 1.0f));
	Sprite sprite2(7.0f, 1.0f, 4.0f, 4.0f, Vec4(0.2f, 0.0f, 1.0f, 1.0f));
	BatchRenderer2D renderer;
#else
	StaticSprite sprite(5.0f, 5.0f, 4.0f, 4.0f, Vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	StaticSprite sprite2(7.0f, 1.0f, 4.0f, 4.0f, Vec4(0.2f, 0.0f, 1.0f, 1.0f), shader);
	Simple2DRenderer renderer;
#endif

	for(float y = 0; y < 9.0f; y+=.1f){
		for(float x = 0; x < 16.0f; x+=.1f){
			if(BATCH_RENDERER)
				sprites.push_back(new Sprite(x, y, 0.08f, 0.08f, Vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				sprites.push_back(new StaticSprite(x, y, 0.08f, 0.08f, Vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
		}    
	}

	Timer timerFPS;
	unsigned int counter = 0, frames = 0;

	Mat4 mat = Mat4::translation(Vec3(8, 4.5, 0));

	std::cout << mat << std::endl;

    /*mat = mat * Mat4::rotation(310.0f, Vec3(0, 0, 1));
	mat *= Mat4::translation(Vec3(-8, 4.5, 0));
	shader.setUniformMat4("ml_matrix", mat);*/

	while(!window.closed()){

		/*Mat4 mat = Mat4::translation(Vec3(8, 4.5, 0));
	    mat = mat * Mat4::rotation(timerFPS.elapsed() * 1.0f, Vec3(0, 0, 1));
		mat = mat * Mat4::translation(Vec3(-8, -4.5, 0));*/
		shader.setUniformMat4("ml_matrix", mat);

		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		if((x < 0 || x > window.getM_Width() || _isnan(x)) || (y < 0 || y > window.getM_Height() || _isnan(y))){
			x = 0;
			y = 0;
		}

		shader.setUniform2f("light_pos", Vec2((float)(x * (16.0f / window.getM_Width())), (float)(9.0f - y * (9.0f / window.getM_Height()))));

#if BATCH_RENDERER
		renderer.begin();
#endif
		for(int i = 0; i < sprites.size(); i++)
			renderer.submit(sprites[i]);

#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();

		counter++;
		if(timerFPS.elapsed() * 1000.0f >= 1000){
			//timerFPS.reset();
			frames = counter;
			counter = 0;
		}
		
		//printf("%d FPS\n", frames==0?counter:frames);

	}

}