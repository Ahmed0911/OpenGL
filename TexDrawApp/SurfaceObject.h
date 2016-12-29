#pragma once
#include "Utils.h"

class SurfaceObject
{
public:
	bool Load(const char * imagepath, GLuint shaderProgramID, int screenWidth = 1920, int screenHeight = 1200);
	void Draw(float x = 0, float y = 0, float rotationDeg = 0);
	void Unload();

private:
	unsigned int Width;
	unsigned int Height;
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;

	GLuint textureID;
	GLuint shaderID;
	GLuint TransMatrixUniformLocation;

	GLuint VA_Id;
	GLuint VBO_Id;
};

