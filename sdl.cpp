#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "sdl.h"
#include "LButtons.h"

//The window we'll be rendering to
extern SDL_Window* gWindow ;

//The window renderer
extern SDL_Renderer* gRenderer ;

//Scene sprites
extern SDL_Rect gEasyLevel;
extern SDL_Rect gMediumLevel;
extern SDL_Rect gHardLevel;

extern SDL_Rect gPlaySprite[ BUTTON_SPRITE_TOTAL ];
extern SDL_Rect gHelpSprite[ BUTTON_SPRITE_TOTAL + 2];
extern SDL_Rect gBackSprite[ BUTTON_SPRITE_TOTAL ];
extern SDL_Rect gReplaySprite[ BUTTON_SPRITE_TOTAL ];
extern SDL_Rect gMenuSprite[ BUTTON_SPRITE_TOTAL ];

extern SDL_Rect gLevelSprite[ BUTTON_SPRITE_TOTAL ];

//The music that will be played
extern Mix_Music *gMusic ;
extern Mix_Music *gMusic1 ;
extern Mix_Music *gMusic2 ;

//The sound effects that will be used
extern Mix_Chunk *gFlip ;
extern Mix_Chunk *gCorrect ;
extern Mix_Chunk *gWin ;
extern Mix_Chunk *gLose ;

//Globally used font
extern TTF_Font *gFont ;

extern LButton gButtons[ TOTAL_BUTTONS ];

extern LTexture gEasyCards[2][4];
extern LTexture gMediumCards[4][6];
extern LTexture gHardCards[4][9];

extern LTexture gButtonSpriteSheetTexture[ TOTAL_BUTTONS ];
extern LTexture back_ground;
extern LTexture menu_bg;
extern LTexture instruction[3];

extern LTexture Tries;

extern LTexture game_over;
extern LTexture lose_back_ground;
extern LTexture you_wins;
extern LTexture win_back_ground;

//Globally used font
extern TTF_Font *gFont ;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
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
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
	//Loading success flag
	bool success = true;

	//Set text color as black
    //SDL_Color textColor = { 255, 255, 255, 255 };
    //Load easy level cards
	for(int i = 0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(!gEasyCards[i][j].loadFromFile( "./images/back_of_the_cards_level1.png" ))
            {
                printf( "Failed to load easy sprite sheet texture!\n" );
                success = false;
            }
        }
    }
	//Load medium level cards
	for(int i = 0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(!gMediumCards[i][j].loadFromFile( "./images/back_of_the_cards_level2.png" ))
            {
                printf( "Failed to load medium sprite sheet texture!\n" );
                success = false;
            }
        }
    }
    //Load hard level cards
	for(int i = 0;i<4;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(!gHardCards[i][j].loadFromFile( "./images/back_of_the_cards_level2.png" ))
            {
                printf( "Failed to load hard sprite sheet texture!\n" );
                success = false;
            }
        }
    }

	//Load sprite sheet texture
	if( !menu_bg.loadFromFile( "./images/back_ground.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !back_ground.loadFromFile( "./images/background4.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !you_wins.loadFromFile( "./images/you_win.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !game_over.loadFromFile( "./images/game_over.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !win_back_ground.loadFromFile( "./images/win_back_ground.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !lose_back_ground.loadFromFile( "./images/game_over3.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	//Load buttons sprite sheet texture
	else if( !gButtonSpriteSheetTexture[PLAY_BUTTONS].loadFromFile( "./images/play_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[HELP_BUTTONS].loadFromFile( "./images/help_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[BACK_BUTTONS].loadFromFile( "./images/back_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[REPLAY_BUTTONS].loadFromFile( "./images/replay_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[MENU_BUTTONS].loadFromFile( "./images/menu_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[EASY_BUTTONS].loadFromFile( "./images/easy_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[MEDIUM_BUTTONS].loadFromFile( "./images/medium_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[HARD_BUTTONS].loadFromFile( "./images/hard_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !instruction[0].loadFromFile( "./images/instruction.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !instruction[1].loadFromFile( "./images/instruction1.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !instruction[2].loadFromFile( "./images/instruction2.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	//Load music
	else if( !( gMusic = Mix_LoadMUS( "./sounds/jazz.wav"  ) ) )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gMusic1 = Mix_LoadMUS( "./sounds/jazz1.wav"  ) ) )
	{
		printf( "Failed to load beat music1! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gMusic2 = Mix_LoadMUS( "./sounds/jazz2.wav"  ) ) )
	{
		printf( "Failed to load beat music2! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Load sound effects
	else if( !( gFlip = Mix_LoadWAV( "./sounds/flip_card_sound.wav"  ) ) )
	{
		printf( "Failed to load flip sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gCorrect = Mix_LoadWAV( "./sounds/correct.wav"  ) ) )
	{
		printf( "Failed to load correct sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gWin = Mix_LoadWAV( "./sounds/win.wav"  ) ) )
	{
		printf( "Failed to load win sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gLose = Mix_LoadWAV( "./sounds/game_over.wav"  ) ) )
	{
		printf( "Failed to load lose sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Open the font
	else if( !( gFont = TTF_OpenFont( "./font/font.ttf", 58 ) ) )
	{
		printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set easy cards sprite
		gEasyLevel.x = 0;
		gEasyLevel.y = 0;
		gEasyLevel.w = 213;
		gEasyLevel.h = 300;

		//Set medium cards sprite
		gMediumLevel.x = 0;
		gMediumLevel.y = 0;
		gMediumLevel.w = 107;
		gMediumLevel.h = 150;

		//Set hard cards sprite
		gHardLevel.x = 0;
		gHardLevel.y = 0;
		gHardLevel.w = 107;
		gHardLevel.h = 150;

		//Set sprites
        for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gPlaySprite[i].x = i*BUTTON_WIDTH;
			gPlaySprite[i].y = 0;
			gPlaySprite[i].w = BUTTON_WIDTH;
			gPlaySprite[i].h = BUTTON_HEIGHT;

			gHelpSprite[i].x = i*(BUTTON_WIDTH+1);
			gHelpSprite[i].y = 0;
			gHelpSprite[i].w = BUTTON_WIDTH;
			gHelpSprite[i].h = BUTTON_HEIGHT;

			gBackSprite[i].x = i*(BUTTON_WIDTH/3+1);
			gBackSprite[i].y = 0;
			gBackSprite[i].w = BUTTON_WIDTH/3;
			gBackSprite[i].h = BUTTON_HEIGHT/3;

			gReplaySprite[i].x = i*BUTTON_WIDTH;
			gReplaySprite[i].y = 0;
			gReplaySprite[i].w = BUTTON_WIDTH;
			gReplaySprite[i].h = BUTTON_HEIGHT;

			gMenuSprite[i].x = i*BUTTON_WIDTH;
			gMenuSprite[i].y = 0;
			gMenuSprite[i].w = BUTTON_WIDTH;
			gMenuSprite[i].h = BUTTON_HEIGHT;

			gLevelSprite[i].x = i*405/2;
			gLevelSprite[i].y = 0;
			gLevelSprite[i].w = 405/2;
			gLevelSprite[i].h = 75;
		}

		gHelpSprite[2].x = 0;
        gHelpSprite[2].y = 0;
        gHelpSprite[2].w = 284;
        gHelpSprite[2].h = 400;

        gHelpSprite[3].x = 0;
        gHelpSprite[3].y = 0;
        gHelpSprite[3].w = 284;
        gHelpSprite[3].h = 400;

		//Set buttons in center
		gButtons[ 0 ].setPosition( SCREEN_WIDTH/2-BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 + 80 );
		gButtons[ 1 ].setPosition( SCREEN_WIDTH/2-BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 + 250 );
		gButtons[ 2 ].setPosition( 10 , 10 );
		gButtons[ 5 ].setPosition( SCREEN_WIDTH/2-405/4, SCREEN_HEIGHT/2 - 75/2 + 50 );
		gButtons[ 6 ].setPosition( SCREEN_WIDTH/2-405/4, SCREEN_HEIGHT/2 - 75/2 + 150 );
		gButtons[ 7 ].setPosition( SCREEN_WIDTH/2-405/4, SCREEN_HEIGHT/2 - 75/2 + 250 );
	}

	return success;
}

void close()
{
	//Free loaded images
	for (int i=0; i<2; i++)
    {
        for (int j=0; j<4; j++)
            gEasyCards[i][j].free();
    }
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<6; j++)
            gMediumCards[i][j].free();
    }
    for (int i=0; i<4; i++)
    {
        for (int j=0; j<9; j++)
            gHardCards[i][j].free();
    }
    for (int i=0; i<TOTAL_BUTTONS; i++)
    {
        gButtonSpriteSheetTexture[i].free();
    }
    for (int i=0; i<3; i++)
    {
        instruction[i].free();
    }
    back_ground.free();
    menu_bg.free();
    game_over.free();
    you_wins.free();
    Tries.free();
    win_back_ground.free();
    lose_back_ground.free();

    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Free the sound effects
	Mix_FreeChunk( gFlip );
	Mix_FreeChunk( gCorrect );
	Mix_FreeChunk( gWin );
	Mix_FreeChunk( gLose );
	gFlip = NULL;
	gCorrect = NULL;
	gWin = NULL;
	gLose = NULL;

	//Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
	Mix_FreeMusic( gMusic1 );
	gMusic1 = NULL;
	Mix_FreeMusic( gMusic2 );
	gMusic2 = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
