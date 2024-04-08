#pragma once
#ifndef Artist
#include "Artist.h"
#endif
#ifndef SDL
#include <SDL.h>
#endif // !SDL
#ifndef vector
#include <vector>
#endif
#ifndef Controller
#include "Controller.h"
#endif // !Controller

class Button {
public:

	struct button {
		Artist::pos pos;
		Artist::pos size;
		bool activated;
		std::vector<SDL_Texture*> idleTex;
		std::vector<SDL_Texture*> hoverTex;
		std::vector<SDL_Texture*> activeTex;
		int frameTime;
		void (*activateFunc)(int);
		void (*hoverFunc)(int);
		void init(Artist::pos inPos, Artist::pos inSize, std::vector<SDL_Texture*> inIdleTex, std::vector<SDL_Texture*> inHoverTex, std::vector<SDL_Texture*> inActiveTex, int inFrameTime, void (*inActivateFunc)(int), void (*inHoverFunc)(int))
		{
			pos = inPos;
			size = inSize;
			activated = false;
			idleTex = inIdleTex;
			hoverTex = inHoverTex;
			activeTex = inActiveTex;
			frameTime = inFrameTime;
			activateFunc = inActivateFunc;
			hoverFunc = inHoverFunc;
		}
		void draw()
		{
			Artist artist;
			if (activated)
			{
				artist.drawAnimation(activeTex, pos.x, pos.y, frameTime, -1, size.x, size.y, 0, SDL_FLIP_NONE);
			}
			else if (Controller::mouseX >= pos.x && Controller::mouseX < pos.x + size.x && Controller::mouseY >= pos.y && Controller::mouseY < pos.y + size.y)
			{
				artist.drawAnimation(hoverTex, pos.x, pos.y, frameTime, -1, size.x, size.y, 0, SDL_FLIP_NONE);
			}
			else
			{
				artist.drawAnimation(idleTex, pos.x, pos.y, frameTime, -1, size.x, size.y, 0, SDL_FLIP_NONE);
			}
		}
		void update()//PROLLY NEEDS TO RUN !NOT! ON FRAME BASED TIMING
		{
			//check to see if we are hovering it
			if (Controller::mouseX >= pos.x && Controller::mouseX < pos.x + size.x && Controller::mouseY >= pos.y && Controller::mouseY < pos.y + size.y)
			{
				//if so run hover func and check if we clicked
				hoverFunc(0);
				if (Controller::mouseStates[0] == 1)
				{
					//if so run activate func and set button to active MAYBE IN FUTURE MAKE IT TAKE THE TIM TO PLAY OUT ACTIVE ANIMATION
					activated = true;
					activateFunc(0);
				}
			}
			
			
		}
	};
};