#include "Character.hpp"

BaseCharacter::BaseCharacter(std::string name){
    this->name = name;
}

BaseCharacter::~BaseCharacter(){

}


bool BaseCharacter::setStringData(std::string dataName, std::string data){

    stringData.insert(std::make_pair(dataName, data));
    // auto iter = stringData.find(dataName);
    // if( iter == stringData.end()){
    //     return false;
    // }
    // else {
    //     //TODO 여기 메모리 릭 안나냐?
    //     iter->second = data;
    //     return true;
    // }

}

bool BaseCharacter::setPercentData(std::string dataName, int curValue, int MaxValue){
    Vector2 data (curValue, MaxValue ); 
    percentData.insert(std::make_pair(dataName, data));


    // auto iter = percentData.find(dataName);
    // if( iter == percentData.end()){
    //     return false;
    // }
    // else {
    //     iter->second = data;
    //     return true;
    // }
}

bool BaseCharacter::setValueData(std::string dataName, int value){
    valueData.insert(std::make_pair(dataName, value));
    // auto iter = valueData.find(dataName);
    // if( iter == valueData.end()){
    //     return false;
    // }
    // else {
    //     iter->second = value;
    //     return true;
    // }
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