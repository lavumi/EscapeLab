#include "../Character/Character.hpp"
#include "DataController.hpp"

DataController* DataController::instance = nullptr;

void DataController::Delete(){
    delete instance;
}

DataController::DataController(){

}

DataController::~DataController(){
    stringUIOrder.clear();
    percentUIOrder.clear();
    valueUIOrder.clear();
}

bool DataController::setPlayer( BaseCharacter* character){
    player = character;
    return true;
}

bool DataController::SetUIStringData(std::string dataName){
    stringUIOrder.push_back( dataName );
    return true;
}

bool DataController::SetUIPercentData(std::string dataName){
    percentUIOrder.push_back( dataName );
    return true;
}

bool DataController::SetUIValueData(std::string dataName){
    valueUIOrder.push_back( dataName );
    return true;
}

std::string DataController::GetStringUIData( std::string dataName){
    return player->GetStringData(dataName);
}

Vector2 DataController::GetPercentUIData( std::string dataName){
    return player->GetPercentData(dataName);
}

int DataController::GetValueUIData( std::string dataName){
    return player->GetValueData(dataName);
}

Vector2 DataController::GetPlayerPos(){
    return player->GetPos();
}


bool DataController::setCharacter( BaseCharacter* character){
    characters.push_back( character);
    return true;
}

int DataController::GetEnemyCount(){
    return characters.size();
}

Vector2 DataController::GetEnemyPos(int index){
    return characters[index]->GetPos();
}