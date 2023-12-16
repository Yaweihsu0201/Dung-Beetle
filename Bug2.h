#ifndef BUG2_H
#define BUG2_H

#include "LTexture.h"
extern LTexture gFooTexture;
extern LTexture poop_bug;
extern LTexture gBug2;
extern LTexture bug_poop;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Bug2
{
    public:
		static const int BUG2_WIDTH = 75;
		static const int BUG2_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int BUG2_VEL = 4;

		//Initializes the variables
		Bug2();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(const SDL_Rect& R, const SDL_Rect& Bug2);

		//Shows the dot on the screen
		void render(bool othergotp);
		
		SDL_Rect Collider();
		bool gotp();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		bool withPoop;
		bool direction;
		//MODIFIED below:
		bool press_attack;
		bool hit;
		bool loss;
		bool stopaccel;
		bool conter_attack;
		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect mCollider;
};
#endif
