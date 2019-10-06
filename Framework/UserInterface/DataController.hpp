#pragma once
#include <iostream>
#include <vector>

#include "../Variables.hpp"
#include "../Character/Character.hpp"

class DataController{
    public :
        static DataController* getInstance(){
            if( instance == nullptr)
                instance = new DataController();
            return instance;
        }
        static bool Delete();

        bool setCharacter( BaseCharacter* character);


        //regoin UI
        bool SetUIStringData(std::string dataName);
        bool SetUIPercentData( std::string dataName);
        bool SetUIValueData( std::string dataName );

        std::string GetStringUIData( std::string dataName);
        Vector2 GetPercentUIData( std::string dataName);
        int GetValueUIData( std::string dataName);

        std::vector<std::string> GetUIstringOrder(){
            return stringUIOrder;
        };
        std::vector<std::string> GetUIpercentOrder(){
            return percentUIOrder;
        };
        std::vector<std::string> GetUIvalueOrder(){
            return valueUIOrder;
        };

        //endregion
        Vector2 GetPlayerPos();

    private:
        static DataController* instance;
        DataController();
        ~DataController();

        std::vector<BaseCharacter*> characters;

        std::vector<std::string> stringUIOrder;
        std::vector<std::string> percentUIOrder;
        std::vector<std::string> valueUIOrder;

};