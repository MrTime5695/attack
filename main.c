#include <SDL/SDL.h>
#include <time.h>

/*
	space invaders clone written in SDL1.2
	* nov 28 2025
	* Marlow Rekers
*/

SDL_bool CheckCollision(SDL_Rect A, SDL_Rect B);

int SetRect(SDL_Rect A, int type);

int Timeout();

int main(int argc, char** argv){
	   
    int quit = 1;
    
    int xvel, yvel, colour;
    
    int shoot = 0;
    int envel = 0;
    
    int atk = 0;
    
    int tvalive = 1;
    
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
    
    rect.x = 10;rect.y = 208;rect.w = 32;rect.h = 32;
    bg.x = 0;bg.y = 0;bg.w = 320;bg.h = 240;
    enemy.x = 50;enemy.y = 10;enemy.y = 32;enemy.h = 32;
    bullet.x = 0;bullet.y = 230;bullet.w = 4;bullet.h =  8;
    shot.x = 0;shot.y = 0;shot.w = 4;shot.h =  8;
    
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

		if(CheckCollision(enemy, bullet)){
			tv = SDL_LoadBMP("tvc.bmp");
			tvalive = 0;
			//printf(": %d", tvalive);
		}
		
		//draw the enemy
		if(tvalive && tvalive != 3){
			if(Timeout()){
				int xdir = (rand()%50);
				int pol = (rand()%4);
				if(pol < 1)
					pol = 1;
				if(pol > 1)
					pol = -1;
				
				if(enemy.x < (320 - enemy.w)){
					enemy.x += (xdir * pol);
				}
			}
			
			SDL_BlitSurface(tv, NULL, screen, &enemy);
		}
		
		if(Timeout()){
			if(atk == 0 && tvalive != 3)
				atk = 1;
		}
		
		if(atk == 1){
			shot.x = (enemy.x + 16);
			shot.y = (enemy.y + 16);
			SDL_FillRect(screen, &shot, SDL_MapRGB(screen->format, 20, 210, 200));
			atk = 2;
		}
		if(atk == 2){
			if(shot.y < 232){
				shot.y += 2;
				if(CheckCollision(rect, shot))
					player = SDL_LoadBMP("tvc.bmp");
				SDL_FillRect(screen, &shot, SDL_MapRGB(screen->format, 20, 210, 200));
			}
			else{
				atk = 0;
			}
				
		}
		
		//draw the player
		SDL_BlitSurface(player, NULL, screen, &rect);
		
		if(tvalive == 0)
		{
			SDL_BlitSurface(tv, NULL, screen, &enemy);
			enemy.y += envel;
			if(Timeout()){
				tvalive = 3;
			}
			/*
			if(enemy.y < 240){
				envel += 2;
			}else{
				tvalive = 2;
			}
			*/
		}
		
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
 
 int SetRect(SDL_Rect A, int type){
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

