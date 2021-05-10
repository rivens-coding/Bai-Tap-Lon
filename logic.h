#ifndef LOGIC__H
#define LOGIC__H

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

int get_arrY(SDL_Event* e);
int get_arrX(SDL_Event* e);
int count_faces();
int find_card_suit(SDL_Event e);
bool is_match();
void draw_update(SDL_Event e);
void check (SDL_Event* e);
void un_match(int round);
void mix_cards(int round);
void mouse(SDL_Event e,int i, int j);
void Menu(SDL_Event e);
void GamePlay(SDL_Event* e);
void menuScreen(SDL_Event e);
void winScreen(SDL_Event e);
void loseScreen(SDL_Event e);

#endif // LOGIC__H
