#include <iostream>
#include <map>
#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"
#include "../UserInterface/LogController.hpp"
#include "Character.hpp"

BaseCharacter::BaseCharacter(std::string name){
    this->name = name;
}

BaseCharacter::~BaseCharacter(){

}

bool BaseCharacter::Move(int x, int y){

    int targetPosX =  position.x + x;
    int targetPosY =  position.y + y;

    int targetTile = ((int*)currentMap->getData())[ targetPosY * MaxMapWidth + targetPosX];
    if( targetTile & 0x01 ){
        LogController::PrintLog( "Can't Move" );
        return false;
    }
    else
    {
        position.x = targetPosX;
        position.y = targetPosY;
        LogController::PrintLog( "MoveTo " + std::to_string( targetPosX )  + " " + std::to_string( targetPosY ) );
        return true;
    }
}


bool BaseCharacter::goUpstair(FloorMap* targetMap){
    currentMap = targetMap;
}

bool BaseCharacter::goDownstair(FloorMap* targetMap){
    currentMap = targetMap;
}


bool BaseCharacter::setStringData(std::string dataName, std::string data){
    stringData.insert(std::make_pair(dataName, data));
}

bool BaseCharacter::setPercentData(std::string dataName, int curValue, int MaxValue){
    Vector2 data (curValue, MaxValue ); 
    percentData.insert(std::make_pair(dataName, data));
}

bool BaseCharacter::setValueData(std::string dataName, int value){
    valueData.insert(std::make_pair(dataName, value));
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