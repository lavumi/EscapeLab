#include "../../Framework/Character/BattleCtrl.hpp"
#include "../../Framework/Character/Character.hpp"
#include "../../Framework/UserInterface/LogController.hpp"
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
    LogController::PrintLog( "RangeAttack " + std::to_string(target.x) + " " + std::to_string(target.y) + " Damage taken"  );
    return true;
}

int BattleCtrl::calculateDamage(int atk, int def){
    int result = atk - def;
    if(result <= 0)
        result = 1;
    return result;
}