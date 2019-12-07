#include "EnemyStateMachine.hpp"
#include "Character.hpp"
#include "../UserInterface/DataController.hpp"

EnemyStateMachine::EnemyStateMachine( BaseCharacter* owner ){
    this->owner = owner;
    currentState = EnemyState::FIND_PLAYER;
    dataCtrl = DataController::getInstance();
}

EnemyStateMachine::~EnemyStateMachine(){

}


void EnemyStateMachine::Update(){
    switch ( currentState ){
        case EnemyState::NONE:

            break;
        case EnemyState::SLEEP:

            break;
        case EnemyState::WANDERING:
            wantering();
            checkCondition();
            break;
        case EnemyState::FIND_PLAYER:
            fallowCharacter();
            break;
        
    }
}


void EnemyStateMachine::wantering(){
     int rnd = rand();

     switch (rnd % 4){
         case 0:
            owner->Move(1,0);
            break;
         case 1:
            owner->Move(-1,0);
            break;
         case 2:
            owner->Move(0,1);
            break;
         case 3:
            owner->Move(0,-1);
            break;
     }
}

void EnemyStateMachine::fallowCharacter(){
    Vector2 pPos = dataCtrl->GetPlayerPos();
    Vector2 myPos = owner->GetPos();

    int deltaX = myPos.x - pPos.x;
    int deltaY = myPos.y - pPos.y;

    if ( abs(deltaX) >= abs(deltaY) && deltaX >= 0 ){
        owner->Move( -1 , 0);
    }
    else if ( abs(deltaX) >= abs(deltaY) && deltaX < 0 ){
        owner->Move( 1 , 0);
    }
    else if ( abs(deltaX) < abs(deltaY) && deltaY >= 0 ){
        owner->Move( 0 , -1);
    }
    else if ( abs(deltaX) < abs(deltaY) && deltaY < 0 ){
        owner->Move( 0 , 1);
    }
}

void EnemyStateMachine::rangeAttack(){

}

void EnemyStateMachine::checkCondition(){

}