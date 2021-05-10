#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>
#include "LTexture.h"
#include "sdl.h"
#include "LButtons.h"
#include "logic.h"

int card_suit_level1[2][4] = {{CARD1,CARD2,CARD3,CARD4},
             {CARD1,CARD2,CARD3,CARD4}};

int card_state_level1[2][4] = {{FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN}};

int card_suit_level2[4][6] = {{CARD11,CARD12,CARD13,CARD14,CARD15,CARD16},
             {CARD5,CARD6,CARD7,CARD8,CARD9,CARD10},{CARD11,CARD12,CARD13,CARD14,CARD15,CARD16},{CARD5,CARD6,CARD7,CARD8,CARD9,CARD10}};

int card_state_level2[4][6] = {{FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},{FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN}};

int card_suit_level3[4][9] = {{CARD1,CARD2,CARD3,CARD4,CARD5,CARD6,CARD7,CARD8,CARD9},
             {CARD10,CARD11,CARD12,CARD13,CARD14,CARD15,CARD16,CARD17,CARD18},
             {CARD1,CARD2,CARD3,CARD4,CARD5,CARD6,CARD7,CARD8,CARD9},
             {CARD10,CARD11,CARD12,CARD13,CARD14,CARD15,CARD16,CARD17,CARD18}};

int card_state_level3[4][9] = {{FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN},
             {FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN,FACE_DOWN}};

int play = 0;

int help = 0;

int back_time = 0;

int monitor = 0;

int clicked = 0;

int wrongs = 0;

int leave = 0;

int pairs = 0;

int last_played = 0;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene sprites
SDL_Rect gEasyLevel;
SDL_Rect gMediumLevel;
SDL_Rect gHardLevel;

SDL_Rect gPlaySprite[ BUTTON_SPRITE_TOTAL ];
SDL_Rect gHelpSprite[ BUTTON_SPRITE_TOTAL + 2];
SDL_Rect gBackSprite[ BUTTON_SPRITE_TOTAL ];
SDL_Rect gReplaySprite[ BUTTON_SPRITE_TOTAL ];
SDL_Rect gMenuSprite[ BUTTON_SPRITE_TOTAL ];

SDL_Rect gLevelSprite[ BUTTON_SPRITE_TOTAL ];

LButton gButtons[ TOTAL_BUTTONS ];

LTexture gEasyCards[2][4];
LTexture gMediumCards[4][6];
LTexture gHardCards[4][9];

LTexture gButtonSpriteSheetTexture[ TOTAL_BUTTONS ];
LTexture back_ground;
LTexture menu_bg;
LTexture instruction[3];

LTexture Tries;

LTexture game_over;
LTexture lose_back_ground;
LTexture you_wins;
LTexture win_back_ground;

//The music that will be played
Mix_Music *gMusic = NULL;
Mix_Music *gMusic1 = NULL;
Mix_Music *gMusic2 = NULL;

//The sound effects that will be used
Mix_Chunk *gFlip = NULL;
Mix_Chunk *gCorrect = NULL;
Mix_Chunk *gWin = NULL;
Mix_Chunk *gLose = NULL;

//Globally used font
TTF_Font *gFont = NULL;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		int i=0;//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			mix_cards(last_played);
			//print_cards();

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
					//Handle key press
					if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
							case SDLK_1:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gMusic, -1);
							}
							if( Mix_PlayingMusic() == 1 )
							{
								//Play the music
								Mix_PlayMusic( gMusic, -1);
							}
							break;

							case SDLK_2:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gMusic1, -1);
							}
							if( Mix_PlayingMusic() == 1 )
							{
								//Play the music
								Mix_PlayMusic( gMusic1, -1);
							}
							break;

							case SDLK_3:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gMusic2, -1);
							}
							if( Mix_PlayingMusic() == 1 )
							{
								//Play the music
								Mix_PlayMusic( gMusic2, -1);
							}
							break;

                            case SDLK_9:
                                //If the music is paused
								if( Mix_PausedMusic() == 1 )
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
								break;

							case SDLK_0:
                                //Stop the music
                                Mix_HaltMusic();
							break;

							case SDLK_ESCAPE:
                                close();
                            return 0;
						}
					}
				}
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                if(monitor == 0)
                    Menu(e);
                else if(monitor == 1)
                {
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    menuScreen(e);
                }
                else if(monitor == 2)
                {
                    GamePlay(&e);
                }
                else if(monitor == 3)
                {
                    GamePlay(&e);
                }
                else if(monitor == 4)
                {
                    GamePlay(&e);
                }
                else if(monitor == 5)
                {
                    //SDL_Delay(1000);
                    winScreen(e);
                }
                else if(monitor == 6)
                {
                    //SDL_Delay(1000);
                    loseScreen(e);
                }
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}
