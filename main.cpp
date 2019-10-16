#include "Framework/precompiled.hpp"
#include "Source/GameMain.hpp"


int main(){
    GameMain* gameMain = new GameMain();



    gameMain->Initialize();

    bool running = true;
    while(running){
       running = gameMain->Update();
    }

#ifdef __NCURSES_H
    endwin(); 
#endif
    
    return 0;
}
