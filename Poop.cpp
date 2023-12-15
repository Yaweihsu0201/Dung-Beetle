#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Poop.h"
#define g 1;
Poop::Poop()
{
    mPosX = SCREEN_WIDTH/2;
    mPosY = 100;
	
	mCollider.w = POOP_WIDTH;
	mCollider.h = POOP_HEIGHT;
    mVelX = 0;
    mVelY = 0;
}

void Poop::move()
{
    mPosX += mVelX;
    mPosY += mVelY+g;
    
    if( ( mPosX < 0 ) || ( mPosX + POOP_WIDTH > SCREEN_WIDTH ) )
    {
        
        mPosX -= mVelX;
    } 
    
    if ( mPosY > 400) {
    	mPosY += mVelY-g;
	} else {
	}
	
	
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}
//! 
void Poop::render()
{
    
	if (!withBug) {
		gPoop.render( mPosX, mPosY );
	}
}

SDL_Rect Poop::PoopCollider() {
	return mCollider;
}
//! 
void Poop::discard() {
	mPosX = 300;
	mPosY = 460;
	withBug = true;
}
