#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Bug2.h"
#define g 1;
Bug2::Bug2()
{
    //Initialize the offsets
    mPosX = 100;
    mPosY = 400;
	
	mCollider.w = BUG2_WIDTH;
	mCollider.h = BUG2_HEIGHT;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Bug2::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_a: mVelX -= BUG2_VEL; break;
            case SDLK_d: mVelX += BUG2_VEL; break;
            case SDLK_w: mVelY += 2; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_a: mVelX += BUG2_VEL; break;
            case SDLK_d: mVelX -= BUG2_VEL; break;
            case SDLK_w: mVelY -= 2; break;
        }
    }
}
void Bug2::move()
{
    //Move the dot left or right
    mPosX += mVelX;
    mPosY -= mVelY-g;
	mCollider.x = mPosX;
	mCollider.y = mPosY;

    //If the dot went too far to the left or right
    
    if( ( mPosX < 0 ) || ( mPosX + BUG2_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    } 
    
    if ( mPosY > 400) {
    	mPosY += mVelY-1;
	}
	
	
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void Bug2::render()
{
    //Show the dot
	gBug2.render( mPosX, mPosY );
}

