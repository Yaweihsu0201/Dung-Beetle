#ifndef BUG2_H
#define BUG2_H

#include "LTexture.h"

extern LTexture gBug2;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Bug2
{
    public:
		static const int BUG2_WIDTH = 75;
		static const int BUG2_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int BUG2_VEL = 1;

		//Initializes the variables
		Bug2();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();
		

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect mCollider;
};
#endif
