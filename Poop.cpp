#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <string>
#include "Poop.h"
#define g 1;
Poop::Poop()
{
    mPosX = SCREEN_WIDTH/2-50;
    mPosY = 100;
	
	mCollider.w = POOP_WIDTH;
	mCollider.h = POOP_HEIGHT;
    mVelX = 0;
    mVelY = 0;
}

void Poop::move()
{
    mPosY += mVelY+g;
    
    
    if ( mPosY > 350) {
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

void Poop::set() {
	mPosX = SCREEN_WIDTH/2-50;
    mPosY = 100;
	withBug = false;
	mCollider.w = POOP_WIDTH;
	mCollider.h = POOP_HEIGHT;
    mVelX = 0;
    mVelY = 0;
}
