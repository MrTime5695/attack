#include <SDL/SDL.h>

	//used to
typedef struct sprite_s{
	int x, y, w, h;
} sprite_t;

int SpriteInit(sprite_t A, int type){
	//enemy
	if(type == 0){
		A.x = 0;
		A.y = 0;
		A.w = 32;
		A.h = 32;
	}
	//player
	if(type == 1){
		A.x = 160;
		A.y = 208;
		A.w = 32;
		A.h = 32;
	}
	//bullet
	if(type == 2){
		A.x = 0;
		A.y = 240;
		A.w = 4;
		A.h = 8;
	}
	//background
	if(type == 3){
		A.x = 0;
		A.y = 0;
		A.w = 0;
		A.h = 0;
	}
	printf("rect x: %d rect y:%d\n", A.x, A.y);
	printf("rect w: %d rect h:%d\n", A.w, A.h);
	
	return 0;
}	

int spr2rect(sprite_t *A, SDL_Rect B){
		B.x = A.x;
		B.y = A.y;
		B.w = A.w;
		B.h = A.h;
		if(B.x == A.x && B.y == A.y && B.w == A.w && B.h == A.h )
			return 1;
		else{
			return 0;
		}
	}
