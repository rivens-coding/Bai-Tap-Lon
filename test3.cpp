#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int CARD1 = 0;
const int CARD2 = 1;
const int CARD3 = 2;
const int CARD4 = 3;
const int CARD5 = 4;
const int CARD6 = 5;
const int CARD7 = 6;
const int CARD8 = 7;
const int CARD9 = 8;
const int CARD10 = 9;
const int CARD11 = 10;
const int CARD12 = 11;
const int CARD13 = 12;
const int CARD14 = 13;
const int CARD15 = 14;
const int CARD16 = 15;
const int CARD17 = 16;
const int CARD18 = 17;

const int FACE_UP = -1;
const int FACE_DOWN = -2;
const int REMOVED = -3;

//Button constants
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 150;

const int TOTAL_BUTTONS = 8;

const int PLAY_BUTTONS = 0;
const int HELP_BUTTONS = 1;
const int BACK_BUTTONS = 2;
const int REPLAY_BUTTONS = 3;
const int MENU_BUTTONS = 4;
const int EASY_BUTTONS = 5;
const int MEDIUM_BUTTONS = 6;
const int HARD_BUTTONS = 7;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_TOTAL = 2
};

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

//Texture wrapper class
class LTexture
{
	public:
		int suits;

		int state;

		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

		//Renders texture at given point
		void renderButtons( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handlePlayButton( SDL_Event* e);

		void handleReplayButton( SDL_Event* e);

		void handleMenuButton( SDL_Event* e);

		void handleHelpButton( SDL_Event* e);

        void handleBackButton( SDL_Event* e);

        void handleEasyButton( SDL_Event* e);

        void handleMediumButton( SDL_Event* e);

        void handleHardButton( SDL_Event* e);

		//Shows button sprite
		void render(int i,SDL_Rect* gSprite);

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
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

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::renderButtons( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::render(int i,SDL_Rect* gSprite)
{
	//Show current button sprite
    gButtonSpriteSheetTexture[i].renderButtons( mPosition.x, mPosition.y, &gSprite[ mCurrentSprite ] );
}

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

	int flag = 0;

	//Set text color as black
    //SDL_Color textColor = { 255, 255, 255, 255 };
    //Load easy level cards
	for(int i = 0;i<2;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(!gEasyCards[i][j].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level1.png" ))
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
            if(!gMediumCards[i][j].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level2.png" ))
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
            if(!gHardCards[i][j].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level2.png" ))
            {
                printf( "Failed to load hard sprite sheet texture!\n" );
                success = false;
            }
        }
    }

	//Load sprite sheet texture
	if( !menu_bg.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_ground.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !back_ground.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/background4.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !you_wins.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/you_win.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !game_over.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/game_over.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !win_back_ground.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/win_back_ground.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !lose_back_ground.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/game_over3.png" ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	//Load buttons sprite sheet texture
	else if( !gButtonSpriteSheetTexture[PLAY_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/play_button_test2.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[HELP_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/help_button_test3.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[BACK_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[REPLAY_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/replay_button_new.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[MENU_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/menu_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[EASY_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/easy_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[MEDIUM_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/medium_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !gButtonSpriteSheetTexture[HARD_BUTTONS].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/hard_button.png"  ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	else if( !instruction[0].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/instruction.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !instruction[1].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/instruction1.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else if( !instruction[2].loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/instruction2.png"  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	//Load music
	else if( !( gMusic = Mix_LoadMUS( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/jazz.wav"  ) ) )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gMusic1 = Mix_LoadMUS( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/jazz1.wav"  ) ) )
	{
		printf( "Failed to load beat music1! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gMusic2 = Mix_LoadMUS( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/jazz2.wav"  ) ) )
	{
		printf( "Failed to load beat music2! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Load sound effects
	else if( !( gFlip = Mix_LoadWAV( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/flip_card_sound.wav"  ) ) )
	{
		printf( "Failed to load flip sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gCorrect = Mix_LoadWAV( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/correct.wav"  ) ) )
	{
		printf( "Failed to load correct sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gWin = Mix_LoadWAV( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/win.wav"  ) ) )
	{
		printf( "Failed to load win sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	else if( !( gLose = Mix_LoadWAV( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/game_over.wav"  ) ) )
	{
		printf( "Failed to load lose sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Open the font
	else if( !( gFont = TTF_OpenFont( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/font.ttf", 58 ) ) )
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

int get_arrY(SDL_Event* e)
{
    int arrY;
    if(monitor == 2)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        arrY = e->button.y/400;
    }
    if(monitor == 3)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            if(e->button.y>=75 && e->button.y<=240)
                arrY = 0;
            if(e->button.y>=255 && e->button.y<=405)
                arrY = 1;
            if(e->button.y>=420 && e->button.y<=570)
                arrY = 2;
            if(e->button.y>=585 && e->button.y<=735)
                arrY = 3;
        }
    }
    if(monitor == 4)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            if(e->button.y>=75 && e->button.y<=240)
                arrY = 0;
            if(e->button.y>=250 && e->button.y<=400)
                arrY = 1;
            if(e->button.y>=410 && e->button.y<=560)
                arrY = 2;
            if(e->button.y>=570 && e->button.y<=720)
                arrY = 3;
        }
    }
    return arrY;
}

int get_arrX(SDL_Event* e)
{
    int arrX;
    if(monitor == 2)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        arrX = e->button.x/311;
    }
    if(monitor == 3)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        arrX = e->button.x/202;
    }
    if(monitor == 4)
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            if(e->button.x>=35 && e->button.x<=142)
                arrX = 0;
            if(e->button.x>=162 && e->button.x<=269)
                arrX = 1;
            if(e->button.x>=289 && e->button.x<=396)
                arrX = 2;
            if(e->button.x>=416 && e->button.x<=523)
                arrX = 3;
            if(e->button.x>=543 && e->button.x<=650)
                arrX = 4;
            if(e->button.x>=670 && e->button.x<=777)
                arrX = 5;
            if(e->button.x>=797 && e->button.x<=904)
                arrX = 6;
            if(e->button.x>=924 && e->button.x<=1031)
                arrX = 7;
            if(e->button.x>=1051 && e->button.x<=1158)
                arrX = 8;
        }
    }
    return arrX;
}

int count_faces() // count the number of cards that are facing up.
{
    int num_faces=0;

    // goes through card_state[][] and adds 1 to num_faces
    // every time it sees the value corresponding to FACE_UP;
    if(monitor == 2)
    {
        for (int i=0; i< 2; i++)
        {
            for (int j=0; j<4; j++)
            {
                if (gEasyCards[i][j].state == FACE_UP)
                {
                    num_faces++;
                }
            }
        }
    }
    if(monitor == 3)
    {
        for (int i=0; i< 4; i++)
        {
            for (int j=0; j<6; j++)
            {
                if (gMediumCards[i][j].state == FACE_UP)
                {
                    num_faces++;
                }
            }
        }
    }
    if(monitor == 4)
    {
        for (int i=0; i< 4; i++)
        {
            for (int j=0; j<9; j++)
            {
                if (gHardCards[i][j].state == FACE_UP)
                {
                    num_faces++;
                }
            }
        }
    }

    return num_faces;
}

// finds the suit of the card that has been clicked.
// also changes the state of that card from face down to face up.
int find_card_suit(SDL_Event e)
{
    int suit; // giving it a random number that is not one assigned to a type.
    int y = get_arrY(&e);
    int x = get_arrX(&e);
    int cards_turned = count_faces();

    // if the card has not been removed.
    if(monitor == 2)
    {
        if (gEasyCards[y][x].state != REMOVED)
        {
            // Changing the state of the card chosen from face down to face up.
            // and returning the suit of the card chosen.
            if (cards_turned<2)
            {
                gEasyCards[y][x].state=FACE_UP;
                suit = gEasyCards[y][x].suits;
                return suit;
            }
            // i want a maximum of two cards to be turned at once so if
            // its going to exceed two return a random nonsense suit.
            if (cards_turned>=2)
            {
                suit = 50;
            return suit;
            }
        }
    }
    if(monitor == 3)
    {
        if (gMediumCards[y][x].state != REMOVED)
        {
            // Changing the state of the card chosen from face down to face up.
            // and returning the suit of the card chosen.
            if (cards_turned<2)
            {
                gMediumCards[y][x].state=FACE_UP;
                suit = gMediumCards[y][x].suits;
                return suit;
            }
            // i want a maximum of two cards to be turned at once so if
            // its going to exceed two return a random nonsense suit.
            if (cards_turned>=2)
            {
                suit = 50;
            return suit;
            }
        }
    }
    if(monitor == 4)
    {
        if (gHardCards[y][x].state != REMOVED)
        {
            // Changing the state of the card chosen from face down to face up.
            // and returning the suit of the card chosen.
            if (cards_turned<2)
            {
                gHardCards[y][x].state=FACE_UP;
                suit = gHardCards[y][x].suits;
                return suit;
            }
            // i want a maximum of two cards to be turned at once so if
            // its going to exceed two return a random nonsense suit.
            if (cards_turned>=2)
            {
                suit = 50;
            return suit;
            }
        }
    }
    else return 50; // just in case the user clicks outside the designated area.
}

 // when two cards are facing up will check if they have the same suit.
bool is_match()
{
    int suit1 = -6; // giving random initial values to the suits
    int suit2 = -8;
    int x1,y1; // x and y location of first card facing up.
    int x2,y2; // x and y location of second card facing up.
    int counter=0; // counts the amount of cards facing up.

    // to know if card are facing up i have to check card_state[][].
    if(monitor == 2)
    {
        for (int i=0; i< 2; i++)
        {
            // only a maximum of two cards will be facing up.
            // so when counter reaches two no need to continue the search.
            if (counter==2)
            {
                break;
            }
            for (int j=0; j<4; j++)
            {
                if (gEasyCards[i][j].state == FACE_UP)
                {
                    counter++;
                    if (counter == 1)
                    {
                        suit1 = gEasyCards[i][j].suits;
                        x1 =j;
                        y1 =i;
                    }
                    // only a maximum of two cards will be facing up.
                    // so when counter reaches two no need to continue the search.
                    if (counter==2)
                    {
                        suit2 = gEasyCards[i][j].suits;
                        x2=j;
                        y2=i;
                        //flipped += 2;
                        break;
                    }
                }
            }
        }

        // if the suits match set their state to REMOVED.
        if (counter == 2)
        {
            if (suit1==suit2)
            {
                leave ++;
                gEasyCards[y1][x1].state=REMOVED;
                gEasyCards[y2][x2].state=REMOVED;
                //SDL_Delay(300);
                Mix_PlayChannel( 1, gCorrect, 0 );
                return true;
            }
            // if the don't match set their state to FACE_DOWN.
            else
            {
                wrongs ++;
                gEasyCards[y1][x1].state=FACE_DOWN;
                gEasyCards[y2][x2].state=FACE_DOWN;
                return false;
             }
        }
    }
    if(monitor == 3)
    {
        for (int i=0; i< 4; i++)
        {
            // only a maximum of two cards will be facing up.
            // so when counter reaches two no need to continue the search.
            if (counter==2)
            {
                break;
            }
            for (int j=0; j<6; j++)
            {
                if (gMediumCards[i][j].state == FACE_UP)
                {
                    counter++;

                    if (counter == 1)
                    {
                        suit1 = gMediumCards[i][j].suits;
                        x1 =j;
                        y1 =i;
                    }
                    // only a maximum of two cards will be facing up.
                    // so when counter reaches two no need to continue the search.
                    if (counter==2)
                    {
                        suit2 = gMediumCards[i][j].suits;
                        x2=j;
                        y2=i;
                        //flipped += 2;
                        break;
                    }
                }
            }
        }

        // if the suits match set their state to REMOVED.
        if (counter == 2)
        {
            if (suit1==suit2)
            {
                leave ++;
                gMediumCards[y1][x1].state=REMOVED;
                gMediumCards[y2][x2].state=REMOVED;
                //SDL_Delay(300);
                Mix_PlayChannel( 1, gCorrect, 0 );
                return true;
            }
            // if the don't match set their state to FACE_DOWN.
            else
            {
                wrongs ++;
                gMediumCards[y1][x1].state=FACE_DOWN;
                gMediumCards[y2][x2].state=FACE_DOWN;
                return false;
            }

        }
    }
    if(monitor == 4)
    {
        for (int i=0; i< 4; i++)
        {
            // only a maximum of two cards will be facing up.
            // so when counter reaches two no need to continue the search.
            if (counter==2)
            {
                break;
            }
            for (int j=0; j<9; j++)
            {
                if (gHardCards[i][j].state == FACE_UP)
                {
                    counter++;

                    if (counter == 1)
                    {
                        suit1 = gHardCards[i][j].suits;
                        x1 =j;
                        y1 =i;
                    }
                    // only a maximum of two cards will be facing up.
                    // so when counter reaches two no need to continue the search.
                    if (counter==2)
                    {
                        suit2 = gHardCards[i][j].suits;
                        x2=j;
                        y2=i;
                        //flipped += 2;
                        break;
                    }
                }
            }
        }

        // if the suits match set their state to REMOVED.
        if (counter == 2)
        {
            if (suit1==suit2)
            {
                leave ++;
                gHardCards[y1][x1].state=REMOVED;
                gHardCards[y2][x2].state=REMOVED;
                //SDL_Delay(300);
                Mix_PlayChannel( 1, gCorrect, 0 );
                return true;
            }
            // if the don't match set their state to FACE_DOWN.
            else
            {
                wrongs ++;
                gHardCards[y1][x1].state=FACE_DOWN;
                gHardCards[y2][x2].state=FACE_DOWN;
                return false;
            }

        }
    }
    // if counter does not equal two meaning two card are not turned
    // the suits don't match so return false.
    else
        return false;
}

 // this is where all the drawing happens.
void draw_update(SDL_Event e)
 {
    int suit;
    int y = get_arrY(&e);
    int x = get_arrX(&e);
    suit = find_card_suit(e);

    if(monitor == 2)
    {
        if (suit == CARD1)
        {
            gEasyCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card1_level1.png");
        }
        if (suit == CARD2)
        {
            gEasyCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card2_level1.png");
        }
        if (suit == CARD3)
        {
            gEasyCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card3_level1.png");
        }
        if (suit == CARD4)
        {
            gEasyCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card4_level1.png");
        }
    }
    if(monitor == 3)
    {
        if (suit == CARD5)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card5_level2.png");
        }
        if (suit == CARD6)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card6_level2.png");
        }
        if (suit == CARD7)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card7_level2.png");
        }
        if (suit == CARD8)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card8_level2.png");
        }
        if (suit == CARD9)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card9_level2.png");
        }
        if (suit == CARD10)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card10_level2.png");
        }
        if (suit == CARD11)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card11_level2.png");
        }
        if (suit == CARD12)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card12_level2.png");
        }
        if (suit == CARD13)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card13_level2.png");
        }
        if (suit == CARD14)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card14_level2.png");
        }
        if (suit == CARD15)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card15_level2.png");
        }
        if (suit == CARD16)
        {
            gMediumCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card16_level2.png");
        }
    }

    if(monitor == 4)
    {
        if (suit == CARD1)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card1_level2.png");
        }
        if (suit == CARD2)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card2_level2.png");
        }
        if (suit == CARD3)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card3_level2.png");
        }
        if (suit == CARD4)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card4_level2.png");
        }
        if (suit == CARD5)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card5_level2.png");
        }
        if (suit == CARD6)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card6_level2.png");
        }
        if (suit == CARD7)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card7_level2.png");
        }
        if (suit == CARD8)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card8_level2.png");
        }
        if (suit == CARD9)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card9_level2.png");
        }
        if (suit == CARD10)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card10_level2.png");
        }
        if (suit == CARD11)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card11_level2.png");
        }
        if (suit == CARD12)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card12_level2.png");
        }
        if (suit == CARD13)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card13_level2.png");
        }
        if (suit == CARD14)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card14_level2.png");
        }
        if (suit == CARD15)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card15_level2.png");
        }
        if (suit == CARD16)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card16_level2.png");
        }
        if (suit == CARD17)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card17_level2.png");
        }
        if (suit == CARD18)
        {
            gHardCards[y][x].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/card18_level2.png");
        }
    }


    //SDL_Delay(200);// waits 200 ms before drawing again. this is need to show
 }

void check (SDL_Event* e)
{
    if(monitor == 2)
    {
        if (is_match()==true)
        {
            for (int i=0; i< 2; i++)
            {
                for (int j=0; j<4; j++)
                {
                    if (gEasyCards[i][j].state == REMOVED)
                    {
                        SDL_RenderPresent( gRenderer );
                    }
                }
            }
        }
    }
    if(monitor == 3)
    {
        if (is_match()==true)
        {
            for (int i=0; i< 4; i++)
            {
                for (int j=0; j<6; j++)
                {
                    if (gMediumCards[i][j].state == REMOVED)
                    {
                        //draw_update(*e);
                        SDL_RenderPresent( gRenderer );
                    }
                }
            }
        }
    }
    if(monitor == 4)
    {
        if (is_match()==true)
        {
            for (int i=0; i< 4; i++)
            {
                for (int j=0; j<9; j++)
                {
                    if (gHardCards[i][j].state == REMOVED)
                    {
                        //draw_update(*e);
                        SDL_RenderPresent( gRenderer );
                    }
                }
            }
        }
    }
}

void un_match(int round)
{
    if(round == 2)
    {
        if(is_match()==false)
        {
            for (int i=0; i< 2; i++)
            {
                for (int j=0; j<4; j++)
                {
                    if (gEasyCards[i][j].state == FACE_DOWN)
                    {
                        gEasyCards[i][j].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level1.png");
                    }
                }
            }
        }
    }
    if(round == 3)
    {
        if(is_match()== false)
        {
            for (int i=0; i< 4; i++)
            {
                for (int j=0; j<6; j++)
                {
                    if (gMediumCards[i][j].state==FACE_DOWN)
                    {
                        gMediumCards[i][j].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level2.png");
                    }
                }
            }
        }
    }
    if(round == 4)
    {
        if(is_match()==false)
        {
            for (int i=0; i< 4; i++)
            {
                for (int j=0; j<9; j++)
                {
                    if (gHardCards[i][j].state==FACE_DOWN)
                    {
                        gHardCards[i][j].loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_cards_level2.png");
                    }
                }
            }
        }
    }
}

void mix_cards(int round)
{
    int holder;
    switch(round)
    {
    case 0 :
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%4;
            int y0 = rand()%2;
            int x1 = rand()%4;
            int y1 = rand()%2;

            holder = card_suit_level1[y0][x0];
            card_suit_level1[y0][x0] = card_suit_level1[y1][x1];
            card_suit_level1[y1][x1] = holder;
        }
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%6;
            int y0 = rand()%4;
            int x1 = rand()%6;
            int y1 = rand()%4;

            holder = card_suit_level2[y0][x0];
            card_suit_level2[y0][x0] = card_suit_level2[y1][x1];
            card_suit_level2[y1][x1] = holder;
        }
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%9;
            int y0 = rand()%4;
            int x1 = rand()%9;
            int y1 = rand()%4;

            holder = card_suit_level3[y0][x0];
            card_suit_level3[y0][x0] = card_suit_level3[y1][x1];
            card_suit_level3[y1][x1] = holder;
        }
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                gEasyCards[i][j].suits=card_suit_level1[i][j];
        }
        cout << "Easy : " << endl;
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                cout << gEasyCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                gEasyCards[i][j].state=card_state_level1[i][j];
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                gMediumCards[i][j].suits=card_suit_level2[i][j];
        }
        cout << "Medium : " << endl;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                cout << gMediumCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                gMediumCards[i][j].state=card_state_level2[i][j];
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                gHardCards[i][j].suits=card_suit_level3[i][j];
        }
        cout << "Hard : " << endl;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                cout << gHardCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                gHardCards[i][j].state=card_state_level3[i][j];
        }
        break;
    case 2:
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%4;
            int y0 = rand()%2;
            int x1 = rand()%4;
            int y1 = rand()%2;

            holder = card_suit_level1[y0][x0];
            card_suit_level1[y0][x0] = card_suit_level1[y1][x1];
            card_suit_level1[y1][x1] = holder;
        }
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                gEasyCards[i][j].suits=card_suit_level1[i][j];
        }
        cout << "Easy : " << endl;
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                cout << gEasyCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<2; i++)
        {
            for (int j=0; j<4; j++)
                gEasyCards[i][j].state=card_state_level1[i][j];
        }
        break;
    case 3:
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%6;
            int y0 = rand()%4;
            int x1 = rand()%6;
            int y1 = rand()%4;

            holder = card_suit_level2[y0][x0];
            card_suit_level2[y0][x0] = card_suit_level2[y1][x1];
            card_suit_level2[y1][x1] = holder;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                gMediumCards[i][j].suits=card_suit_level2[i][j];
        }
        cout << "Medium : " << endl;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                cout << gMediumCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<6; j++)
                gMediumCards[i][j].state=card_state_level2[i][j];
        }
        break;
    case 4:
        for (int i=0; i<20; i++)
        {
            int x0 = rand()%9;
            int y0 = rand()%4;
            int x1 = rand()%9;
            int y1 = rand()%4;

            holder = card_suit_level3[y0][x0];
            card_suit_level3[y0][x0] = card_suit_level3[y1][x1];
            card_suit_level3[y1][x1] = holder;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                gHardCards[i][j].suits=card_suit_level3[i][j];
        }
        cout << "Hard : " << endl;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                cout << gHardCards[i][j].suits << ' ';
            cout << endl;
        }
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<9; j++)
                gHardCards[i][j].state=card_state_level3[i][j];
        }
        break;
    }

}

void mouse(SDL_Event e,int i, int j)
{
    //If mouse event happened
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

        if(monitor == 2)
        {
            //Mouse is left of the button
		if( x < gEasyLevel.w*(j)+54+80*j )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > gEasyLevel.w*(j+1)+54+80*j )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < gEasyLevel.h*i + 90 )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > gEasyLevel.h*(i+1) + 90 )
		{
			inside = false;
		}
		//Mouse is outside button
		if( !inside )
		{

		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel( 0, gFlip, 0 );
                    clicked ++;
                    draw_update(e);
                    if(clicked >= 3)
                    {
                        check(&e);
                        SDL_Delay(300);
                        un_match(monitor);
                        clicked = 0;
                    }
                    /*cout << "clicked :" << clicked << endl;
                    cout << "flipped :" << flipped << endl;
                    cout << "wrongs :" << wrongs << endl;
                    cout << leave << endl;*/
                }
		}
        }
        if(monitor == 3)
        {
            //Mouse is left of the button
		if( x < gMediumLevel.w*(j)+75+80*j )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > gMediumLevel.w*(j+1)+75+80*j )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < gMediumLevel.h*i + 90 +15*i)
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > gMediumLevel.h*(i+1) + 90 +15*i)
		{
			inside = false;
		}
		//Mouse is outside button
		if( !inside )
		{

		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel( 0, gFlip, 0 );
                    clicked ++;
                    draw_update(e);
                    if(clicked >= 3)
                    {
                        check(&e);
                        SDL_Delay(300);
                        un_match(monitor);
                        clicked = 0;
                    }
                    //cout << "card state :" << gMediumCards[i][j].state << endl;
                    //cout << "clicked :" << clicked << endl;
                }
		}
        }
        if(monitor == 4)
        {
            //Mouse is left of the button
		if( x < gHardLevel.w*(j)+35+20*j )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > gHardLevel.w*(j+1)+35+20*j )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < gHardLevel.h*i + 90 +10*i)
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > gHardLevel.h*(i+1) + 90 +10*i)
		{
			inside = false;
		}
		//Mouse is outside button
		if( !inside )
		{

		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
                if(e.type==SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel( 0, gFlip, 0 );
                    clicked ++;
                    draw_update(e);
                    if(clicked >= 3)
                    {
                        check(&e);
                        SDL_Delay(300);
                        un_match(monitor);
                        clicked = 0;
                    }
                    //cout << "clicked :" << clicked << endl;
                }
		}
        }
	}
}

void LButton::handlePlayButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
				case SDL_MOUSEBUTTONUP :
                    play ++;
                    break;
			}
		}
	}
}

void LButton::handleReplayButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
				case SDL_MOUSEBUTTONUP:
                    mix_cards(last_played);
                    wrongs = 0;
                    leave = 0;
                    monitor = last_played;
                    un_match(last_played);
                    SDL_RenderClear(gRenderer);
                    break;
			}
		}
	}
}

void LButton::handleHelpButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
				case SDL_MOUSEBUTTONDOWN:
				    help++;
                    break;
			}
		}
	}
}

void LButton::handleBackButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH/3 )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT/3 )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
				case SDL_MOUSEBUTTONDOWN:
				    back_time ++;
				    leave = 0;
				    wrongs = 0;
				    if(monitor == 2 || monitor == 3 || monitor == 4)
                    {
                        mix_cards(last_played);
                        un_match(last_played);
                    }
                    break;
			}
		}
	}
}

void LButton::handleMenuButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
				case SDL_MOUSEBUTTONUP:
				    play = 0;
                    help = 0;
                    back_time = 0;
                    monitor = 0;
				    wrongs = 0;
                    leave = 0;
                    mix_cards(last_played);
                    un_match(last_played);
                    break;
			}
		}
	}
}

void LButton::handleEasyButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + 405/2 )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + 75 )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    monitor = 2;
                    break;
			}
		}
	}
}

void LButton::handleMediumButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + 405/2 )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + 75 )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    monitor = 3;
                    break;
			}
		}
	}
}

void LButton::handleHardButton( SDL_Event* e)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + 405/2 )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + 75 )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                    mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    monitor = 4;
                    break;
			}
		}
	}
}

void Menu(SDL_Event e)
{
    menu_bg.render(0,0,NULL);

    //Render buttons
    if(play==0&&help==0)
    {
        gButtons[ PLAY_BUTTONS ].render( PLAY_BUTTONS, gPlaySprite);
        gButtons[ HELP_BUTTONS ].render( HELP_BUTTONS, gHelpSprite);
        gButtons[ PLAY_BUTTONS ].handlePlayButton(&e);
        gButtons[ HELP_BUTTONS ].handleHelpButton(&e);
    }
    else if(help!=0)
    {
        SDL_RenderClear( gRenderer );
        instruction[0].render(0,0,NULL);
        instruction[1].render(313,200,&gHelpSprite[2]);
        instruction[2].render(613,200,&gHelpSprite[3]);
        gButtons[ BACK_BUTTONS ].render( BACK_BUTTONS , gBackSprite );
        gButtons[ BACK_BUTTONS ].handleBackButton(&e);
        if(back_time!=0)
        {
             back_time=0;
             play = 0;
             help = 0;
             Menu(e);
        }
    }
    else
        monitor = 1;
}

void GamePlay(SDL_Event* e)
{
    SDL_RenderClear(gRenderer);

    back_ground.render(0,0,NULL);

    //In memory text stream
    std::stringstream triesText;

    //Set text color as black
    SDL_Color textColor = { 255, 255, 255, 255 };

    if(monitor == 2)
    {
        pairs = 4;
        last_played = monitor;
        //Set text to be rendered
        triesText.str( "" );
        triesText << "TRIES " << wrongs << " /7 ";

        //Render text
        if( !Tries.loadFromRenderedText( triesText.str().c_str(), textColor ) )
        {
            printf( "Unable to render tries texture!\n" );
        }
        gButtons[ BACK_BUTTONS ].render( BACK_BUTTONS, gBackSprite );
        gButtons[ BACK_BUTTONS ].handleBackButton(e);
        if(back_time!=0)
        {
            back_time=0;
            play = 0;
            help = 0;
            monitor = 0;
            Menu(*e);
        }

        //Render cards sprite
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<4;j++)
            {
                gEasyCards[i][j].render( 54 + j*(gEasyLevel.w + 80), gEasyLevel.h*i + 50*i +90, &gEasyLevel );
            }
        }

        for(int i=0;i<2;i++)
        {
            for(int j=0;j<4;j++)
            {
                mouse(*e,i,j);
            }
        }
        //Render attemps
        Tries.render( ( SCREEN_WIDTH - Tries.getWidth() ) / 2, 0 );

        if(wrongs < 7 && leave == pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gWin, 0 );
            monitor = 5;
        }
        if(wrongs == 7 && leave != pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gLose, 0 );
            monitor = 6;
        }
        }
    if(monitor == 3)
    {
        pairs = 12;
        last_played = monitor;
        //Set text to be rendered
        triesText.str( "" );
        triesText << "TRIES " << wrongs << " /18 ";

        //Render text
        if( !Tries.loadFromRenderedText( triesText.str().c_str(), textColor ) )
        {
            printf( "Unable to render tries texture!\n" );
        }
        gButtons[ BACK_BUTTONS ].render( BACK_BUTTONS, gBackSprite );
        gButtons[ BACK_BUTTONS ].handleBackButton(e);
        if(back_time!=0)
        {
            back_time=0;
            play = 0;
            help = 0;
            monitor = 0;
            Menu(*e);
        }

        //Render cards sprite
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<6;j++)
            {
                gMediumCards[i][j].render( 75 + j*(gMediumLevel.w + 80), gMediumLevel.h*i+90+15*i, &gMediumLevel );
            }
        }
        //un_match();
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<6;j++)
            {
                mouse(*e,i,j);
            }
        }
        //Render attemps
        Tries.render( ( SCREEN_WIDTH - Tries.getWidth() ) / 2, 0 );

        if(wrongs < 18 && leave == pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gWin, 0 );
            monitor = 5;
        }
        if(wrongs == 18 && leave != pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gLose, 0 );
            monitor = 6;
        }
    }
    if(monitor == 4)
    {
        pairs = 18;
        last_played = monitor;
        //Set text to be rendered
        triesText.str( "" );
        triesText << "TRIES " << wrongs << " /18 ";

        //Render text
        if( !Tries.loadFromRenderedText( triesText.str().c_str(), textColor ) )
        {
            printf( "Unable to render tries texture!\n" );
        }
        gButtons[ BACK_BUTTONS ].render( BACK_BUTTONS, gBackSprite );
        gButtons[ BACK_BUTTONS ].handleBackButton(e);
        if(back_time!=0)
        {
            back_time=0;
            play = 0;
            help = 0;
            monitor = 0;
            Menu(*e);
        }

        //Render cards sprite
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<9;j++)
            {
                gHardCards[i][j].render( 35 + j*(gHardLevel.w + 20), gHardLevel.h*i+90+10*i, &gHardLevel );
            }
        }
        //un_match();
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<9;j++)
            {
                mouse(*e,i,j);
            }
        }
        //Render attemps
        Tries.render( ( SCREEN_WIDTH - Tries.getWidth() ) / 2, 0 );

        if(wrongs < 18 && leave == pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gWin, 0 );
            monitor = 5;
        }
        if(wrongs == 18 && leave != pairs)
        {
            SDL_Delay(1000);
            SDL_RenderClear(gRenderer);
            Mix_PlayChannel( -1, gLose, 0 );
            monitor = 6;
        }
    }
}

void menuScreen(SDL_Event e)
{
    SDL_RenderClear(gRenderer);
    menu_bg.render(0,0,NULL);
    gButtons[ BACK_BUTTONS ].render( BACK_BUTTONS, gBackSprite );
    gButtons[ EASY_BUTTONS ].render( EASY_BUTTONS, gLevelSprite );
    gButtons[ MEDIUM_BUTTONS ].render( MEDIUM_BUTTONS, gLevelSprite );
    gButtons[ HARD_BUTTONS ].render( HARD_BUTTONS, gLevelSprite );
    gButtons[ BACK_BUTTONS ].handleBackButton(&e);
    gButtons[ EASY_BUTTONS ].handleEasyButton(&e);
    gButtons[ MEDIUM_BUTTONS ].handleMediumButton(&e);
    gButtons[ HARD_BUTTONS ].handleHardButton(&e);

    if(back_time!=0)
    {
        monitor = 0;
        back_time=0;
        play = 0;
        help = 0;
        Menu(e);
    }
}

void winScreen(SDL_Event e)
{
    SDL_RenderClear(gRenderer);
    win_back_ground.render(0,0,NULL);
    you_wins.render(100,0,NULL);
    gButtons[ REPLAY_BUTTONS ].setPosition( SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 );
    gButtons[ MENU_BUTTONS ].setPosition( SCREEN_WIDTH/2 - BUTTON_WIDTH/2, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 + 200);
    gButtons[ REPLAY_BUTTONS ].render( REPLAY_BUTTONS , gReplaySprite);
    gButtons[ REPLAY_BUTTONS ].handleReplayButton(&e);
    gButtons[ MENU_BUTTONS ].render( MENU_BUTTONS , gMenuSprite);
    gButtons[ MENU_BUTTONS ].handleMenuButton(&e);
}

void loseScreen (SDL_Event e)
{
    SDL_RenderClear(gRenderer);
    lose_back_ground.render(0,0,NULL);
    game_over.render(160,0,NULL);
    gButtons[ REPLAY_BUTTONS ].setPosition( 290, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 );
    gButtons[ MENU_BUTTONS ].setPosition( 290, SCREEN_HEIGHT/2 - BUTTON_HEIGHT/2 + 200);
    gButtons[ REPLAY_BUTTONS ].render( REPLAY_BUTTONS , gReplaySprite);
    gButtons[ REPLAY_BUTTONS ].handleReplayButton(&e);
    gButtons[ MENU_BUTTONS ].render( MENU_BUTTONS , gMenuSprite);
    gButtons[ MENU_BUTTONS ].handleMenuButton(&e);
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
