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
    T_Wall ,
    T_Obstacle,
    T_Dark_noUse
};


class FloorMap{
    public : 
        FloorMap();
        ~FloorMap();

        TileType* getData();
    private : 
        
        TileType* tileType;

};