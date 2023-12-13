#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Poop.h"
#define g 1;
Poop::Poop()
{
    //Initialize the offsets
    mPosX = SCREEN_WIDTH/2;
    mPosY = 100;
	
	mCollider.w = POOP_WIDTH;
	mCollider.h = POOP_HEIGHT;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Poop::move()
{
    //Move the dot left or right
    mPosX += mVelX;
    mPosY -= mVelY-g;
	mCollider.x = mPosX;
	mCollider.y = mPosY;

    //If the dot went too far to the left or right
    
    if( ( mPosX < 0 ) || ( mPosX + POOP_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    } 
    
    if ( mPosY > 400) {
    	mPosY += mVelY-1;
	} else {
		printf("in the air\n");
	}
	
	
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void Poop::render()
{
    //Show the dot
	gPoop.render( mPosX, mPosY );
}

