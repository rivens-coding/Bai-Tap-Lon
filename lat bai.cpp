#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL );

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

//Walking animation
const int WALKING_ANIMATION_FRAMES = 16;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
LTexture gSpriteSheetTexture;


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

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
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
	if( !gSpriteSheetTexture.loadFromFile( "C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/back_of_the_card.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		//Set top left sprite
		gSpriteClips[ 0 ].x = 0;
		gSpriteClips[ 0 ].y = 0;
		gSpriteClips[ 0 ].w = 248;
		gSpriteClips[ 0 ].h = 350;

        gSpriteClips[ 1 ].x = 0;
		gSpriteClips[ 1 ].y = 0;
		gSpriteClips[ 1 ].w = 248-31;
		gSpriteClips[ 1 ].h = 350;

		gSpriteClips[ 2 ].x = 0;
		gSpriteClips[ 2 ].y = 0;
		gSpriteClips[ 2 ].w = 248-31*2;
		gSpriteClips[ 2 ].h = 350;

        //Set top right sprite
		gSpriteClips[ 3 ].x = 0;
		gSpriteClips[ 3 ].y = 0;
		gSpriteClips[ 3 ].w = 248-31*3;
		gSpriteClips[ 3 ].h = 350;

        //Set bottom left sprite
		gSpriteClips[ 4 ].x = 0;
		gSpriteClips[ 4 ].y = 0;
		gSpriteClips[ 4 ].w = 248-31*4;
		gSpriteClips[ 4 ].h = 350;

		gSpriteClips[ 5 ].x = 0;
		gSpriteClips[ 5 ].y = 0;
		gSpriteClips[ 5 ].w = 248-31*5;
		gSpriteClips[ 5 ].h = 350;

		gSpriteClips[ 6 ].x = 0;
		gSpriteClips[ 6 ].y = 0;
		gSpriteClips[ 6 ].w = 248-31*6;
		gSpriteClips[ 6 ].h = 350;

		//Set bottom right sprite
		gSpriteClips[ 7 ].x = 0;
		gSpriteClips[ 7 ].y = 0;
		gSpriteClips[ 7 ].w = 248-31*7;
		gSpriteClips[ 7 ].h = 350;

        gSpriteClips[ 8 ].x = 0;
		gSpriteClips[ 8 ].y = 0;
		gSpriteClips[ 8 ].w = 248-31*7;
		gSpriteClips[ 8 ].h = 350;

		gSpriteClips[ 9 ].x = 0;
		gSpriteClips[ 9 ].y = 0;
		gSpriteClips[ 9 ].w = 248-31*6;
		gSpriteClips[ 9 ].h = 350;

		gSpriteClips[ 10 ].x = 0;
		gSpriteClips[ 10 ].y = 0;
		gSpriteClips[ 10 ].w = 248-31*5;
		gSpriteClips[ 10 ].h = 350;

		gSpriteClips[ 11 ].x = 0;
		gSpriteClips[ 11 ].y = 0;
		gSpriteClips[ 11 ].w = 248-31*4;
		gSpriteClips[ 11 ].h = 350;

		gSpriteClips[ 12 ].x = 0;
		gSpriteClips[ 12 ].y = 0;
		gSpriteClips[ 12 ].w = 248-31*3;
		gSpriteClips[ 12 ].h = 350;

		gSpriteClips[ 13 ].x = 0;
		gSpriteClips[ 13 ].y = 0;
		gSpriteClips[ 13 ].w = 248-31*2;
		gSpriteClips[ 13 ].h = 350;

		gSpriteClips[ 14 ].x = 0;
		gSpriteClips[ 14 ].y = 0;
		gSpriteClips[ 14 ].w = 248-31;
		gSpriteClips[ 14 ].h = 350;

		gSpriteClips[ 15 ].x = 0;
		gSpriteClips[ 15 ].y = 0;
		gSpriteClips[ 15 ].w = 248;
		gSpriteClips[ 15 ].h = 350;
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

			//Current animation frame
			int frame = 0;

			//While application is running
			while( frame!=16*3 )
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

				//Render current frame
				SDL_Rect* currentClip = &gSpriteClips[ frame / 3 ];
				gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Go to next frame
				frame++;

				//Cycle animation
				if( frame / 2 >= WALKING_ANIMATION_FRAMES )
				{
					gSpriteSheetTexture.free();
                    gSpriteSheetTexture.loadFromFile("C:/Users/FFMW/Dropbox/My PC (LAPTOP-5AN6CR2Q)/Desktop/tai lieu/test2.png");
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
