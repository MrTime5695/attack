#include "game.h"




int main(int argc, int** argv){
	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Clone Test", "Clone Test");
	SDL_Surface* screen = SDL_SetVideoMode(SCREENW, SCREENH, 16, SDL_HWSURFACE);
	
	SDL_Rect bg;
	SetRect(&bg, 0,0,SCREENW,SCREENH);
	//SetRect(&guy, 0,0,32,32);
	//CloneRect(&guy, &clone);
	
	
	SDL_Event event;
	int run = 1;
	
	ball_t ball1;
	ball1.r.x = 0;
	ball1.r.y = 0;
	ball1.r.w = 32;
	ball1.r.h = 32;
	ball1.bx = 5;
	ball1.by = 5;

	ball_t ball2;
	ball2.r.x = 230;
	ball2.r.y = 40;
	ball2.r.w = 32;
	ball2.r.h = 32;
	ball2.bx = 5;
	ball2.by = -5;
	while(run){
			
			while( SDL_PollEvent( &event )){
				 switch( event.type ){
					case SDL_KEYDOWN:
						switch( event.key.keysym.sym ){
							case SDLK_RETURN:
								run = 0;
								break;
						}
				}
			}
			//draw bg
			BallBounce(&ball1);
			BallBounce(&ball2);
	
			SDL_FillRect(screen, &bg, SDL_MapRGB(screen->format, 100, 110, 150));
			SDL_FillRect(screen, &ball2.r, SDL_MapRGB(screen->format, 200, 40, 150));
			SDL_FillRect(screen, &ball1.r, SDL_MapRGB(screen->format, 0, 40, 255));
			//MoveRect(&guy, screen);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(1000/60);
		
	}
	return 0;
}

