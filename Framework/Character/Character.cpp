#include <iostream>
#include <map>
#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"
#include "../UserInterface/LogController.hpp"
#include "../UserInterface/DataController.hpp"
#include "BaseBattleCtrl.hpp"
#include "FieldOfView.hpp"
#include "Character.hpp"

BaseCharacter::BaseCharacter(){

}

BaseCharacter::~BaseCharacter(){
    delete fov;
}

bool BaseCharacter::Initialize(std::string name, BaseBattleCtrl* battleCtrl, bool isPlayer = false){
    this->name = name;
    if(isPlayer == true )
        fov = new FieldOfView(this);
    sightSize = 8;


    btlCtrl = battleCtrl;
    isPlayerCharacter = isPlayer;
    return true;
}

// Status BaseCharacter::getStatusData(){
//     Status returnValue;
//     returnValue = *stats;
//     returnValue.Name = stats->Name;
//     return returnValue;
// }

std::string BaseCharacter::getStatusData(StatusData::stringData data){
    std::string returnValue;
    // switch (data)
    // {
    // case stringData::Name:
    //    returnValue = stats->StringData[stringData::Name];
    //     break;
    // default:
    //     break;
    // }
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
       // LogController::PrintLog( "MoveTo " + std::to_string( targetPos.x + targetPos.y * MaxMapWidth) );
        position = targetPos;
        if(isPlayerCharacter){
            currentMap->resetfovData();
            fov->Compute( position, sightSize);
        }

        return true;
    }
    else{
      //  TakeDanage(14);
      //  LogController::PrintLog( "Can't Move" );
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
}

