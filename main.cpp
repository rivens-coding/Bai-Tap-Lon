#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "sdl_utils.h"

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int CARD1 = 0;
const int CARD2 = 1;
const int CARD3 = 2;
const int CARD4 = 3;

const int FACE_UP = -1;
const int FACE_DOWN = -2;
const int REMOVED = -3;

 int card_suit[2][4] = {{CARD1,CARD2,CARD3,CARD4},
             {CARD1,CARD2,CARD3,CARD4}};

int card_locX[4] = {80,160,240,320};
int card_locY[2] = {120,240};

 int card_state[2][4] = {{FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN}};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

//Scene sprites
SDL_Rect gSpriteClips[ 8 ];

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
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
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render top left sprite
				gSpriteSheetTexture.render( 14, 30, &gSpriteClips[ 0 ] );

				gSpriteSheetTexture.render( 14 + gSpriteClips[ 1 ].w + 60, 30, &gSpriteClips[ 1 ] );

				gSpriteSheetTexture.render( 14 + 2*(gSpriteClips[ 2 ].w + 60), 30, &gSpriteClips[ 2 ] );

				//Render top right sprite
				gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 3 ].w - 14, 30, &gSpriteClips[ 3 ] );

				//Render bottom left sprite
				gSpriteSheetTexture.render( 14, SCREEN_HEIGHT - gSpriteClips[ 4 ].h - 40, &gSpriteClips[ 4 ] );

				gSpriteSheetTexture.render( 14 + gSpriteClips[ 5 ].w+60, SCREEN_HEIGHT - gSpriteClips[ 5 ].h - 40, &gSpriteClips[ 5 ] );

				gSpriteSheetTexture.render( 14 + 2*(gSpriteClips[ 6 ].w+60), SCREEN_HEIGHT - gSpriteClips[ 6 ].h - 40, &gSpriteClips[ 6 ] );

				//Render bottom right sprite
				gSpriteSheetTexture.render( SCREEN_WIDTH - gSpriteClips[ 7 ].w - 14, SCREEN_HEIGHT - gSpriteClips[ 7 ].h - 40, &gSpriteClips[ 7 ] );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
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

bool loadMedia()
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

void close()
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

void mix_cards()
{
    int holder;
    for (int i=0; i<20; i++)
    {
        int x0 = rand()%4;
        int y0 = rand()%2;
        int x1 = rand()%4;
        int y1 = rand()%2;

        holder = card_suit[y0][x0];
        card_suit[y0][x0] = card_suit[y1][x1];
        card_suit[y1][x1] = holder;
    }
}

int count_faces()
{
    int num_faces=0;
    for (int i=0; i< 2; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (card_state[i][j]==FACE_UP)
            {
                num_faces++;
            }
        }
    }
    return num_faces;
}

int get_arrY()
{
    SDL_Event e;
    int arrY;
    if(e.type == SDL_MOUSEBUTTONDOWN)
        arrY=e.button.y;//
    return arrY;
}

int get_arrX()
{
    SDL_Event e;
    int arrX;
    if(e.type == SDL_MOUSEBUTTONDOWN)
        arrX=e.button.x;//
    return arrX;
}

int find_card_suit()
{
    int suit;
    int y = get_arrY();
    int x = get_arrX();
    int cards_turned = count_faces();
    if (card_state[y][x] != REMOVED)
    {
        if (cards_turned<2)
        {
            card_state[y][x]=FACE_UP;
            suit = card_suit[y][x];
            return suit;
        }
        if (cards_turned>=2)
        {
            suit = 10;
            return suit;
        }
    }
    else return 10;
}

bool is_match()
{
    int suit1 = -6;
    int suit2 = -8;
    int x1,y1;
    int x2,y2;
    int counter=0;
    for (int i=0; i< 2; i++)
    {
        if (counter==2)
            break;

        for (int j=0; j<4; j++)
        {
            if (card_state[i][j] == -1)
            {
                counter++;

                if (counter == 1)
                {
                    suit1 = card_suit[i][j];
                    x1 =j;
                    y1 =i;
                }
                if (counter==2)
                {
                    suit2 = card_suit[i][j];
                    x2=j;
                    y2=i;
                    break;
                }
            }
        }
    }

        if (counter == 2)
        {
            if (suit1==suit2)
            {
                card_state[y1][x1]=REMOVED;
                card_state[y2][x2]=REMOVED;

                return true;
            }
            else
            {
            card_state[y1][x1]=FACE_DOWN;
            card_state[y2][x2]=FACE_DOWN;
            return false;
            }
        }
    else
        return false;
}
