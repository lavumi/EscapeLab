#include "BattleCtrl.hpp"
#include "Character.hpp"
#include "../UserInterface/LogController.hpp"
#include "../Map/FloorMap.hpp"
#include "BattleCtrl.hpp"


BattleCtrl::BattleCtrl(){

}

BattleCtrl::~BattleCtrl(){
    
}

bool BattleCtrl::MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) {
    int atk = attacker->getStatusData(StatusData::STR);
    int def = defender->getStatusData(StatusData::DEF);
    int damage = calculateDamage(atk, def);
    LogController::PrintLog( std::to_string(damage) + " Damage" );
    defender->TakeDamage(damage);
    return true;
}

bool BattleCtrl::RangeAttack( BaseCharacter* attacker, Vector2 target){
    int atk = attacker->getStatusData(StatusData::STR);
    FloorMap* curMap = attacker->GetCurrentMap();

    int deltaX, deltaY;
    int counter = 0;

    Vector2 start = attacker->GetPos();
    Vector2 end = target;


    int width = end.x - start.x;
    int height = end.y - start.y;



    if ( width < 0 ){
        deltaX = -1;
        width = -width;
    }
    else {
        deltaX = 1;
    }

    if ( height < 0 ) {
        deltaY = -1;
        height = -height;
    }
    else{
        deltaY = 1;
    }

    int x = start.x;
    int y = start.y;

    BaseCharacter* target_char;
    if ( width >= height ){
        for ( int i = 0; i < width ; i++){
            x += deltaX;
            counter += height;

            if( counter >= width ){
                y += deltaY;
                counter -= width;
            }
            if (curMap->isMovable(x,y ) == false )
                break;
            target_char = curMap->getCharacter(x, y);
            if ( target_char != nullptr)
                break;
        }
    }
    else {
        for ( int i = 0 ; i < height ; i++ ){
            y += deltaY;
            counter += width;

            if ( counter >= height ){
                x += deltaX;
                counter -= height;
            }
            if (curMap->isMovable(x,y ) == false )
                break;

            target_char = curMap->getCharacter(x, y);
            if ( target_char != nullptr)
                break;

        }
    }

    if( target_char != nullptr){
        int def = target_char->getStatusData(StatusData::DEF);
        int damage = calculateDamage(atk, def);
        target_char->TakeDamage( damage );
        LogController::PrintLog( target_char->getStatusData(StatusData::Name) + " take " +  std::to_string(damage) + " Damage" );
        return true;
    }
    else {
        LogController::PrintLog( "You hit Nothing" );
        return false;
    }



}

int BattleCtrl::calculateDamage(int atk, int def){
    int result = atk - def;
    if(result <= 0)
        result = 1;
    return result;
}