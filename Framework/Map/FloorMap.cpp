#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "../Character/Character.hpp"
#include "FloorMap.hpp"





FloorMap::FloorMap(){
    tileData = new TileData[MaxMapWidth * MaxMapHeight];
    
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            if( i == 0 || j == 0 || i == MaxMapHeight - 1 || j == MaxMapWidth - 1){
                tileData[i * MaxMapWidth + j].Property = 0b00000011;
            }
            else{
                tileData[i * MaxMapWidth + j].Property = 0b00000000;
            }
            tileData[i * MaxMapWidth + j].State = 0;
        }
    }

    upstairPos = new Vector2[3];
    downstairPos = new Vector2[3];

    //set testWalls

    for(int i = 20;i < 30 ; i++){
         tileData[40 * MaxMapWidth + i].Property = 0b00000011;
    }
    
    for(int i = 40;i < 50 ; i++){
         tileData[i * MaxMapWidth + 23].Property = 0b00000011;
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



bool FloorMap::moveCharacter(Vector2 from, Vector2 to){
    TileData* fromTile = &tileData[from.y * MaxMapWidth + from.x];
    TileData* toTile = &tileData[to.y * MaxMapWidth + to.x];

    if( fromTile->character != nullptr && toTile->character == nullptr && isMovable(to.x, to.y) == true){
        //현재 타일에 케릭터가 있고, 대상 타일에 캐릭터가 없고
        //대상 타일로 움직일 수 있는 상태    
        toTile->character = fromTile->character;
        fromTile->character = nullptr;
        return true;
    }
    else if( fromTile->character != nullptr && toTile->character == nullptr && isMovable(to.x, to.y) == false){
        //현재 타일에 케릭터가 있고, 대상 타일에 캐릭터가 없고
        //대상 타일로 움직일 수 없는
        return false;
    }
    else if (fromTile->character != nullptr && toTile->character != nullptr){
        //움직이고자 한 타일에 적이 있을때
        //공격해야겠지?
        fromTile->character->MeleeAttack( toTile->character );
        return false;
    }
    else if(fromTile->character == nullptr ){
        //from 타일에 케릭터가 없음
        //에러 표기
        LogController::PrintLog( "No char : " + std::to_string(from.y * MaxMapWidth + from.x)  );
        return false;
    }
    else{
                        LogController::PrintLog( "555" );
        //다른 경우가 잇을까
        
                        
        return false;
    }
    return false;
}

bool FloorMap::characterEnter(Vector2 pos, BaseCharacter* chara){
    tileData[pos.y * MaxMapWidth + pos.x].character = chara;
    return false;
}

bool FloorMap::isMovable(int x, int y){
    return !(tileData[y * MaxMapWidth + x].Property       & 0b00000001);
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
