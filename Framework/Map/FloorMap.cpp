#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "../Character/Character.hpp"
#include "FloorMap.hpp"





FloorMap::FloorMap(){
    tileData = new TileData[MaxMapWidth * MaxMapHeight];
    upstairPos = new Vector2[3];
    downstairPos = new Vector2[3];



    rndMap = new RandomMap(MaxMapHeight,MaxMapWidth  );
    rndMap->initMap();
    rndMap->makeRNDmap(MT_FOREST);

    setData( MaxMapWidth, MaxMapHeight , rndMap->getMapData());
}


FloorMap::~FloorMap(){
    delete[] tileData;
    delete rndMap;
}


TileData* FloorMap::getData(){
    return tileData;
}

void FloorMap::setData( int width, int height , int *mapData) {
    for( int i = 0;i < height * width ; i++){

            if( mapData[i] == TILE_WALL ){
                tileData[i ].cantMove = false;
                tileData[i ].cantSee = false;
                tileData[i ].tileID = 1;
            }
            else if ( mapData[i] == TILE_BASE){
                tileData[i].cantMove = true;
                tileData[i].cantSee =  true;
                tileData[i ].tileID = 0;
            }
            else if ( mapData[i] == TILE_WATER){
                tileData[i].cantMove = false;
                tileData[i].cantSee =  true;
                tileData[i ].tileID = 2;
            }
            else if ( mapData[i] == TILE_BRIDGE){
                tileData[i].cantMove = true;
                tileData[i].cantSee =  true;
                tileData[i ].tileID = 6;
            }
            else if ( mapData[i] == TILE_START ){
                tileData[i].cantMove = true;
                tileData[i].cantSee =  true;
                tileData[i ].tileID = 0;
                upstairPos[0] = Vector2( i % width ,(int) ( i / width ));
            }
            else{
                tileData[i ].cantMove = true;
                tileData[i ].cantSee =  true;
                tileData[i ].tileID = 0;
            }
    }
}


Vector2 FloorMap::getStartPos(){
    return upstairPos[0];
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

int FloorMap::getTileID(int x, int y) {
    return 0;
}
