#include "../Character/Character.hpp"
#include "InputCtrl.hpp"


InputController* InputController::instance = nullptr;

void InputController::Delete(){
    delete instance;
}

InputController::InputController(){
    player = nullptr;
    currentMode = InputMode::NORMAL;
    cursor = Vector2(0,0);
}

InputController::~InputController(){

}

void InputController::SetPlayer( BaseCharacter* player ){
    this->player = player;
}

bool InputController::WairForInput(){

    char ch = getch();

    if( currentMode == NORMAL ){
        if(ch == 'h')
            player->Move(-1,0);
        if(ch == 'l')
            player->Move(1,0);
        if(ch == 'k')
            player->Move(0,-1);
        if(ch == 'j')
            player->Move(0,1);
        if(ch == 'f')
            changeMode(RANGE_ATTACK);
        if(ch == 'q')
            return false;
    }
    else if( currentMode == RANGE_ATTACK ){
        if(ch == 'h')
            cursor.x -= 1;
        if(ch == 'l')
            cursor.x += 1;
        if(ch == 'k')
           cursor.y -= 1;
        if(ch == 'j')
            cursor.y += 1;
        if(ch == '\n'){
            player->RangeAttack( cursor );
            changeMode(NORMAL);
        }
        if(ch == 'q'){
            changeMode(NORMAL);
        }
    }
    return true;
}

void InputController::changeMode(InputMode mode){
    if( mode == currentMode )
        return;

    switch ( mode ){
        case NORMAL:
            currentMode = NORMAL;
            cursor = Vector2(0,0);
            break;
        case RANGE_ATTACK :
            cursor = player->GetPos();
            currentMode = RANGE_ATTACK;
            break;
    }
}

Vector2 InputController::GetCursorPos(){
    return cursor;
}