#pragma once
#include "../precompiled.hpp"

class FloorMap;
class FieldOfView;


class BaseCharacter{
    public : 
        BaseCharacter(std::string name, bool isPlayer = false);
        ~BaseCharacter();


        bool Move(int x, int y) ;

        virtual bool Initialize() = 0;
        bool goUpstair(FloorMap* targetMap);
        bool goDownstair(FloorMap* targetMap);
        
        Vector2 GetPos(){
            return position;
        }

        std::string GetStringData( std::string dataName);
        Vector2 GetPercentData( std::string dataName);
        int GetValueData( std::string dataName);

        FloorMap* GetCurrentMap(){ return currentMap;};

    protected:
        bool isPlayerCharacter;

        std::string name;
        Vector2 position;
        FloorMap* currentMap;
 
        bool setStringData( std::string dataName, std::string stringData);
        bool setPercentData( std::string dataName, int curValue, int MaxValue);
        bool setValueData( std::string dataName, int value);

        std::map<std::string, std::string > stringData;
        std::map<std::string, Vector2> percentData;
        std::map<std::string, int > valueData;

        FieldOfView* fov;

        int sightSize;
};