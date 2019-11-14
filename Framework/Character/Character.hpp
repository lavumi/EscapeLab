#pragma once
#include "../precompiled.hpp"

class FloorMap;
class FieldOfView;
class BaseBattleCtrl;

namespace StatusData{
    enum stringData: unsigned int{
        Name,
    };

    enum vectorData: unsigned int{
        HP,
        MP,
    };

    enum intData: unsigned int{
        STR,
        EV,
        DEX,
        DEF,
        INT,
        GLD
    };


    stringData stringList[1]= {Name};
    vectorData vectorList[2] = { HP, MP};
    intData intList[6] = {         STR,        EV,        DEX,        DEF,        INT,        GLD};
}

typedef struct _status{
        std::string StringData[1];
        Vector2 VectorData[2];
        int intData[6];
        //std::string Name;

        // Vector2 HP;
        // Vector2 MP;
        // int STR;  
        // int EV ; 
        // int DEX;  
        // int DEF;  
        // int INT;   
        // int GLD;
}Status;

class BaseCharacter{
    public : 
        BaseCharacter();
        ~BaseCharacter();


        bool Initialize(std::string name, BaseBattleCtrl* battleCtrl, bool isPlayer);

        bool Move(int x, int y) ;
        bool goUpstair(FloorMap* targetMap);
        bool goDownstair(FloorMap* targetMap);

        std::string getStatusData(StatusData::stringData);
        Vector2 getStatusData(StatusData::vectorData);
        int getStatusData(StatusData::intData);

        Vector2 GetPos(){
            return position;
        }

        FloorMap* GetCurrentMap(){ return currentMap;};


        bool MeleeAttack(BaseCharacter* target );

        void TakeDamage(int atk);

    protected:
        bool isPlayerCharacter;

        std::string name;
        Vector2 position;
        FloorMap* currentMap;
        Status* stats;
        

        FieldOfView* fov;

        int sightSize;

        BaseBattleCtrl* btlCtrl;

        void die();
};