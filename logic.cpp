#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "LTexture.h"
#include "sdl.h"
#include "LButtons.h"
#include "logic.h"

using namespace std;

extern int card_suit_level1[2][4] ;

extern int card_state_level1[2][4] ;

extern int card_suit_level2[4][6] ;

extern int card_state_level2[4][6] ;

extern int card_suit_level3[4][9];

extern int card_state_level3[4][9] ;

extern int play ;

extern int help ;

extern int back_time ;

extern int monitor ;

extern int clicked ;

extern int wrongs ;

extern int leave ;

extern int pairs ;

extern int last_played ;

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
