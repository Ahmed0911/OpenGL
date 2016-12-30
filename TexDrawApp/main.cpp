
#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_TITLE_PREFIX "Tex Draw App v1.0"
#include "Window.h"

Window renderWindow;

// Callbacks
void IdleFunction(void)
{
	glutPostRedisplay();
}

void TimerFunction(int Value)
{
	renderWindow.TimerFunction(Value);
	glutTimerFunc(1000, TimerFunction, 1);
}

void Render(void)
{
	renderWindow.Draw();
}

void Destroy(void)
{
	renderWindow.Destroy();
}

void ResizeFunction(int Width, int Height)
{
	renderWindow.ResizeFunction(Width, Height);
}



////////////////////////////////////////////
// MAIN
////////////////////////////////////////////
int main(int argc, char* argv[])
{
	renderWindow.Init(argc, argv);

	// setup callbacks
	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(Render);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
	glutCloseFunc(Destroy);


	glutMainLoop();

	exit(EXIT_SUCCESS);
}
