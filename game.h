#include <SDL/SDL.h>
#include <time.h>

#define SCREENW 320
#define SCREENH 240

//General functions
int CheckCollision(SDL_Rect A, SDL_Rect B)
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
    if (bottomA <= topB) { return 0; }
    if (topA >= bottomB) { return 0; }
    if (rightA <= leftB) { return 0; }
    if (leftA >= rightB) { return 0; }

    // If none of the sides from A are outside B
    return 1;
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

//
// Entites
//

typedef struct ship_s{
	SDL_Rect r;
	SDL_Rect b;
	int xvel, yvel;
	int vis;
	char* name[48];
} ship_t;

typedef struct ball_s{
	SDL_Rect r;
	int bx, by;
	char name[48];
} ball_t;

//
// end of Entites
//

int Attack(ship_t* B, SDL_Surface* scr){
	B->b.w = 4;
	B->b.h = 8;
	
	//SDL_FillRect(scr,&B->r, SDL_MapRGB(scr->format, 20, 210, 200));

	if(B->b.y < 232){
		B->b.y += 2;
		SDL_FillRect(scr, &B->b, SDL_MapRGB(scr->format, 20, 210, 200));
		return 0;
	}
	return 1;
}

//Rect A is enemy. B is bullet. sprite is sprite.
int MoveShip(ship_t* A,SDL_Surface* sprite, SDL_Surface* scr){
	if(Timeout()){
		int xdir = (rand()%50);
		int pol = (rand()%3);
		pol -=1;
		
		if(A->r.x < (320 - A->r.w)){
			A->r.x += (xdir * pol);
		}
		SDL_BlitSurface(sprite, NULL, scr, &A->r);
		return 1;
	}

	SDL_BlitSurface(sprite, NULL, scr, &A->r);
	return 0;
}

int MoveBullet(ship_t* B){
		B->b.x = (B->r.x + 16);
		B->b.y = (B->r.y + 16);
	}

void BallBounce(ball_t *P){
	if(P->r.x < (SCREENW-32) && P->r.x > (0)){
	 	P->r.x += P->bx;
	}
	else{
		P->bx = (P->bx * -1);
		P->r.x += P->bx;		
	}	
	if(P->r.y < (SCREENH-32) && P->r.y > (0)){
		P->r.y += P->by;
	}
	else{
		P->by = (P->by * -1);
		P->r.y += P->by;
		//printf("\nx:%d", P->r.x);
	}
}

void ShipSet(ship_t* A, int type){
	if(type == 0){
		A->r.x = 0; A->r.y = 0; A->r.w = 32; A->r.h = 32;
		A->b.x = 0; A->b.y = 0; A->b.w = 4; A->b.h = 8;
		A->vis = 1;
    }
    else{
		A->r.x = 10; A->r.y = 208; A->r.w = 32; A->r.h = 32;
		A->b.x = 10; A->b.y = 208; A->b.w = 4; A->b.h = 8;
		A->xvel = 0; A->yvel = 0; A->vis = 1;
	}
}

int EnemyHandle(ship_t* pl, ship_t* en, SDL_Surface* scr, SDL_Surface* sprite){
	if(!CheckCollision(en->r, pl->b) && en->vis){
			MoveShip(en, sprite, scr);
		
			if(Attack(en, scr)){
				MoveBullet(en);
			}
	}
	else{ en->vis = 0; }
}	
