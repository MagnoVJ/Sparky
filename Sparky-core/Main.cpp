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
#include "src\graphics\texture.h"

#include <FreeImage.h>
#include <string>
#include <vector>
#include <time.h>

#define BATCH_RENDERER 1

#if 1
int main(){

	using namespace sparky::maths;
	using namespace sparky::graphics;
	using sparky::Timer;

	Window window("Sparky Engine", 960, 540);

	//glClearColor(0.0, 0.0, 0.0, 1.0f);

	Shader shader("src/shaders/vertexshader.vert", "src/shaders/fragmshader.frag");

	shader.enable();
	shader.setUniformMat4("pr_matrix", Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	shader.setUniform2f("light_pos", Vec2(4.0f, 1.5f));

	TileLayer layer1(&shader);

	Texture* textures[] = {new Texture("ta.png"), new Texture("tb.png"), new Texture("tc.png")};
	
	for(float y = -9.0; y < 9.0f; y++)
		for(float x = -16.0f; x < 16.0f; x++)
			if(rand() % 4 == 0)
				layer1.add(new Sprite(x, y, 0.9f, 0.9f, Vec4(rand() % 1000 / 1000.f, 0, 1, 1)));
			else
				layer1.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand ()%3]));

	GLint texIDs[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	shader.enable();
	shader.setUniform1iv("textures", texIDs, 10);

	srand(time(NULL));

	Timer timerFPS;

	unsigned int counter = 0, frames = 0;

	while(!window.closed()){

		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		if((x < 0 || x > window.getM_Width() || _isnan(x)) || (y < 0 || y > window.getM_Height() || _isnan(y))){x = 0; y = 0;}

		shader.setUniform2f("light_pos", Vec2((float)(x * 32.0f / window.getM_Width() - 16.0f), (float)(9.0f - y * 18.0f / window.getM_Height())));

		layer1.render();

		window.update();

		counter++;
		if(timerFPS.elapsed() * 1000.0f >= 1000){
			timerFPS.reset();
			frames = counter;
			counter = 0;
		}
		
		//printf("%d FPS\n", frames==0?counter:frames);

	}

	for(int i = 0; i < 3; i++)
		delete textures[i];

}

#else
int main(){

	const char* filename = "teste.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;
	
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if(!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if((bits == 0) || (width == 0) || (height == 0))
		return false;

	unsigned int pitch = FreeImage_GetPitch(dib);

	bits += pitch * (height - 1);

	for(int y = 0; y < height; y++){
		BYTE* pixel = bits;
		for(int x = 0; x < width; x++){
			printf("%d %d %d\n", +pixel[FI_RGBA_RED], +pixel[FI_RGBA_GREEN], +pixel[FI_RGBA_BLUE]);
			pixel += 3;
		}
		bits -= pitch;
	}

	FreeImage_Unload(dib);
	
	system("PAUSE");

}
#endif