#include "Application.h"
#include <stdlib.h>
#include <stdio.h>


// Monika Ellingerová
// ELL0014

int main(void)
{
	
	Application* app = new Application();
	app->initialize();
	app->run();
}
