#pragma once
#include "Utils.h"

class SurfaceObject
{
public:
	bool Load(const char * imagepath, GLuint shaderProgramID);
	void Draw();
	void Unload();

private:
	unsigned int Width;
	unsigned int Height;
	GLuint textureID;
	GLuint shaderID;

	GLuint VA_Id;
	GLuint VBO_Id;
};

