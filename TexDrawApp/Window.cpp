#include "Window.h"

#define WINDOW_TITLE_PREFIX "Tex Draw App v1.0"

bool Window::Init(int argc, char* argv[])
{
	// Init
	glutInit(&argc, argv);

	glutInitContextVersion(4, 4);
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

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);

	// create shaders
	CreateShaders();

	// load objects
	SurfaceObject obj1, obj2, obj3;
	obj1.Load("sample_04.bmp", ShaderID1);
	obj2.Load("colors.bmpx", ShaderID1);
	obj3.Load("Speed-Meter.bmpx", ShaderID1);
	Objects.push_back(obj1);
	Objects.push_back(obj2);
	Objects.push_back(obj3);

	return false;
}

void Window::CreateShaders()
{
	// create shaders
	ShaderID1 = glCreateProgram();
	ExitOnGLError("ERROR: Could not create the shader program");

	GLuint fragmentID = LoadShader("SimpleShader.fragment.glsl", GL_FRAGMENT_SHADER);
	GLuint vertexID = LoadShader("SimpleShader.vertex.glsl", GL_VERTEX_SHADER);
	glAttachShader(ShaderID1, fragmentID);
	glAttachShader(ShaderID1, vertexID);
	glLinkProgram(ShaderID1);
	ExitOnGLError("ERROR: Could not link the shader program");

	// delete shaders (only linked shader program is needed)
	glDeleteShader(fragmentID);
	glDeleteShader(vertexID);
}

float timer = 0;
void Window::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set shaders
	glUseProgram(ShaderID1);
	ExitOnGLError("ERROR: Could not use the shader program");

	// draw objects
	Objects[0].Draw(1920/2, 1200/2, 0);
	for (int i = 0; i != 10; i++)
	{
		for(int j=0; j!=10; j++)
		Objects[1].Draw(i*300.0f, j*300.0f, timer);
	}
	timer += 0.02f;

	glutSwapBuffers();
	glutPostRedisplay();
	FrameCount++;
}


void Window::Destroy()
{
	// kill objects
	for (int i = 0; i != Objects.size(); i++)
	{
		Objects[i].Unload();
	}

	// kill shader programs
	glDeleteProgram(ShaderID1);
}


void Window::ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void Window::TimerFunction(int Value)
{
	if (0 != Value) {
		char* TempString = (char*)
			malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(
			TempString,
			"%s: %d fps  [%0.3f ms] @ %d x %d",
			WINDOW_TITLE_PREFIX,
			FrameCount * 4,
			1000.0/(FrameCount * 4),
			CurrentWidth,
			CurrentHeight
		);

		glutSetWindowTitle(TempString);
		free(TempString);
	}

	FrameCount = 0;

}