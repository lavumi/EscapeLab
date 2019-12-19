#pragma once
#include "../Variables.hpp"
enum TileType {
    T_Base ,
    T_Obstacle,
    T_Dark,
    T_Wall,
};

class BaseCharacter;


//Map Int data
//xxxxxxxxx
// Property : property of tile
//      0 : can Move
//      1 : can See
//      2 : 
//      3 : 
//      4 : 
//      5 :
//      6 :
//      7 :
//
//
// State     : on Tile status
//      0 : onSight
//      1 : hasSeen
//      2 : 
//      3 : 
//      4 : 
//      5 :
//      6 :
//      7 : 

typedef struct _singleTile{
    unsigned char Property;
    unsigned char State;
    BaseCharacter* character;

    _singleTile(){
        Property = 0b00000000;
        State = 0b00000000;
        character = nullptr;
    };
    ~_singleTile(){

    };
} TileData;

class FloorMap{
    public : 
        FloorMap();
        ~FloorMap();

        TileData* getData();

        bool isMovable(int x, int y);
        bool isVisible(int x, int y);
        bool isInSight(int x, int y);
        bool hasSeen(int x, int y);
        BaseCharacter* getCharacter(int x, int y);
        void setVisible(int x, int y);
        bool moveCharacter(Vector2 from, Vector2 to);
        bool characterEnter(Vector2 pos, BaseCharacter* chara);
        bool removeCharacter(Vector2 pos, BaseCharacter* chara );
        void resetfovData();
    private : 
        
        TileData* tileData;
        Vector2* upstairPos;
        Vector2* downstairPos;

};
