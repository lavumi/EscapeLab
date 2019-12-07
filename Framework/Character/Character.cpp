#include <iostream>
#include <map>
#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"
#include "../UserInterface/LogController.hpp"
#include "../UserInterface/DataController.hpp"
#include "EnemyStateMachine.hpp"
#include "BattleCtrl.hpp"
#include "FieldOfView.hpp"
#include "Character.hpp"

BaseCharacter::BaseCharacter(){
    stats = new Status();
}

BaseCharacter::~BaseCharacter(){
    if(isPlayerCharacter == true )
        delete fov;
    else 
        delete stateMachine;

    delete stats;
}

bool BaseCharacter::Initialize( BattleCtrl* battleCtrl, Status pStats, Vector2 position,bool isPlayer = false){
    btlCtrl = battleCtrl;
    if(isPlayer == true ){
        fov = new FieldOfView(this);
    }
    else {
        stateMachine = new EnemyStateMachine( this );
    }


    this->name = pStats.StringData[0];
    this->position = position;
    sightSize = 8;
    *stats = pStats;

    isPlayerCharacter = isPlayer;
    _isDead = true;
    
    return true;
}

char BaseCharacter::GetNameHead(){
    return stats->StringData[StatusData::Name][0];
}

std::string BaseCharacter::getStatusData(StatusData::stringData data){
    std::string returnValue;
    returnValue = stats->StringData[data];
    return returnValue;
}

Vector2 BaseCharacter::getStatusData(StatusData::vectorData data) {
    Vector2 returnValue;
    returnValue = stats->VectorData[data];
    return returnValue;
}

int BaseCharacter::getStatusData(StatusData::intData data){
    int returnValue;
    returnValue = stats->intData[data];
    return returnValue;
}

bool BaseCharacter::Move(int x, int y){
    Vector2 targetPos;
    targetPos.x = position.x + x;
    targetPos.y = position.y + y;

    if( currentMap->moveCharacter(position, targetPos) == true ){
        position = targetPos;
        if(isPlayerCharacter){
            currentMap->resetfovData();
            fov->Compute( position, sightSize);
        }
        return true;
    }
    else{
        return false;
    }

}

bool BaseCharacter::__setPosition(Vector2 pos ){
    if( currentMap->moveCharacter(position, pos) == true ){
        position = pos;
        if(isPlayerCharacter){
            currentMap->resetfovData();
            fov->Compute( position, sightSize);
        }
        return true;
    }
    else{
        return false;
    }
}

bool BaseCharacter::goUpstair(FloorMap* targetMap){
    currentMap = targetMap;
    targetMap->characterEnter(position, this);
    if(isPlayerCharacter){
        currentMap->resetfovData();
        fov->Compute( position, sightSize);
    }
    return true;
}

bool BaseCharacter::goDownstair(FloorMap* targetMap){

    currentMap = targetMap;
    targetMap->characterEnter(position, this);
    if(isPlayerCharacter){
        currentMap->resetfovData();
        fov->Compute( position, sightSize);
    }
    return true;
}

bool BaseCharacter::MeleeAttack(BaseCharacter* target ){
    btlCtrl->MeleeAttack(this, target);
    return true;
}

bool BaseCharacter::RangeAttack(Vector2 target){
    btlCtrl->RangeAttack( this, target );
    return true;
}

void BaseCharacter::TakeDamage(int damage){
    stats->VectorData[StatusData::HP].x -= damage;
    if( stats->VectorData[StatusData::HP].x <= 0)
        die();
}

void BaseCharacter::die(){
    if(currentMap->removeCharacter(position, this) == true){
        LogController::PrintLog( name + " DIE!!");
        DataController::getInstance()->removeCharacter(this);
    }
    else{
        LogController::PrintLog("error : "+ name + " DIE!!");
    }
    _isDead = false;
}


void BaseCharacter::Update(){
    if( isPlayerCharacter == false )
        stateMachine->Update();
}
