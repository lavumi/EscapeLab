#include "../UserInterface/LogController.hpp"
#include "FloorMap.hpp"
#include "../Variables.hpp"


//Map Int data
//xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxxx
// First 8bit : property of tile
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
// Second     : on Tile status
//      0 : enemy
//      1 : item
//      2 : 
//      3 : 
//      4 : 
//      5 :
//      6 :
//      7 : 


FloorMap::FloorMap(){
    tileType = new TileType[MaxMapWidth * MaxMapHeight];
    
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            if( i == 0 || j == 0 || i == MaxMapHeight - 1 || j == MaxMapWidth - 1){
                tileType[i * MaxMapWidth + j] = T_Wall;
            }
            else{
                tileType[i * MaxMapWidth + j] = T_Base;
            }
        }
    }


    //set testWalls

    for(int i = 20;i < 30 ; i++){
         tileType[40 * MaxMapWidth + i] = T_Wall;
    }
    
        for(int i = 40;i < 50 ; i++){
         tileType[i * MaxMapWidth + 23] = T_Wall;
    }

    fovData = new bool[MaxMapWidth * MaxMapHeight];
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            fovData[i * MaxMapWidth + j] = false;
        }
    }
}


FloorMap::~FloorMap(){
    delete[] tileType;
    delete[] fovData;
}

TileType* FloorMap::getData(){
    return tileType;
}

bool FloorMap::isInSight(int x, int y){
    return fovData[y * MaxMapWidth + x];
}

bool FloorMap::isMovable(int x, int y){
    return tileType[y * MaxMapWidth + x] & 0x01;
}

bool FloorMap::isVisible(int x, int y){
    return tileType[y * MaxMapWidth + x] >> 1 & 0x01;
}

void FloorMap::setVisible(int x, int y){
    if( x + y * MaxMapWidth > MaxMapWidth * MaxMapHeight)
        return;
    fovData[x + y * MaxMapWidth] = true;
}

void FloorMap::resetfovData(){

    std::fill(&fovData[0], &fovData[MaxMapWidth * MaxMapHeight - 1], false);
}
