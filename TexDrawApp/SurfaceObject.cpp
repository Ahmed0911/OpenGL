#include "SurfaceObject.h"

bool SurfaceObject::Load(const char * imagepath, GLuint shaderProgramID, int screenWidth, int screenHeight)
{
	// Native Screen resolution, used for scaling/translation
	ScreenHeight = screenHeight;
	ScreenWidth = screenWidth;

	// load texture
	textureID = LoadBMP(imagepath, Width, Height);

	/// create vertices
	Vertex Vertices[] = {
		{{-1.0f,  1.0f, 0.0f, 1.0f  }, { 1, 0, 0, 1 }, { 0, 1 } },
		{{ 1.0f,  1.0f, 0.0f, 1.0f  }, { 0, 1, 0, 1 }, { 1, 1 } },
		{{ -1.0f, -1.0f, 0.0f, 1.0f }, { 0, 0, 1, 1 }, { 0, 0 } },
		{{ 1.0f, -1.0f, 0.0f, 1.0f  }, { 1, 1, 1, 1 }, { 1, 0 } }
	};

	// Vertex buffer
	glGenBuffers(1, &VBO_Id);
	ExitOnGLError("ERROR: Could not generate the buffer objects");

	// Vertex Arrays
	glGenVertexArrays(1, &VA_Id);
	ExitOnGLError("ERROR: Could not generate the VAO");
	glBindVertexArray(VA_Id);
	ExitOnGLError("ERROR: Could not bind the VAO");
	
	// Fill Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

	// Set Vertex Array
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)sizeof(Vertices[0].Position));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)(sizeof(Vertices[0].Position) + sizeof(Vertices[0].Color)));
	ExitOnGLError("ERROR: Could not set VAO attributes");
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ExitOnGLError("ERROR: Could not enable vertex attributes");

	glBindVertexArray(0);

	shaderID = shaderProgramID; // copy shader ID

	// get uniform location
	TransMatrixUniformLocation = glGetUniformLocation(shaderID, "TransMatrix");

	return true;
}

void SurfaceObject::Draw(float x, float y, float rotationDeg)
{
	// set shaders
	glUseProgram(shaderID);
	ExitOnGLError("ERROR: Could not use the shader program");

	// set Uniforms
	Matrix transMatrix = IDENTITY_MATRIX;
	RotateAboutZ(&transMatrix, DegreesToRadians(rotationDeg));
	ScaleMatrix(&transMatrix, (float)Width / ScreenWidth, (float)Height / ScreenHeight, 1);
	TranslateMatrix(&transMatrix, (2*x / ScreenWidth) - 1, 1 - (2*y / ScreenHeight), 0);
	//TranslateMatrix(&transMatrix, ((2*x + Width) / ScreenWidth) - 1, 1 - ((2*y + Height ) / ScreenHeight), 0); // top-left corner as pivot for translation
	glUniformMatrix4fv(TransMatrixUniformLocation, 1, GL_FALSE, transMatrix.m);
	ExitOnGLError("ERROR: Could not set the shader uniforms");

	// set vertex array
	glBindVertexArray(VA_Id);
	ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

	// set texure
	glBindTexture(GL_TEXTURE_2D, textureID);

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	ExitOnGLError("ERROR: Could not draw the cube");

	// unbind
	glBindVertexArray(0);
	glUseProgram(0);
}

void SurfaceObject::Unload()
{
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO_Id);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VA_Id);
	glDeleteTextures(1, &textureID);
}