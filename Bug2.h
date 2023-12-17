#ifndef BUG2_H
#define BUG2_H

#include "LTexture.h"
extern LTexture gBug2r;
extern LTexture gBug2l;
extern LTexture gBug2rp;
extern LTexture gBug2lp;
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
		void move(const SDL_Rect& R, const SDL_Rect& Bug2,int);

		//Shows the dot on the screen
		void render(bool othergotp);
		
		SDL_Rect Collider();
		bool gotp();
		int returnmScore();
		bool resetgoal();
		void set();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		bool withPoop;
		bool direction;
		//MODIFIED below:
		bool press_attack;
		bool hit;
		bool loss;
		int jumptimes;
		bool conter_attack;
		bool goal;
		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect mCollider;
		int mScore;
		
};
#endif
