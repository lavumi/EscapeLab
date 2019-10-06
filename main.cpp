#include <stdio.h>
#include <conio.h>
#include "Source/GameMain.hpp"


bool initialize();

int main(){
    GameMain* gameMain = new GameMain();



    gameMain->Initialize();

    char ch;
    while(true){
        
        gameMain->Update();

    }
    
    system("pause");
}