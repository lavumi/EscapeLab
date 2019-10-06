#include "BaseUI.hpp"


BaseUI::BaseUI(){

}

BaseUI::~BaseUI(){
    stringUIData.clear();
    percentUIData.clear();
    valueUIData.clear();
}


bool BaseUI::InitStringData(std::string dataName){
    std::pair< std::map<std::string, std::string>::iterator, bool > pr;
    pr = stringUIData.insert(std::make_pair( dataName, "BASE_STRING"));
    if( pr.second == true){
        stringUIOrder.push_back(dataName );
        return true;
    }
    else{
        return false;
    }
}

bool BaseUI::InitPercentData(std::string dataName){
    std::pair< std::map<std::string, Vector2>::iterator, bool > pr;
    Vector2 data(0,0); 
    pr = percentUIData.insert(std::make_pair( dataName, data));
    if( pr.second == true){
        percentUIOrder.push_back(dataName );
        return true;
    }
    else{
        return false;
    }
}

bool BaseUI::InitValueData(std::string dataName){
    std::pair< std::map<std::string, int>::iterator, bool > pr;
    pr = valueUIData.insert(std::make_pair( dataName, 0));
    if( pr.second == true){
        valueUIOrder.push_back(dataName );
        return true;
    }
    else{
        return false;
    }
}

bool BaseUI::SetStringData(std::string dataName, std::string stringData){

    auto iter = stringUIData.find(dataName);
    if( iter == stringUIData.end()){
        return false;
    }
    else {
        //TODO 여기 메모리 릭 안나냐?
        iter->second = stringData;
        return true;
    }

}

bool BaseUI::SetPercentData(std::string dataName, int curValue, int MaxValue){


    Vector2 data (curValue, MaxValue );

    auto iter = percentUIData.find(dataName);
    if( iter == percentUIData.end()){
        return false;
    }
    else {
        iter->second = data;
        return true;
    }
}

bool BaseUI::SetValueData(std::string dataName, int value){


    auto iter = valueUIData.find(dataName);
    if( iter == valueUIData.end()){
        return false;
    }
    else {
        iter->second = value;
        return true;
    }
}

std::string BaseUI::GetStringData( std::string dataName){
    auto iter = stringUIData.find(dataName);
    if( iter == stringUIData.end()){
        return "";
    }
    else {
        return iter->second;
    }
}

Vector2 BaseUI::GetPercentData( std::string dataName){
    auto iter = percentUIData.find(dataName);
    if( iter == percentUIData.end()){
        return Vector2(0,0);
    }
    else {
        return iter->second;
    }
}

int BaseUI::GetValueData( std::string dataName){
    auto iter = valueUIData.find(dataName);
    if( iter == valueUIData.end()){
        return 0;
    }
    else {
        return iter->second;
    }
}