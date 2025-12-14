#include <SDL/SDL.h>
#include <time.h>

//General functions

SDL_bool CheckCollision(SDL_Rect A, SDL_Rect B)
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    // Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) { return SDL_FALSE; }
    if (topA >= bottomB) { return SDL_FALSE; }
    if (rightA <= leftB) { return SDL_FALSE; }
    if (leftA >= rightB) { return SDL_FALSE; }

    // If none of the sides from A are outside B
    return SDL_TRUE;
}

 int SetRect(SDL_Rect* A, int x, int y, int w, int h){
	A->x = x;
	A->y = y;
	A->w = w;
	A->h = h;
	return 0;
}

//Uses SetRect() to put Rect A into Rect B
void CloneRect(SDL_Rect* A,SDL_Rect* B){
	SetRect(B,A->x,A->y,A->w,A->h);
} 

int Timeout(){
	int num = (rand()%40);
	num -=1;
	/*
	if(time(NULL) > (time(NULL) +num)){
		return 1;
	}
	* */
	if(0 >= num){
		return 1;
	}
	return 0;
}

/*#################################
  ##							   #
  ##	ENEMY OBJECT CODE :'(	    #
  ##							  	#
  ###################################
*/

SDL_Rect clone;
SDL_Rect clone1;
SDL_Rect clone2;
SDL_Rect clone3;
SDL_Rect clone4;
SDL_Rect clone5;
SDL_Rect clone6;
SDL_Rect clone7;
SDL_Rect clone8;
SDL_Rect clone9;
SDL_Rect clone10;

int Attack(SDL_Rect* B, SDL_Surface* scr){
	B->w = 4;
	B->h = 8;
	
	SDL_FillRect(scr, B, SDL_MapRGB(scr->format, 20, 210, 200));

	if(B->y < 232){
		B->y += 2;
		SDL_FillRect(scr, B, SDL_MapRGB(scr->format, 20, 210, 200));
		return 0;
	}
	return 1;
}

//Rect A is enemy. B is bullet. sprite is sprite.
int MoveEnemy(SDL_Rect* A,SDL_Surface* sprite, SDL_Surface* scr, SDL_Rect* proj){
	if(Timeout()){
		int xdir = (rand()%50);
		int pol = (rand()%3);
		pol -=1;
		
		if(A->x < (320 - A->w)){
			A->x += (xdir * pol);
		}
		SDL_BlitSurface(sprite, NULL, scr, A);
		return 1;
	}

	SDL_BlitSurface(sprite, NULL, scr, A);
	return 0;
}
