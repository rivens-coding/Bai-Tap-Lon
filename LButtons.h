#ifndef LBUTTONS__H
#define LBUTTONS__H

//Screen dimension constants
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

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

#endif // LBUTTONS__H
