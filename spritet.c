#include "game.h"

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_WM_SetCaption("Ailen Attack", "Ailen Attack");
	
	SDL_Surface* screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE);;
	
	sprite_t *being;
	being = malloc(sizeof(sprite_t));

	SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	SDL_Delay(4000);
	
	return 0;
}
