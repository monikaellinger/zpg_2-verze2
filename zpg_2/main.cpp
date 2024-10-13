#include "Application.h"

#include <stdlib.h>
#include <stdio.h>


int main(void)
{
	Application* app = new Application();
	app->initialize();
	app->compileShaders();
	app->run();
}
