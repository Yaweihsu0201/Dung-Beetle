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
		static const int POOP_VEL = 1;

		Poop();

		void move();

		void render();
		
		SDL_Rect PoopCollider();
		//!
		void discard();
		
		void set();
	
    private:
		int mPosX, mPosY;
		//!
		bool withBug;
		int mVelX, mVelY;
		SDL_Rect mCollider;
};
#endif
