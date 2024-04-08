#include <stdio.h>
#include "Artist.h"
#include "Controller.h"
#include "MainMenu.h".


int main(int argc, char* args[])
{
	//Declare Artist and controller
	Artist Artist;
	Controller controller;
	MainMenu mainMenu;
	

	//Start up SDL and create window
	if (!Artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!Artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}


		//loading setting ect
		controller.loadController();
		mainMenu.init();


		//While application is running
		while (!Controller::quit)
		{
			//Clear screen
			Artist.clearScreen();


			//Checks for user input
			controller.controller();

			

			//Draw everything
			Artist.draw();






			//Update screen
			Artist.updateScreen();
		}

	}

	//Free resources and close SDL
	Artist.close();

	return 0;
}