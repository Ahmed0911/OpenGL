#pragma once
#include "SurfaceObject.h"
#include <vector>

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
	std::vector<SurfaceObject> Objects;

	GLuint ShaderID1;
	int CurrentWidth = 1920;
	int CurrentHeight = 1200;
	int WindowHandle = 0;
	unsigned FrameCount = 0;
};

