#include "Framework/precompiled.hpp"
#include "Source/GameMain.hpp"


int main(){
    GameMain* gameMain = new GameMain();



    gameMain->Initialize();

    bool running = true;
    while(running){
       running = gameMain->Update();
    }

    endwin();
    return 0;
}
