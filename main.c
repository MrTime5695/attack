#include "game.h"

/*
	space invaders clone written in SDL1.2
	* nov 28 2025
	* Marlow Rekers
*/

int main(int argc, char** argv){
	   
    int quit = 1;
    
    int xvel, yvel, colour;
   
    int shoot = 0; 
    int tvel = 1;
     
    SDL_Init(SDL_INIT_VIDEO);
	
	SDL_WM_SetCaption("Ailen Attack", "Ailen Attack");
	
	SDL_Surface* screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE);
    
    //define images
    SDL_Surface* bgimage = SDL_LoadBMP("bg.bmp");
	SDL_Surface* ship = SDL_LoadBMP("jointship.bmp");
    SDL_Surface* tv = SDL_LoadBMP("tv.bmp");
    
    //define position / hitbox of said images
    SDL_Rect bg;

    ship_t enemy1, player;
    ship_t en2, en3, en4, en5, en6, en7;
    
    ShipSet(&enemy1, 0);
	ShipSet(&en2, 0);
	ShipSet(&en3, 0);
	ShipSet(&en4, 0);
	ShipSet(&en5, 0);
	ShipSet(&en6, 0);
	ShipSet(&en7, 0);
	ShipSet(&player, 1);
    
    en2.r.y += 32;
	en3.r.y += 64;
	en4.r.y += 128;
	en5.r.y += 196;
    en6.r.y += 32;
    en7.r.y += 64;
    
    SetRect(&bg,0,0,320,240);

	SDL_Event event;
    
    /* Main game loop */
    /* Check for events */
    while(quit){
    while( SDL_PollEvent( &event )){
        switch( event.type ){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
						player.xvel = -4;
                        break;
                    case SDLK_RIGHT:
						player.xvel = 4;
                        break;
                    case SDLK_SPACE:
                        if(shoot == 0){
							shoot = 1;
							player.b.x = (player.r.x + (player.r.w /2));
							player.b.y = player.r.y;
						}
                        break;
                    case SDLK_a:
                        if(shoot == 0){
							shoot = 1;
							player.b.x = (player.r.x + (player.r.w /2));
							player.b.y = player.r.y;
						}
                        break;
                    case SDLK_RETURN:
						quit = 0;
						break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        if( player.xvel < 0)
                            player.xvel = 0;
                        break;
                    case SDLK_RIGHT:
                        if( player.xvel > 0 )
                            player.xvel = 0;
                        break;
                    case SDLK_UP:
                    
                        break;
                    case SDLK_DOWN:
                        
                        break;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        
        }
        
        }	
		
		if(player.r.x < (320 - player.r.w)){
			player.r.x += player.xvel;
		}
		else{
			player.r.x -= 4;
		}
		
		//draw the background
		SDL_BlitSurface(bgimage, NULL, screen, &bg);

		
		//draw the enemy
		/*
		if(CheckCollision(enemy1.b, player.r)){
			ship = SDL_LoadBMP("tvc.bmp");
		}
		*/
		
		
		
		EnemyHandle(&player, &enemy1, screen, tv);
		EnemyHandle(&player, &en2, screen, tv);
		EnemyHandle(&player, &en3, screen, tv);
		EnemyHandle(&player, &en4, screen, tv);
		EnemyHandle(&player, &en5, screen, tv);
		EnemyHandle(&player, &en6, screen, tv);
		EnemyHandle(&player, &en7, screen, tv);
		
		//draw the player
		SDL_BlitSurface(ship, NULL, screen, &player.r);
		
		if(shoot){
			if(player.b.y > 0){	
				player.b.y -= 4;
				SDL_FillRect(screen, &player.b, SDL_MapRGB(screen->format, 20, 210, 200));
			}
			else{
				shoot = 0;
				player.b.y = 233;
			}
		}
		
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		SDL_Delay(1000/60);

	}
    
    SDL_FreeSurface(ship);
    SDL_FreeSurface(tv);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(bgimage);
    SDL_Quit();
    
	return 0;
 }

