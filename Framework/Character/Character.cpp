#include <iostream>
#include <map>
#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"
#include "../UserInterface/LogController.hpp"
#include "FieldOfView.hpp"
#include "Character.hpp"

BaseCharacter::BaseCharacter(std::string name, bool isPlayer){
    this->name = name;
    fov = new FieldOfView(this);
    sightSize = 8;
    isPlayerCharacter = isPlayer;
}

BaseCharacter::~BaseCharacter(){

}

bool BaseCharacter::Move(int x, int y){



    Vector2 targetPos;
    targetPos.x = position.x + x;
    targetPos.y = position.y + y;


    if( currentMap->moveCharacter(position, targetPos) == true ){
        LogController::PrintLog( "MoveTo " + std::to_string( targetPos.x + targetPos.y * MaxMapWidth) );
        position = targetPos;
        if(isPlayerCharacter){
            currentMap->resetfovData();
            fov->Compute( position, sightSize);
        }

        return true;
    }
    else{
      //  TakeDanage(14);
        LogController::PrintLog( "Can't Move" );
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
    int atk = valueData.find("ATK")->second;
    LogController::PrintLog("ATK " + std::to_string(atk) + " damage");
    target->TakeDanage(atk);
}

void BaseCharacter::TakeDanage(int atk){
    int def = GetValueData("DEF");


    Vector2 hp = GetPercentData("HP"); 
    hp.x -= atk - def;
    std::string myname = GetStringData("Name");
    LogController::PrintLog(myname + " take " + std::to_string(atk -def ) + " damage.");

}