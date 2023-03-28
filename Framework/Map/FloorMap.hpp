#pragma once
#include "../Variables.hpp"
#include "./MapMaker.h"
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

typedef struct singleTile{
    bool cantMove;
    bool cantSee;
    bool onSight;
    bool hasSeen;
    int tileID;
    BaseCharacter* character;

    singleTile(){
        cantMove = false;
        cantSee = false;
        onSight = false;
        hasSeen = false;
        character = nullptr;
    };

    char getTileID() const{
        return tileID;//!cantMove + !cantSee * 2;
    }

    ~singleTile()= default;;
} TileData;

class FloorMap{
    public : 
        FloorMap();
        ~FloorMap();

        TileData* getData();
        void setData( int width, int height , int* mapData );

        bool isMovable(int x, int y);
        bool isVisible(int x, int y);
        bool isInSight(int x, int y);
        bool hasSeen(int x, int y);
        int getTileID( int x, int y );
        BaseCharacter* getCharacter(int x, int y);
        void setVisible(int x, int y);
        bool moveCharacter(Vector2 from, Vector2 to);
        bool characterEnter(Vector2 pos, BaseCharacter* chara);
        bool removeCharacter(Vector2 pos, BaseCharacter* chara );
        void resetfovData();
        Vector2 getStartPos();
    private :
        RandomMap* rndMap;
        TileData* tileData;
        Vector2* upstairPos;
        Vector2* downstairPos;


};
