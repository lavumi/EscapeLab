#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "../Character/Character.hpp"
#include "FloorMap.hpp"





FloorMap::FloorMap(){
    tileData = new TileData[MaxMapWidth * MaxMapHeight];
    
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            if( i == 0 || j == 0 || i == MaxMapHeight - 1 || j == MaxMapWidth - 1){
                tileData[i * MaxMapWidth + j].cantMove = false;
                tileData[i * MaxMapWidth + j].cantSee = false;
            }
            else if ( i % 2 == 0 && j % 2 == 0 && rand() % 3 == 1){
                tileData[i * MaxMapWidth + j].cantMove = false;
                tileData[i * MaxMapWidth + j].cantSee = false;
            }
            else{
                tileData[i * MaxMapWidth + j].cantMove = true;
                tileData[i * MaxMapWidth + j].cantSee = true;
            }

        }
    }

    upstairPos = new Vector2[3];
    downstairPos = new Vector2[3];

    //set testWalls
    for(int i = 20;i < 30 ; i++){
        tileData[40 * MaxMapWidth + i].cantMove = false;
        tileData[40 * MaxMapWidth + i].cantSee = false;
    }
    
    for(int i = 40;i < 50 ; i++){
         tileData[i * MaxMapWidth + 23].cantMove = false;
         tileData[i * MaxMapWidth + 23].cantSee = false;
    }



}


FloorMap::~FloorMap(){
    delete[] tileData;

}

TileData* FloorMap::getData(){
    return tileData;
}



BaseCharacter* FloorMap::getCharacter(int x, int y){
    return  tileData[y * MaxMapWidth + x].character;
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
        //이거 안좋은 코드 같은데...
        //여기서 공격이 아니라 뭔가 다른걸 반환해줘서 캐릭터에서 그걸 받아서 실행하는게 더 좋을거 같다
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
    return tileData[y * MaxMapWidth + x].cantMove;
}

bool FloorMap::hasSeen(int x, int y){
    return tileData[y * MaxMapWidth + x].hasSeen;
}

bool FloorMap::isVisible(int x, int y){
    return !tileData[y * MaxMapWidth + x].cantSee;
}

bool FloorMap::isInSight(int x, int y){
    return  tileData[y * MaxMapWidth + x].onSight ;
}

void FloorMap::setVisible(int x, int y){
    if( x + y * MaxMapWidth > MaxMapWidth * MaxMapHeight)
        return;

    tileData[y * MaxMapWidth + x].onSight = true;
    tileData[y * MaxMapWidth + x].hasSeen = true;

}

void FloorMap::resetfovData(){
    for( int i = 0;i < MaxMapHeight ; i++){  
        for( int j = 0;j < MaxMapWidth ; j++){
            tileData[i * MaxMapWidth + j].onSight = false;
        }
    }
}

bool FloorMap::removeCharacter(Vector2 pos, BaseCharacter* chara){
    if( tileData[pos.y * MaxMapWidth + pos.x].character == chara){
        tileData[pos.y * MaxMapWidth + pos.x].character = nullptr;
        return true;
    }
    else{
        return false;
    }
}