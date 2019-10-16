#ifdef __NCURSES_H
    #include <ncurses.h>
#else
    #include <conio.h>
#endif

#include "../Character/Character.hpp"
#include "InputCtrl.hpp"


InputController* InputController::instance = nullptr;

void InputController::Delete(){
    delete instance;
}

InputController::InputController(){
    player = nullptr;
}

InputController::~InputController(){

}

void InputController::SetPlayer( BaseCharacter* player ){
    this->player = player;
}

void InputController::WairForInput(){
    char ch = getch();
    if(ch == 'a')
        player->Move(-1,0);
    if(ch == 'd')
        player->Move(1,0);
    if(ch == 'w')
        player->Move(0,-1);
    if(ch == 's')
        player->Move(0,1);
}