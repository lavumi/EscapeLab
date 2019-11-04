#include "../../Framework/Character/BaseBattleCtrl.hpp"
#include "../../Framework/Character/Character.hpp"
#include "../../Framework/UserInterface/LogController.hpp"
#include "BattleCtrl.hpp"


BattleCtrl::BattleCtrl(){

}

BattleCtrl::~BattleCtrl(){
    
}

bool BattleCtrl::MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) {
    int atk = attacker->GetValueData("STR");
    int def = defender->GetValueData("DEF");
    int damage = calculateDamage(atk, def);

    defender->TakeDamage(damage);

    LogController::PrintLog( std::to_string(atk) + " atk , " + std::to_string(def) + " def , " + std::to_string(damage) + " Damage taken"  );
    return true;
}

int BattleCtrl::calculateDamage(int atk, int def){
    int result = atk - def;
    if(result <= 0)
        result = 1;
    return result;
}