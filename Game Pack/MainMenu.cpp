#include "Button.h"
#include <vector>
#include "Artist.h"
#include "MainMenu.h"
#include "ParticleFling.h"
#include "TileTest.h"


//MAKE EACH GAME A NEW HEADER THAT HAS A CLASS/STRUCT THAT HOLDS THE VARIABLES AND FUNCTIONS SO WE CAN CONSRUCT AND DE CONSTRUCT EACH GAME INDIVIDUALY

enum menuStates {
	MAIN_MENU,
	OPTIONS,
	IN_GAME
};

enum gameList {
	PARTICLE_FLING,
	TILE_TEST
};

std::vector<Button::button> buttonList;

int menuState = MAIN_MENU;

void startParticleFling(int gameID)
{
	menuState = IN_GAME;
	particleFling runningGame;
	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].activated = false;
	}
	menuState = MAIN_MENU;

}

void startTileTest(int gameID)
{
	menuState = IN_GAME;
	tileTest runningGame;

	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList[i].activated = false;
	}
	menuState = MAIN_MENU;
}

void dummyFunc(int arb)
{

}

void MainMenu::init()
{
	Artist artist;
	//load test button
	std::vector<SDL_Texture*> inIdleTex = artist.loadAnimationData("tests", "testButton", 0, 11);
	std::vector<SDL_Texture*> inHoverTex = artist.loadAnimationData("tests", "testButton", 1, 11);
	std::vector<SDL_Texture*> inActiveTex = artist.loadAnimationData("tests", "testButton", 2, 11);
	Button::button testButton;
	testButton.init({ Artist::SCREEN_WIDTH / 2 - 64, Artist::SCREEN_HEIGHT / 2 - 32 }, { 128, 64 }, inIdleTex, inHoverTex, inActiveTex, 100,  dummyFunc, dummyFunc);
	//buttonList.push_back(testButton);

	//load partical fling button
	inIdleTex = artist.loadAnimationData("particleFling", "mainMenuButton", 0, 1);
	inHoverTex = artist.loadAnimationData("particleFling", "mainMenuButton", 1, 6);
	inActiveTex = artist.loadAnimationData("particleFling", "mainMenuButton", 2, 9);
	Button::button particalFlingButton;
	particalFlingButton.init({ Artist::SCREEN_WIDTH / 2 - 240, 128 }, { 480, 74 }, inIdleTex, inHoverTex, inActiveTex, 100, startParticleFling, dummyFunc);
	buttonList.push_back(particalFlingButton);

	//load tile test button
	inIdleTex = artist.loadAnimationData("tiletest", "mainMenuButton", 0, 1);
	inHoverTex = artist.loadAnimationData("tiletest", "mainMenuButton", 1, 6);
	inActiveTex = artist.loadAnimationData("tiletest", "mainMenuButton", 2, 9);
	Button::button tileTestButton;
	tileTestButton.init({ Artist::SCREEN_WIDTH / 2 - 240, 256 }, { 480, 74 }, inIdleTex, inHoverTex, inActiveTex, 100, startTileTest, dummyFunc);
	buttonList.push_back(tileTestButton);
}

void MainMenu::controller()
{
	if (menuState != IN_GAME)
	{
		if (Controller::keyboardStates[SDL_SCANCODE_ESCAPE] == 1)
		{
			Controller::quit = true;
		}
		for (int i = 0; i < buttonList.size(); i++)
		{
			buttonList[i].update();
		}
	}
}

//in charge of drawing all menus and games based on game state
void MainMenu::draw()
{
	Artist artist;

	switch (menuState)
	{
	case MAIN_MENU:

		for (int i = 0; i < buttonList.size(); i++)
		{
			buttonList[i].draw();
		}
		artist.drawLetters("Game?", Artist::SCREEN_WIDTH / 2 - 64 * 2.5, 8, Artist::largeFont);

		break;
	case OPTIONS:

		break;
	}
	
}