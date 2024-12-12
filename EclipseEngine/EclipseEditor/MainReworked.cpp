#include "App.h"
#include "EclipseEngine/Logger.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <stdlib.h>

enum MainState
{
	CREATE = 1,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* app = NULL;

int main(int argc, char* args[])
{

	MainState state = CREATE;
	int result = EXIT_FAILURE;

	while (state != EXIT)
	{
		//OPTICK_FRAME("MainLoop");
		switch (state)
		{
			// Allocate the engine ---------------------------------------------
		case CREATE:

			app = new App(argc, args);

			if (app != NULL)
				state = START;
			else
				state = FAIL;

			break;

			// Call all modules before first frame  ----------------------------
		case START:
			if (app->Start() == true)
			{
				state = LOOP;
			}
			else
			{
				state = FAIL;
			}
			break;

			// Loop all modules until we are asked to leave --------------------
		case LOOP:
		{
			//OPTICK_FRAME("Main Loop");
			if (app->Update() == false)
				state = CLEAN;
		}
		break;

		// Cleanup allocated memory --------------------------------------------
		case CLEAN:
			if (app->CleanUp() == true)
			{
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame --------------------------------------
		case FAIL:
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
	}

	// Dump memory leaks
	return result;
}