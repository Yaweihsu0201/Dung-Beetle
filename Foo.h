#ifndef FOO_H
#define FOO_H

#include "LTexture.h"
extern LTexture gBug1r;
extern LTexture gBug1l;
extern LTexture gBug1rp;
extern LTexture gBug1lp;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Foo
{
    public:
		static const int FOO_WIDTH = 75;
		static const int FOO_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int FOO_VEL = 4;

		//Initializes the variables
		Foo();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(const SDL_Rect& , const SDL_Rect&, int );
		//Shows the dot on the screen
		void render(bool othergotp);
		bool gotp();
		SDL_Rect Collider();
		int returnmScore();
		bool resetgoal();
		
		void set();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		bool withPoop;
		bool direction;	
		bool press_attack;
		bool hit;
		bool loss;
		int jump_times;
		bool conter_attack;
		bool goal;
		//The velocity of the dot
		int mVelX, mVelY;
		SDL_Rect mCollider;
		int mScore;
		
};
#endif
