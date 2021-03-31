#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "sdl_utils.h"

bool init(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia(LTexture gSpriteSheetTexture, SDL_Rect gSpriteClips[ 8 ])
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "D:/CodeinCodeBlock/New_project/back_of_the_cards.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
	{
		//Set top left sprite
		gSpriteClips[ 0 ].x = 0;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w = 248;
		gSpriteClips[ 0 ].h = 350;

        gSpriteClips[ 1 ].x = 0;
		gSpriteClips[ 1 ].y = 0;
		gSpriteClips[ 1 ].w = 248;
		gSpriteClips[ 1 ].h = 350;

		gSpriteClips[ 2 ].x = 0;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w = 248;
		gSpriteClips[ 2 ].h = 350;

        //Set top right sprite
		gSpriteClips[ 3 ].x = 0;
		gSpriteClips[ 3 ].y = 0;
		gSpriteClips[ 3 ].w = 248;
		gSpriteClips[ 3 ].h = 350;

        //Set bottom left sprite
		gSpriteClips[ 4 ].x = 0;
		gSpriteClips[ 4 ].y = 0;
		gSpriteClips[ 4 ].w = 248;
		gSpriteClips[ 4 ].h = 350;

		gSpriteClips[ 5 ].x = 0;
		gSpriteClips[ 5 ].y = 0;
		gSpriteClips[ 5 ].w = 248;
		gSpriteClips[ 5 ].h = 350;

		gSpriteClips[ 6 ].x = 0;
		gSpriteClips[ 6 ].y = 0;
		gSpriteClips[ 6 ].w = 248;
		gSpriteClips[ 6 ].h = 350;

		//Set bottom right sprite
		gSpriteClips[ 7 ].x = 0;
		gSpriteClips[ 7 ].y = 0;
		gSpriteClips[ 7 ].w = 248;
		gSpriteClips[ 7 ].h = 350;
	}

	return success;
}

void close(SDL_Window* gWindow, LTexture gSpriteSheetTexture, SDL_Renderer* gRenderer)
{
	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

