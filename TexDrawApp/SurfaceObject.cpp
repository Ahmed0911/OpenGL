#include "SurfaceObject.h"

bool SurfaceObject::Load(const char * imagepath, GLuint shaderProgramID)
{
	// load texture
	textureID = LoadBMP(imagepath, Width, Height);

	/// create vertices
	Vertex Vertices[] = {
		{{-1.0f,  1.0f, 0.0f, 1.0f  }, { 0, 0, 0, 1 }, { 0, 0 } },
		{{ 1.0f,  1.0f, 0.0f, 1.0f  }, { 0, 0, 0, 1 }, { 1, 0 } },
		{{ -1.0f, -1.0f, 0.0f, 1.0f }, { 0, 0, 0, 1 }, { 1, 1 } },
		{{ 1.0f, -1.0f, 0.0f, 1.0f  }, { 0, 0, 0, 1 }, { 0, 1 } }
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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]), (GLvoid*)sizeof(Vertices[0].Color));
	ExitOnGLError("ERROR: Could not set VAO attributes");
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	ExitOnGLError("ERROR: Could not enable vertex attributes");

	glBindVertexArray(0);

	shaderID = shaderProgramID; // copy shader ID

	return true;
}

void SurfaceObject::Draw()
{
	// set shaders
	glUseProgram(shaderID);
	ExitOnGLError("ERROR: Could not use the shader program");

	//glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, ModelMatrix.m);	
	ExitOnGLError("ERROR: Could not set the shader uniforms");

	// set vertex array
	glBindVertexArray(VA_Id);
	ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");

	// set texure
	glBindTexture(GL_TEXTURE_2D, textureID);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, 6);
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