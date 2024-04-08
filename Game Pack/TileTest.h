#pragma once
#ifndef Artist
#include "Artist.h"
#endif
#ifndef Controller
#include "Controller.h"
#endif
#ifndef FPSCounter
#include "FPSCounter.h"
#endif // !FPSCounter
#ifndef SDL_image
#include <SDL_image.h>
#endif // !SDL_image



class tileTest
{
	// declare classses
	Artist artist;
	Controller controller;
	FPSCounter fpsCounter;


	//game data
	bool running = true;
	SDL_Texture* tileA = NULL;
	SDL_Texture* tileB = NULL;
	std::vector<std::vector<bool>> grid;
	SDL_Texture* gridTex = NULL;

	


	//sub funcs
	void drawFinalGrid()
	{
		//artist.drawImage(tileA, 0, 0);
		artist.drawImage(gridTex, 0, 0);
	}

	void drawTiles()
	{
		for (int x = 0; x < 120; x++)
		{
			for (int y = 0; y < 68; y++)
			{
				if (grid[x][y] == true)
				{
					artist.drawImage(tileA, x * 16, y * 16);
				}
				else
				{
					artist.drawImage(tileB, x * 16, y * 16);
				}
			}
		}
	}

	



	//main funcs
	void init()
	{ 
		//load textures
		tileA = artist.loadStreamableTexture("Resource/tileTest/tile0.png");
		tileB = artist.loadStreamableTexture("Resource/tileTest/tile1.png");
		
		//resize grid
		grid.resize(120);
		for (int i = 0; i < grid.size(); i++)
		{
			grid[i].resize(68);
		}
		//populate grid
		for (int x = 0; x < 120; x++)
		{
			for (int y = 0; y < 68; y++)
			{
				grid[x][y] = rand() % 2;
			}
		}
		//TEST MANIPULATING TEXTURE

		//load a base texture   dont need too if we can set the size manualy
		//gridTex = artist.loadStreamableTexture("Resource/tileTest/tileTemplate.png");
		gridTex = artist.loadTargetTexture(grid.size() * 16, grid[0].size() * 16);

		artist.setRenderTarget(gridTex);

		drawTiles();

		artist.setRenderTarget(NULL);
		//resize texture to fit the screen
		//gridTex = artist.resizeTexture(gridTex, grid.size() * 64, grid[0].size() * 64 );
		//tileA = artist.resizeTexture(tileA, 64, 64);
		//tileB = artist.resizeTexture(tileB, 64, 64);
		////transpose tile onto gridTex
		//for (int x = 0; x < grid.size(); x++)
		//{
		//	for (int y = 0; y < grid[x].size(); y++)
		//	{
		//		if (grid[x][y])
		//		{
		//			artist.transposeTexture(tileA, gridTex, x * 64, y * 64);
		//		}
		//		else
		//		{
		//			artist.transposeTexture(tileB, gridTex, x * 64, y * 64);
		//		}
		//	}
		//}
		

		//Map colors
		//Uint32 colorKey = SDL_MapRGB(mappingFormat, 255, 0, 0);
		//Uint32 transparent = SDL_MapRGBA(mappingFormat, 0, 0, 0, 0);
		//
		////Color key pixels
		//for (int i = 0; i < pixelCount; ++i)
		//{
		//	Uint8 r, g, b, a;
		//	SDL_GetRGBA(pixels[i], mappingFormat, &r, &g, &b, &a);
		//	if (pixels[i] == colorKey)
		//	{
		//		pixels[i] = transparent;
		//	}
		//}
		
		
		
		//unlock texture
		//artist.unlockTexture(gridTex);
	}

	void control()
	{
		if (Controller::keyboardStates[SDL_SCANCODE_ESCAPE] == 1)
		{
			running = false;
		}
	}

	void update()
	{

	}

	void draw()
	{
		//drawTiles();
		drawFinalGrid();
	}

public:




	//constructor
	tileTest()
	{
		//init
		init();

		//game loop
		while (running && !Controller::quit)
		{
			//Clear screen
			artist.clearScreen();

			//update user input
			controller.controller();


			//react to user input
			control();

			//run game logic
			update();

			//Draw everything
			draw();



			//FPS counter code
			if (Artist::displayFPS)
			{
				fpsCounter.updateFPS();

				artist.drawLetters(std::to_string(fpsCounter.getFPS()), 0, 1, Artist::smallFont);
			}

			//Update screen
			artist.updateScreen();
		}
	}
};