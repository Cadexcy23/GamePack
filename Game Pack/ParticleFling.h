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



//TARGETTING WITH DATA
//TRAILS

class particleFling {
	
	// declare classses
	Artist artist;
	Controller controller;
	FPSCounter fpsCounter;

	struct particle {

		// declare classses
		Artist artist;

		SDL_Texture* tex;
		float xPos, yPos, xVel, yVel;
		int size;
		void draw()
		{
			artist.drawImage(tex, xPos - size / 2, yPos - size / 2, size, size);
		}
		void update()
		{
			
			xPos += xVel;
			yPos += yVel;
			if (xPos + size / 2 > Artist::SCREEN_WIDTH)
			{
				xVel *= -1;
			}
			if (xPos - size / 2 < 0)
			{
				xVel *= -1;
			}
			if (yPos + size / 2 > Artist::SCREEN_HEIGHT)
			{
				yVel *= -1;
			}
			if (yPos - size / 2 < 0)
			{
				yVel *= -1;
			}
		}
		bool compareCollision(particle comparePart)
		{
			int distance = abs(xPos - comparePart.xPos) + abs(yPos - comparePart.yPos);
			int overallSize = size / 2 + comparePart.size / 2;
			if (distance < overallSize)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		particle(float inXPos, float inYPos, float inXVel = 0, float inYVel = 0, int inSize = 5)
		{
			xPos = inXPos;
			yPos = inYPos;
			xVel = inXVel;
			yVel = inYVel;
			size = inSize;
			tex = artist.loadTexture("Resource/particleFling/particle.png");
		}
	};

	//game data
	bool running = true;
	std::vector<particle> particleList;
	int targetParticleID = 0;
	SDL_Texture* target;
	SDL_Texture* targetScreen;
	int lastSpawn = 0;
	Artist::pos clickPos = { -1, -1 };
	Artist::pos dragPos = { -1, -1 };
	bool pause;
	
	
	void drawTargetData()
	{
		artist.drawImage(targetScreen, 1792, 929);
		//make sure we have particles to look at
		if (particleList.size() > 0)
		{
			artist.drawImage(target, particleList[targetParticleID].xPos - 32, particleList[targetParticleID].yPos - 32);
			artist.drawLetters(std::to_string(targetParticleID), 1831, 935, Artist::smallFont);
			artist.drawLetters(std::to_string(particleList[targetParticleID].size), 1797, 984, Artist::smallFont);
			artist.drawLetters(std::to_string(particleList[targetParticleID].xVel), 1797, 1033, Artist::smallFont);
			artist.drawLetters(std::to_string(particleList[targetParticleID].yVel), 1797, 1054, Artist::smallFont);
			artist.drawImage(particleList[targetParticleID].tex, 1882 - particleList[targetParticleID].size / 2, 994 - particleList[targetParticleID].size / 2, particleList[targetParticleID].size, particleList[targetParticleID].size);

		}

	}

	//TEMP
	void overTimeSpawn()//maybe make color goals and then have it move towards each goal on a loop ALSO would always have to stay possitive
	{
		int currentTime = clock();
		if (lastSpawn < currentTime - 16)//check timer
		{
			particle tempParticle(Artist::SCREEN_WIDTH / 2, Artist::SCREEN_HEIGHT / 2, 10, -10);
			//decide color
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			int colorToSet = particleList.size() % 255;
			if (particleList.size() < 255)
			{
				r = 255;
				g = 255 - colorToSet;
				b = 255 - colorToSet;
				
			}
			else if (particleList.size() < 510)
			{
				r = 255;
				g = colorToSet;
				b = colorToSet;
			}
			else if (particleList.size() < 765)
			{
				r = 255 - colorToSet;
				g = 255;
				b = 255 - colorToSet;
			}
			else if (particleList.size() < 1020)
			{
				r = colorToSet;
				g = 255;
				b = colorToSet;
			}
			else if (particleList.size() < 1275)
			{
				r = 255 - colorToSet;
				g = 255 - colorToSet;
				b = 255;
			}
			else if (particleList.size() < 1530)
			{
				r = colorToSet;
				g = colorToSet;
				b = 255;
			}
			else if (particleList.size() < 1785)
			{
				r = 255;
				g = 255;
				b = 255 - colorToSet;
			}
			else if (particleList.size() < 2040)
			{
				r = 255;
				g = 255;
				b = colorToSet;
			}
			else if (particleList.size() < 2295)
			{
				r = 255;
				g = 255 - colorToSet;
				b = 255;
			}
			else if (particleList.size() < 2550)
			{
				r = 255;
				g = colorToSet;
				b = 255;
			}
			else if (particleList.size() < 2805)
			{
				r = 255 - colorToSet;
				g = 255;
				b = 255;
			}
			else if (particleList.size() < 3060)
			{
				r = colorToSet;
				g = 255;
				b = 255;
			}
			
			SDL_SetTextureColorMod(tempParticle.tex, r, g, b);
			particleList.push_back(tempParticle);
			lastSpawn = currentTime;
		}
	}

	//TEMP
	void loadRandomParticle(int amount)
	{
		for (int i = 0; i < amount; i++)
		{
			particle tempParticle(Artist::SCREEN_WIDTH / 2, Artist::SCREEN_HEIGHT / 2);
			tempParticle.xVel = float(rand() % 10000) * 0.001 - 5.0;
			tempParticle.yVel = float(rand() % 10000) * 0.001 - 5.0;
			tempParticle.size = rand() % 64 + 1;
			SDL_SetTextureColorMod(tempParticle.tex, rand() % 255, rand() % 255, rand() % 255);
			SDL_SetTextureAlphaMod(tempParticle.tex, 200);
			particleList.push_back(tempParticle);
		}
	}

	void drawClickPos()
	{
		if (dragPos.x != -1)
		{
			int xDist = clickPos.x - dragPos.x, yDist = clickPos.y - dragPos.y;
			artist.drawLineFromPoints(clickPos.x, clickPos.y, clickPos.x + xDist, clickPos.y + yDist);
			//artist.drawImage(target, clickPos.x - 32, clickPos.y - 32);
			//artist.drawImage(target, dragPos.x - 32, dragPos.y - 32);
		}
	}

	void setClickPos()
	{
		clickPos = { Controller::mouseX, Controller::mouseY };
	}

	void updateDragPos()
	{
		if (clickPos.x != -1)
		{
			dragPos = { Controller::mouseX, Controller::mouseY };
		}
	}

	void releaseClickPos()
	{
		if (clickPos.x != -1)
		{
			particle tempParticle(clickPos.x, clickPos.y);
			tempParticle.xVel = (clickPos.x - dragPos.x) * 0.1;
			tempParticle.yVel = (clickPos.y - dragPos.y) * 0.1;
			tempParticle.size = 10;
			SDL_SetTextureColorMod(tempParticle.tex, rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);

			particleList.push_back(tempParticle);


			clickPos = { -1, -1 };
			dragPos = { -1, -1 };
		}
	}

	void updateParticleCollision(int particleID)
	{
		for (int i = 0; i < particleList.size(); i++)
		{
			if (i != particleID)
			{
				if (particleList[i].compareCollision(particleList[particleID]))
				{
					//get the difference in X and Y of the 2 particles
					float xDif = particleList[i].xPos - particleList[particleID].xPos, yDif = particleList[i].yPos - particleList[particleID].yPos;
					float totalDif = xDif + yDif;
					//figure out the ratio of X to Y
					float aTotalVel = abs(particleList[i].xVel) + abs(particleList[i].yVel), bTotalVel = abs(particleList[particleID].xVel) + abs(particleList[particleID].yVel);
					//also keep track of negatives
					//spread the total velocity across the 2 according to the ratio
					float xApplyPercent = totalDif / xDif, yApplyPercent = totalDif / yDif;
					particleList[i].xVel += xApplyPercent * aTotalVel;
					particleList[i].yVel += yApplyPercent * aTotalVel;
					particleList[particleID].xVel += -1 * xApplyPercent * bTotalVel;
					particleList[particleID].yVel += -1 * yApplyPercent * bTotalVel;
					//NEEDS WORK
				}

			}
			
		}
	}


	//controll game from user input
	int control()
	{
		if (Controller::keyboardStates[SDL_SCANCODE_ESCAPE] == 1)
		{
			running = false;
			
		}
		if (Controller::keyboardStates[SDL_SCANCODE_UP] == 1)
		{
			if (particleList.size() > 0)
			{
				targetParticleID++;
				if (targetParticleID > particleList.size() - 1)
				{
					targetParticleID = 0;
				}
			}
		}
		if (Controller::keyboardStates[SDL_SCANCODE_DOWN] == 1)
		{
			if (particleList.size() > 0)
			{
				targetParticleID--;
				if (targetParticleID < 0)
				{
					targetParticleID = particleList.size() - 1;
				}
			}
		}
		if (Controller::keyboardStates[SDL_SCANCODE_RIGHT] == 1)
		{
			if (pause)
			{
				pause = false;
			}
			else
			{
				pause = true;
			}
		}
		if (Controller::keyboardStates[SDL_SCANCODE_SPACE] == 1)
		{
			if (particleList.size() > 0)
			{
				particleList.erase(particleList.begin() + targetParticleID);
				if (targetParticleID > particleList.size() - 1)
				{
					targetParticleID = particleList.size() - 1;
				}
			}
		}
		if (Controller::keyboardStates[SDL_SCANCODE_RETURN])
		{
			loadRandomParticle(10);
		}
		if (Controller::keyboardStates[SDL_SCANCODE_RSHIFT] == 1)
		{
			particleList.clear();
			targetParticleID = 0;
		}
		if (Controller::mouseStates[0] == 1)
		{
			setClickPos();
		}
		if (Controller::mouseStates[0] == 2)
		{
			updateDragPos();
		}
		if (Controller::mouseStates[0] == 3)
		{
			releaseClickPos();
		}

		return 0;
	}

	//updates game logic
	int update()
	{
		if (Controller::TickLimiter)
		{
			if (!pause)
			{
				for (int i = 0; i < particleList.size(); i++)
				{
					particleList[i].update();
					//updateParticleCollision(i); //NOT WORKING
				}
			}
		}

		//overTimeSpawn();

		return 0;
	}

	//draws the graphics
	int draw()
	{
		for (int i = 0; i < particleList.size(); i++)
		{
			particleList[i].draw();
			//shows ID attached to particle
			//artist.drawLetters(std::to_string(i), particleLst[i].xPos, particleLst[i].yPos, Artist::smallFont);
		}
		
		drawTargetData();
		drawClickPos();

		return 0;
	}


public:

	
	

	//constructor
	particleFling()
	{
		//initialize any starting data
		target = artist.loadTexture("Resource/particleFling/target.png");
		targetScreen = artist.loadTexture("Resource/particleFling/targetScreen.png");

		srand(clock());
		
		//loadRandomParticle(1000);
		
		

		//game loop
		while (running && !Controller::quit)
		{
			//Clear screen
			artist.clearScreen();

			//update user input
			controller.controller();


			//react to use input
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




