#include "FloorMap.hpp"
#include "../Variables.hpp"

FloorMap::FloorMap(){
    tileType = new TileType[MaxMapWidth * MaxMapHeight];

    for( int i = 0;i < MaxMapWidth ; i++){  
        for( int j = 0;j < MaxMapHeight ; j++){
            if( i == 0 || j == 0 || i == MaxMapWidth - 1 || j == MaxMapHeight - 1){
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
