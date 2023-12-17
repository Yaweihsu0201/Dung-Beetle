#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <cmath>
#include "Poop.h"
#include "Bug2.h"
#include "Foo.h"
#include "LTexture.h"
//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GameState
{
public:
	//State transitions
	virtual bool enter() = 0;
	virtual bool exit() = 0;

	//Main loop functions
	virtual void handleEvent( SDL_Event& e ) = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//Make sure to call child destructors
	virtual ~GameState(){};
};

class IntroState : public GameState
{
public:
	//Static accessor
	static IntroState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static IntroState sIntroState;

	//Private constructor
	IntroState();

	//Intro background
	LTexture mBackgroundTexture;
};

class TitleState : public GameState
{
public:
	//Static accessor
	static TitleState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static TitleState sTitleState;

	//Private constructor
	TitleState();

	//Intro background
	LTexture mBackgroundTexture;

};

class OverWorldState : public GameState
{
public:
	//Static accessor
	static OverWorldState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Level dimensions
	const static int LEVEL_WIDTH = SCREEN_WIDTH * 2;
	const static int LEVEL_HEIGHT = SCREEN_HEIGHT * 2;
	int count;
	//Static instance
	static OverWorldState sOverWorldState;

	//Private constructor
	OverWorldState();

	//Overworld textures
	LTexture mBackgroundTexture;

	//Game objects
	Poop poop;
	Foo bug1;
	Bug2 bug2;

};

class ExitState : public GameState
{
public:
	//Static accessor
	static ExitState* get();

	//Transitions
	bool enter();
	bool exit();

	//Main loop functions
	void handleEvent( SDL_Event& e );
	void update();
	void render();

private:
	//Static instance
	static ExitState sExitState;

	//Private constructor
	ExitState();
};







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

//State managers
void setNextState( GameState* nextState );
void changeState();

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

//Globally used font
TTF_Font* gFont = NULL;

//Rendered texture
LTexture ScoreATexture;
LTexture ScoreBTexture;
//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gPoop;
LTexture gBug2;
LTexture poop_bug;
LTexture bug_poop;

//Game state object
GameState* gCurrentState = NULL;
GameState* gNextState = NULL;

IntroState* IntroState::get()
{
	//Get static instance
	return &sIntroState;
}

bool IntroState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "img/intro.png" ) )
	{
		printf( "Failed to intro background!\n" );
		success = false;
	}


	return success;
}

bool IntroState::exit()
{
	//Free background and text
	mBackgroundTexture.free();


	return true;
}


void IntroState::handleEvent( SDL_Event& e )
{
	//If the user pressed enter
	if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_RETURN ) )
	{
		//Move onto title state
		setNextState( TitleState::get() );
	}
}

void IntroState::update()
{

}

void IntroState::render()
{
	//Show the background
	mBackgroundTexture.render( 0, 0 );
}

IntroState IntroState::sIntroState;

IntroState::IntroState()
{
	//No public instantiation
}


TitleState* TitleState::get()
{
	//Get static instance
	return &sTitleState;
}

bool TitleState::enter()
{
	//Loading success flag
	bool success = true;

	//Load background
	if( !mBackgroundTexture.loadFromFile( "img/title.png" ) )
	{
		printf( "Failed to title background!\n" );
		success = false;
	}


	return success;
}

bool TitleState::exit()
{
	//Free background and text
	mBackgroundTexture.free();
	return true;
}

void TitleState::handleEvent( SDL_Event& e )
{
	//If the user pressed enter
	if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_RETURN ) )
	{
		//Move to overworld
		setNextState( OverWorldState::get() );
	}
}

void TitleState::update()
{

}

void TitleState::render()
{
	//Show the background
	mBackgroundTexture.render( 0, 0 );
}

//Declare static instance
TitleState TitleState::sTitleState;

TitleState::TitleState()
{
	//No public instantiation
}



OverWorldState* OverWorldState::get()
{
	//Get static instance
	return &sOverWorldState;
}

bool OverWorldState::enter()
{
	//Loading success flag
	bool success = true;
	count =0;
	//Load background
	if( !mBackgroundTexture.loadFromFile( "img/desert.png" ) )
	{
		printf( "Failed to load overworld background!\n" );
		success = false;
	}


	return success;
}

bool OverWorldState::exit()
{
	//Free textures
	mBackgroundTexture.free();
	

	return true;
}

void OverWorldState::handleEvent( SDL_Event& e )
{
	bug1.handleEvent(e);
	bug2.handleEvent(e);
}

void OverWorldState::update()
{

	bug1.move(poop.PoopCollider(), bug2.Collider(),count);
	bug2.move(poop.PoopCollider(), bug1.Collider(),count);
	poop.move();
				//!
	if (bug2.gotp() || bug1.gotp()) {
		poop.discard();
	}
	count += 1;
}

void OverWorldState::render()
{
	//Render background
	mBackgroundTexture.render( 0, 0);

	
	bool bug1gotp = bug1.gotp();
	bool bug2gotp = bug2.gotp();
	//Render objects
	bug1.render(bug2gotp);
	bug2.render(bug1gotp);
	poop.render();
}

//Declare static instance
OverWorldState OverWorldState::sOverWorldState;

OverWorldState::OverWorldState()
{
	//No public instantiation
}


//Hollow exit state
ExitState* ExitState::get()
{
	return &sExitState;
}

bool ExitState::enter()
{
	return true;
}
	
bool ExitState::exit()
{
	return true;
}

void ExitState::handleEvent( SDL_Event& e )
{

}

void ExitState::update()
{

}

void ExitState::render()
{

}

ExitState ExitState::sExitState;

ExitState::ExitState()
{

}





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
				//Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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
	
    //Open the font
    gFont = TTF_OpenFont( "texture/score.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
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
	//Free loaded images
    ScoreATexture.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    
    
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void setNextState( GameState* newState )
{
    //If the user doesn't want to exit
    if( gNextState != ExitState::get() )
    {
        //Set the next state
        gNextState = newState;
    }
}

void changeState()
{
    //If the state needs to be changed
    if( gNextState != NULL )
    {
		gCurrentState->exit();
		gNextState->enter();

        //Change the current state ID
        gCurrentState = gNextState;
        gNextState = NULL;
    }
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
			gCurrentState = IntroState::get();
			gCurrentState->enter();

						while( gCurrentState != ExitState::get() )
			{
				//Do state event handling
				while( SDL_PollEvent( &e ) != 0 )
				{
					//Handle state events
					gCurrentState->handleEvent( e );

					//Exit on quit
					if( e.type == SDL_QUIT )
					{
						setNextState( ExitState::get() );
					}
				}

				//Do state logic
				gCurrentState->update();

				//Change state if needed
				changeState();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Do state rendering
				gCurrentState->render();

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
