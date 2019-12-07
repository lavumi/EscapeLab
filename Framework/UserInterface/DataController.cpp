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

std::string DataController::GetStringUIData( StatusData::stringData data){
    return player->getStatusData(data);
}

Vector2 DataController::GetPercentUIData( StatusData::vectorData data){
    return player->getStatusData(data);
}

int DataController::GetValueUIData( StatusData::intData data){
    return player->getStatusData(data);
}

Vector2 DataController::GetPlayerPos(){
    return player->GetPos();
}


bool DataController::setCharacter( BaseCharacter* character){
    characters.push_back( character);
    return true;
}


bool DataController::removeCharacter( BaseCharacter* character){

    auto iter = std::find(characters.begin(), characters.end(), character);
    characters.erase(iter);
    return true;
}

int DataController::GetEnemyCount(){
    return characters.size();
}

Vector2 DataController::GetEnemyPos(int index){
    auto iter = characters.front();
    iter += index;
    return iter->GetPos();
}

void DataController::Update(){
    std::for_each(characters.begin(), characters.end(), [](BaseCharacter* character) { 
        character->Update();
    });
}

// auto DataController::GetUIstringOrder(){
//     return StatusData::stringList;
// };
// auto DataController::GetUIpercentOrder(){
//     return StatusData::vectorList;
// };
// // StatusData::intData* DataController::GetUIvalueOrder(){
// //     return StatusData::intList;
// // };
// StatusData::intData (&GetUIvalueOrder())[6]{
//     return StatusData::intList;
// };