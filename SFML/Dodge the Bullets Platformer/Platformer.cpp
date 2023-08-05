#include <iostream>
#include "Window.h"
#include <time.h>

int main()
{
	srand(time(NULL));

    Window window;

	while (window.isOpen())
	{
		window.handleEvents();
		window.handleInputs();
		window.update();
		window.render();
		window.handleCollisionsWithWindow();
		window.handleCollisionsWithPlatforms();
		window.handleCollisionsWithBullets();
	}

	return 0;
}

