#pragma once
#include <iostream>
#include <map>
#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"

class FloorMap;
class BaseCharacter{
    public : 
        BaseCharacter(std::string name);
        ~BaseCharacter();

        virtual bool Initialize() = 0;
        virtual bool Move(int x, int y) = 0;

        virtual bool goUpstair() = 0;
        virtual bool goDownstair() = 0;
        
        Vector2 GetPos(){
            return position;
        }

        std::string GetStringData( std::string dataName);
        Vector2 GetPercentData( std::string dataName);
        int GetValueData( std::string dataName);

    protected:
        std::string name;
        Vector2 position;
        FloorMap* currentMap;
 
        bool setStringData( std::string dataName, std::string stringData);
        bool setPercentData( std::string dataName, int curValue, int MaxValue);
        bool setValueData( std::string dataName, int value);

        std::map<std::string, std::string > stringData;
        std::map<std::string, Vector2> percentData;
        std::map<std::string, int > valueData;
};