#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Poop.h"
#include "Bug2.h"
#include "Foo.h"
#include "LTexture.h"
//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};




//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gPoop;
LTexture gBug2;
LTexture poop_bug;
LTexture bug_poop;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else {
	
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{

			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{

	bool success = true;

	if( !gFooTexture.loadFromFile( "img/bug2.png" ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	if( !gPoop.loadFromFile( "img/poop.png" ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	
	if( !gBackgroundTexture.loadFromFile( "img/desert.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	
	if( !gBug2.loadFromFile( "img/bug3.png" ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	//!
	if (!poop_bug.loadFromFile("img/poop_bug.png"))
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	//!
	if (!bug_poop.loadFromFile("img/bug_poop.png"))
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	
    
	return success;
}

void close()
{
	//Free loaded images
	gFooTexture.free();
	gBackgroundTexture.free();
	gBug2.free();
	gPoop.free();
	poop_bug.free();
	
    
    
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{	
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{	
		printf("Success to initialize!\n");
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;
			
			//Event handler
			SDL_Event e;
			
			SDL_Color textColor = { 255, 255, 255, 255 };
			std::stringstream ScoreAText;
			std::stringstream ScoreBText;
			Foo foo;
			Bug2 bug2;
			Poop poop;
			//While application is running
			while( !quit )
			{	
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					} 
               	
					foo.handleEvent(e);
					bug2.handleEvent(e);
					
				}
				bool bug2p = bug2.gotp();
				bool foop = foo.gotp();
				foo.move(poop.PoopCollider(), bug2.Collider());
				bug2.move(poop.PoopCollider(), foo.Collider());
				poop.move();
				//!
				if (bug2.gotp() || foo.gotp()) {
					poop.discard();
				}
			
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//Render background texture to screen
				
				gBackgroundTexture.render( 0, 0 ); 
				//Render Foo' to the screen
				foo.render(bug2p);
				bug2.render(foop);
				poop.render();
				//Render textures
				//Update screen
				SDL_RenderPresent( gRenderer );
				SDL_Delay(10);
			}
		}
	}
	
	//Free resources and close SDL
	close();

	return 0;
}
