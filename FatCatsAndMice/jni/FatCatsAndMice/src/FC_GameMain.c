#include <sdl.h>
void GameMain(); // FC_Game.cpp
                   
// O SDL redefine main como SDL_main no Android e iOS 
int main(int argc, char * argv[])
{        
    GameMain();
	return 0;              
}      
                    
  
                                     
