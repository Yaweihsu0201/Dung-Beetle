#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Bug2.h"
Bug2::Bug2()
{
    //Initialize the offsets
    mPosX = 100;
    mPosY = 400;
	withPoop = false;
	direction = true;
	mCollider.w = BUG2_WIDTH;
	mCollider.h = BUG2_HEIGHT;
	//MODIFIED below: 
	press_attack = false;
	hit = false;
	jumptimes = 0;
	conter_attack = false;
	loss = false;
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
            case SDLK_a: mVelX -= BUG2_VEL;direction = false;break;
            case SDLK_d: mVelX += BUG2_VEL;direction = true ;break;
            case SDLK_w: mVelY += 3;jumptimes++;break;
			case SDLK_j: 
				if(!withPoop){
					press_attack=true;
				} 
				else{
					press_attack=false;
				}
				break;
			case SDLK_SPACE: 
				if(withPoop){
					conter_attack=true;
				}
				else
					conter_attack=false;
				break;

            
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
            case SDLK_j: press_attack=false; break;
			case SDLK_SPACE: conter_attack=false; break;
        }
    }
}
void Bug2::move(const SDL_Rect& R, const SDL_Rect& Bug2)
{
      //MODIFIED below: 增加重力變數以及跳躍落下的判定 
	int g=0;
   
    if(mPosY<400&& jumptimes==0){
    	g=3;
	}
	if(mPosY<300&& jumptimes!=0){
    	mVelY-=3;
    	jumptimes--;
	}
	//MODIFIED above
	
	
	//Move the dot left or right
    int newmVelX= mVelX;
	if (withPoop) {
    	newmVelX = mVelX/2;
	}
	mPosX += newmVelX;
    mPosY -= mVelY-g;

    //If the dot went too far to the left or right
    
    if( ( mPosX < 0 ) || ( mPosX + BUG2_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    } 
    
    if ( mPosY > 400) {
    	mPosY += mVelY-1;
	}
		
	if (SDL_HasIntersection(&R,&mCollider)) {
		withPoop = true;
	
	}
	if (SDL_HasIntersection(&Bug2,&mCollider)&&press_attack) {
		hit = true;
	}
	if (SDL_HasIntersection(&Bug2,&mCollider)&&conter_attack) {
		loss = true;
	}
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void Bug2::render(bool othergotp)
{
    //Show the dot
	if (withPoop) {
		if(loss){
			withPoop=false;			
			hit = false;
			conter_attack = false;
			press_attack = false;
			loss=false;
		}
	
		if (direction) {
			bug_poop.render( mPosX, mPosY );
		} else {
			poop_bug.render( mPosX, mPosY );
		}

	
	} 
	else {
		if (hit) {
			if(othergotp){ 
				withPoop = true;
			} 
			conter_attack = false;
			hit = false;
			loss=false;
			press_attack = false;
		}
		if (direction) {
			gBug2.render( mPosX, mPosY );
		} else {
			gFooTexture.render( mPosX, mPosY );
		}	
	}

}

SDL_Rect Bug2::Collider() {
	return mCollider;
}

bool Bug2::gotp() {
	return withPoop;
}
