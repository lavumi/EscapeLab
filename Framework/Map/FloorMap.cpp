#include "FloorMap.hpp"
#include "../Variables.hpp"

FloorMap::FloorMap(){
    tileType = new TileType[MaxMapWidth * MaxMapHeight];

    int a = 0;
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
}


FloorMap::~FloorMap(){
    delete[] tileType;
}

TileType* FloorMap::getData(){
    return tileType;
}
