
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



bool DataController::setCharacter( BaseCharacter* character){
    characters.push_back( character);
}

bool DataController::SetUIStringData(std::string dataName){
    stringUIOrder.push_back( dataName );
}

bool DataController::SetUIPercentData(std::string dataName){
    percentUIOrder.push_back( dataName );
}

bool DataController::SetUIValueData(std::string dataName){
    valueUIOrder.push_back( dataName );
}

std::string DataController::GetStringUIData( std::string dataName){
    return characters[0]->GetStringData(dataName);
}

Vector2 DataController::GetPercentUIData( std::string dataName){
    return characters[0]->GetPercentData(dataName);
}

int DataController::GetValueUIData( std::string dataName){
    return characters[0]->GetValueData(dataName);
}

Vector2 DataController::GetPlayerPos(){
    return characters[0]->GetPos();
}