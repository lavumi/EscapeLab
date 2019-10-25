#pragma once

/**
 * TileType
 *  
 * Can Walk         Can See         : 0x00
 * Can`t Walk       Can See         : 0x01
 * Can Walk         Can`t See       : 0x10
 * Can`t Walk       Can`t See       : 0x11
 */
enum TileType {
    T_Base ,
    T_Obstacle,
    T_Dark,
    T_Wall,
};

typedef struct _singleTile{
    unsigned char Property;
    BaseCharacter* character;
    //std::vector<> items;
} TileData;

class FloorMap{
    public : 
        FloorMap();
        ~FloorMap();

        TileType* getData();

        bool isMovable(int x, int y);
        bool isVisible(int x, int y);
        bool isInSight(int x, int y);
        void setVisible(int x, int y);
        void resetfovData();
    private : 
        
        TileType* tileType;
        bool* fovData;

};
