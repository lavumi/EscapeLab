#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "../Character/Character.hpp"
#include "FloorMap.hpp"





FloorMap::FloorMap(){
    tileData = new TileData[MaxMapWidth * MaxMapHeight];
    
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            if( i == 0 || j == 0 || i == MaxMapHeight - 1 || j == MaxMapWidth - 1){
                tileData[i * MaxMapWidth + j].Property = T_Wall;
            }
            else{
                tileData[i * MaxMapWidth + j].Property = T_Base;
            }
            tileData[i * MaxMapWidth + j].State = 0;
        }
    }


    //set testWalls

    for(int i = 20;i < 30 ; i++){
         tileData[40 * MaxMapWidth + i].Property = T_Wall;
    }
    
        for(int i = 40;i < 50 ; i++){
         tileData[i * MaxMapWidth + 23].Property = T_Wall;
    }
}


FloorMap::~FloorMap(){
    delete[] tileData;

}

TileData* FloorMap::getData(){
    return tileData;
}

bool FloorMap::isInSight(int x, int y){
    return  tileData[y * MaxMapWidth + x].State & 0b00000001;
}

bool FloorMap::isMovable(int x, int y){
    return tileData[y * MaxMapWidth + x].Property & 0b00000001;
}

bool FloorMap::isVisible(int x, int y){
    return tileData[y * MaxMapWidth + x].Property >> 1 & 0b00000001;
}

void FloorMap::setVisible(int x, int y){
    if( x + y * MaxMapWidth > MaxMapWidth * MaxMapHeight)
        return;
   tileData[y * MaxMapWidth + x].State = 0b00000001;
}

void FloorMap::resetfovData(){
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            tileData[i * MaxMapWidth + j].State = 0;
        }
    }
}
