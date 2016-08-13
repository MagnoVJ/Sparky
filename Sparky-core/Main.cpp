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
#include "src\graphics\layers\group.h"

#include <string>
#include <vector>
#include <time.h>

#define BATCH_RENDERER 1
#define ADD_MANY_SPRITES 0

int main(){

	using namespace sparky::maths;
	using namespace sparky::graphics;
	using sparky::Timer;

	Window window("Sparky Engine", 960, 540);

	//glClearColor(0.0, 0.0, 0.0, 1.0f);

	Shader shader("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");
	Shader shader2("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");

	shader.enable();
	shader2.enable();

	shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));
	shader2.setUniform2f("light_pos", Vec2(4.0f, 1.5f));

	TileLayer layer1(&shader);

#if ADD_MANY_SPRITES
	for(float y = -9.0; y < 9.0f; y+=.2f)
		for(float x = -16.0f; x < 16.0f; x+=.2f)
			layer1.add(new Sprite(x, y, 0.18f, 0.18f, Vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
	/*for(float y = -9.0; y < 9.0f; y++)
		for(float x = -16.0f; x < 16.0f; x++)
			layer1.add(new Sprite(x, y, 0.9f, 0.9f, Vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));*/

	Mat4 transformation =  Mat4::translation(Vec3(-3.0f, -1.5f, 0.0f)) * Mat4::rotation(0.0f, Vec3(0.0f, 0.0f, 1.0f));

	Group* group = new Group(transformation);
	group->add(new Sprite(0, 0, 6, 3, Vec4(1, 1, 1, 1)));

	Group* button = new Group(Mat4::translation(Vec3(0.5f, 0.5f, 0.0f)));
	button->add(new Sprite(0.0, 0.0, 5.0f, 2.0f, Vec4(1, 0, 1, 1)));
	button->add(new Sprite(0.5f, 0.5f, 4.0f, 1.0f, Vec4(0.2f, 0.3f, 0.8f, 1)));
	group->add(button);
	
	layer1.add(group);

#endif

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
		shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getM_Width() - 16.0f), (float)(9.0f - y * 18.0f / window.getM_Height())));

		//shader2.enable();
		//shader2.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getM_Width() - 16.0f), (float)(9.0f - y * 18.0f / window.getM_Height())));

		layer1.render();
		//layer2.render();

		window.update();

		counter++;
		if(timerFPS.elapsed() * 1000.0f >= 1000){
			timerFPS.reset();
			frames = counter;
			counter = 0;
		}
		
		//printf("%d FPS\n", frames==0?counter:frames);

	}

}