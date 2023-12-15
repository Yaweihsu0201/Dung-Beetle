#ifndef POOP_H
#define POOP_H

#include "LTexture.h"

extern LTexture gPoop;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Poop
{
    public:
		static const int POOP_WIDTH = 20;
		static const int POOP_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int POOP_VEL = 1;

		//Initializes the variables
		Poop();

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();
		
		SDL_Rect PoopCollider();
		

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect mCollider;
};
#endif
