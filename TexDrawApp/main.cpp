
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_TITLE_PREFIX "Tex Draw App v1.0"
#include "Utils.h"
#include "SurfaceObject.h"

SurfaceObject obj;

int
CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;

unsigned FrameCount = 0;

// Shader stuff
GLuint ShaderIds[3] = { 0 };


void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void DestroyCube(void);

int main(int argc, char* argv[])
{
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}



void Initialize(int argc, char* argv[])
{
	InitWindow(argc, argv);

	GLenum GlewInitResult;
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		fprintf(
			stderr,
			"ERROR: %s\n",
			glewGetErrorString(GlewInitResult)
		);

		exit(EXIT_FAILURE);
	}

	fprintf(
		stdout,
		"INFO: OpenGL Version: %s\n",
		glGetString(GL_VERSION)
	);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	
	glewExperimental = GL_TRUE; // hack!
	glewInit();
	glGetError();

	// create shaders
	ShaderIds[0] = glCreateProgram();
	ExitOnGLError("ERROR: Could not create the shader program");

	ShaderIds[1] = LoadShader("SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	ShaderIds[2] = LoadShader("SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
	glAttachShader(ShaderIds[0], ShaderIds[1]);
	glAttachShader(ShaderIds[0], ShaderIds[2]);
	glLinkProgram(ShaderIds[0]);
	ExitOnGLError("ERROR: Could not link the shader program");

	obj.Load("sample_04.bmp", ShaderIds[0]);
}

void InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4,0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS
	);

	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (WindowHandle < 1) {
		fprintf(
			stderr,
			"ERROR: Could not create a new rendering window.\n"
		);
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(DestroyCube);
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}


void TimerFunction(int Value)
{
	if (0 != Value) {
		char* TempString = (char*)
			malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(
			TempString,
			"%s: %d Frames Per Second @ %d x %d",
			WINDOW_TITLE_PREFIX,
			FrameCount * 4,
			CurrentWidth,
			CurrentHeight
		);

		glutSetWindowTitle(TempString);
		free(TempString);
	}

	FrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}

void RenderFunction(void)
{
	FrameCount++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set shaders
	glUseProgram(ShaderIds[0]);
	ExitOnGLError("ERROR: Could not use the shader program");

	obj.Draw();

	glutSwapBuffers();
	glutPostRedisplay();
}



void DestroyCube(void)
{
	glDetachShader(ShaderIds[0], ShaderIds[1]);
	glDetachShader(ShaderIds[0], ShaderIds[2]);
	glDeleteShader(ShaderIds[1]);
	glDeleteShader(ShaderIds[2]);
	glDeleteProgram(ShaderIds[0]);
	ExitOnGLError("ERROR: Could not destroy the shaders");
}
