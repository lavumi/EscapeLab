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


bool BaseCharacter::setStringData(std::string dataName, std::string data){
    stringData.insert(std::make_pair(dataName, data));
        return true;
}

bool BaseCharacter::setPercentData(std::string dataName, int curValue, int MaxValue){
    Vector2 data (curValue, MaxValue ); 
    percentData.insert(std::make_pair(dataName, data));
        return true;
}

bool BaseCharacter::setValueData(std::string dataName, int value){
    valueData.insert(std::make_pair(dataName, value));
        return true;
}

std::string BaseCharacter::GetStringData( std::string dataName){
    auto iter = stringData.find(dataName);
    if( iter == stringData.end()){
        return "AA";
    }
    else {
        return iter->second;
    }
}

Vector2 BaseCharacter::GetPercentData( std::string dataName){
    auto iter = percentData.find(dataName);
    if( iter == percentData.end()){
        return Vector2(0,0);
    }
    else {
        return iter->second;
    }
}

int BaseCharacter::GetValueData( std::string dataName){
    auto iter = valueData.find(dataName);
    if( iter == valueData.end()){
        return 0;
    }
    else {
        return iter->second;
    }
}

bool BaseCharacter::MeleeAttack(BaseCharacter* target ){
    btlCtrl->MeleeAttack(this, target);
    return true;
}

void BaseCharacter::TakeDamage(int damage){
    auto iter = percentData.find("HP");
    if( iter == percentData.end()){
        return ;
    }
    else {
        iter->second.x -= damage;
        if( iter->second.x <= 0){
            die();
        }
    }

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
