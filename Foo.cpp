#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Foo.h"

Foo::Foo()
{
    //Initialize the offsets
    mPosX = SCREEN_WIDTH - 100;
    mPosY = 400;
	
	mCollider.w = FOO_WIDTH;
	mCollider.h = FOO_HEIGHT;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Foo::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX -= FOO_VEL; break;
            case SDLK_RIGHT: mVelX += FOO_VEL; break;
            case SDLK_UP: mVelY += 3; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT: mVelX += FOO_VEL; break;
            case SDLK_RIGHT: mVelX -= FOO_VEL; break;
            case SDLK_UP: mVelY -= 3; break;
        }
    }
}
void Foo::move()
{
    //Move the dot left or right
    mPosX += mVelX;
    mPosY -= mVelY-1;
	mCollider.x = mPosX;
	mCollider.y = mPosY;

    //If the dot went too far to the left or right
    
    if( ( mPosX < 0 ) || ( mPosX + FOO_WIDTH > SCREEN_WIDTH ) )
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

void Foo::render()
{
    //Show the dot
	gFooTexture.render( mPosX, mPosY );
}

