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
	
    /*
     * Colour mask doesn't work yet :'(
    Uint32 colorkey = SDL_MapRGB(screen->format, 0, 0xFF, 0xFF); // Map a turquoise color
    SDL_SetColorKey(screen, SDL_SRCCOLORKEY, colorkey); 
    */
    
    //define images
    SDL_Surface* bgimage = SDL_LoadBMP("bg.bmp");
	SDL_Surface* player = SDL_LoadBMP("jointship.bmp");
    SDL_Surface* tv = SDL_LoadBMP("tv.bmp");
    
    //define position / hitbox of said images
    SDL_Rect rect, bg, enemy, bullet, shot;
    
    
    SetRect(&rect,10,208,32,32);
    SetRect(&bg,0,0,320,240);
	SetRect(&enemy,50,10,32,32);
    SetRect(&bullet,0,230,4,8);
    clone1.x = (enemy.x + 16); clone1.y = (enemy.y + 16);
    
    CloneRect(&enemy, &clone);
    
    xvel = 0;
    yvel = 0;
    
	colour = 0;
    
    SDL_Event event;
    /* Main game loop */
    /* Check for events */
    while(quit){
    while( SDL_PollEvent( &event )){
        switch( event.type ){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
						xvel = -4;
                        break;
                    case SDLK_RIGHT:
						xvel = 4;
                        break;
                    case SDLK_SPACE:
                        if(shoot == 0){
							shoot = 1;
							bullet.x = (rect.x + (rect.w /2));
							bullet.y = rect.y;
						}
                        break;
                    case SDLK_a:
                        if(shoot == 0){
							shoot = 1;
							bullet.x = (rect.x + (rect.w /2));
							bullet.y = rect.y;
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
                        if( xvel < 0)
                            xvel = 0;
                        break;
                    case SDLK_RIGHT:
                        if( xvel > 0 )
                            xvel = 0;
                        break;
                    case SDLK_UP:
                        //if( yvel < 0 )
                        //    yvel = 0;
                        break;
                    case SDLK_DOWN:
                        //if( yvel > 0 )
                        //    yvel = 0;
                        break;
                    default:
                        break;
                }
                break;
            
            default:
                break;
        
        }
        
    }	
		if(rect.x < (320 - rect.w)){
			rect.x += xvel;
		}
		else{
			rect.x -= 4;
		}
		
		//draw the background
		SDL_BlitSurface(bgimage, NULL, screen, &bg);

		
		//draw the enemy
		if(CheckCollision(enemy, bullet)){
			tv = SDL_LoadBMP("tvc.bmp");
		}
		
		if(!CheckCollision(enemy, bullet)){
			MoveEnemy(&enemy, tv, screen, &clone1);
		
			if(Attack(&clone1, screen)){
				clone1.x = (enemy.x + 16);
				clone1.y = (enemy.y + 16);
			}
		}
		else
		{
			tv = SDL_LoadBMP("tvc.bmp");
			SDL_BlitSurface(tv, NULL, screen, &enemy);
			SDL_UpdateRect(screen, 0, 0, 0, 0);
			SDL_Delay(1000);
			SDL_Quit();
			return 0;
		}
		
		//draw the player
		SDL_BlitSurface(player, NULL, screen, &rect);
		
		if(shoot){
			if(bullet.y > 0){	
				bullet.y -= 4;
				SDL_FillRect(screen, &bullet, SDL_MapRGB(screen->format, 20, 210, 200));
			}
			else{
				shoot = 0;
			}
		}
		
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		//SDL_Flip(screen);
		SDL_Delay(1000/60);

	}
    
    SDL_FreeSurface(player);
    SDL_Quit();
    
	return 0;
 }

