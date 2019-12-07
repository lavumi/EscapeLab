
#include "../precompiled.hpp"
#include "../Variables.hpp"
#include "Character.hpp"
#include "CharacterGenerator.hpp"
#include "BattleCtrl.hpp"


CharacterGenerator::CharacterGenerator(){
    characterPool = new BaseCharacter[100];
}

CharacterGenerator::~CharacterGenerator(){
    delete[] characterPool;
}

void CharacterGenerator::Initialize(BattleCtrl* btlCtrl){
    this->btlCtrl = btlCtrl;
}

BaseCharacter* CharacterGenerator::makeCharacter( Status data , FloorMap* map, Vector2 Pos, bool isPlayer){

    BaseCharacter* charPtr = nullptr;
    if(isPlayer == true)
        charPtr = &characterPool[0];
    else{
        for( int i = 1; i < 100 ; i++){
            if(characterPool[i].isDead() == false){
                charPtr = &characterPool[i];
                break;
            }
        }
    }

    if( charPtr != nullptr){
        charPtr->Initialize(btlCtrl, data, Pos, isPlayer);
        charPtr->goDownstair( map );
    }
       
    return charPtr;
}