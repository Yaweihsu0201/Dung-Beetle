#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include "Foo.h"

Foo::Foo()
{
    //Initialize the offsets
    mPosX = SCREEN_WIDTH - 100;
    mPosY = 350;
	withPoop = false;
	direction = false;
	press_attack = false;
	hit = false;
	jump_times = 0;
	conter_attack = false;
	mCollider.w = FOO_WIDTH;
	mCollider.h = FOO_HEIGHT;
	mScore =0;
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
            case SDLK_LEFT: mVelX -= FOO_VEL;direction=false; break;
            case SDLK_RIGHT: mVelX += FOO_VEL;direction = true; break;
            	//MODIFIED below: 改動跳躍數值以及跳躍判定 
			
			case SDLK_UP:mVelY += 3;jump_times++;break;
			case SDLK_SPACE: 
				if(!withPoop){
					press_attack=true;
				} 
				else{
					press_attack=false;
				}
				break;
			case SDLK_j:
				if(withPoop){
					conter_attack=true;
				}
				else
					conter_attack=false;
				break;
		
			//MODIFIED above
			
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
            case SDLK_SPACE: 
				press_attack=false; 
				break;
				
			case SDLK_j: 
				conter_attack=false;
				break;

        }
    }
}

void Foo::move(const SDL_Rect& R, const SDL_Rect& Bug2, int count)
{
      //MODIFIED below: 增加重力變數以及跳躍落下的判定 
	int g=0;
   
    if(mPosY<350&& jump_times==0){
    	g=3;
	}
	if(mPosY<250&& jump_times!=0){
    	mVelY-=3;
    	jump_times--;
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
    
    if( mPosX < 0 ) 
    {
        //Move back
        mPosX -= mVelX;
    } else if( mPosX + FOO_WIDTH > SCREEN_WIDTH) {
    	if (withPoop) {
    		goal = true;
    		withPoop = false;
		} else {
			mPosX -= mVelX;
		}
	}
    
    if ( mPosY > 350) {
    	mPosY += mVelY-1;
	}
		
	if (SDL_HasIntersection(&R,&mCollider) && count >= 10) {
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

void Foo::render(bool othergotp)
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
			gBug1rp.render( mPosX, mPosY );
		} else {
			gBug1lp.render( mPosX, mPosY );
		}

	
	} 
	else {
		if (hit) {
			if(othergotp){
				withPoop = true;
			} 
			conter_attack = false;
			hit = false;
			press_attack = false;
			loss=false;
		}
		if (direction) {
			gBug1r.render( mPosX, mPosY );
		} else {
			gBug1l.render( mPosX, mPosY );
		}
	}

}
bool Foo::gotp() {
	return withPoop;
}
SDL_Rect Foo::Collider() {
	return mCollider;
}

int Foo::returnmScore() {
	return mScore;
}

bool Foo::resetgoal() {
	bool currentgoal = goal;
	goal = false;
	return currentgoal;
	printf("end\n");
}

void Foo::set() {
	mPosX = SCREEN_WIDTH - 100;
    mPosY = 350;
	withPoop = false;
	direction = false;
	press_attack = false;
	hit = false;
	jump_times = 0;
	conter_attack = false;
	mCollider.w = FOO_WIDTH;
	mCollider.h = FOO_HEIGHT;
	mScore =0;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}
