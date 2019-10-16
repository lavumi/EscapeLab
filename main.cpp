#include "Framework/precompiled.hpp"
#include "Source/GameMain.hpp"


int main(){
    GameMain* gameMain = new GameMain();



    gameMain->Initialize();

    while(true){
        gameMain->Update();
    }
    
    system("pause");

    return 0;
}
