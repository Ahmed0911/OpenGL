#pragma once
#include "SurfaceObject.h"

class Window
{
public:
	bool Init(int argc, char* argv[]);
	void Draw();
	void Destroy();

	void ResizeFunction(int Width, int Height);
	void TimerFunction(int Value);

private:
	void CreateShaders();

private:
	SurfaceObject object1;
	GLuint ShaderID1;
	int CurrentWidth = 800;
	int CurrentHeight = 600;
	int WindowHandle = 0;
	unsigned FrameCount = 0;
};

