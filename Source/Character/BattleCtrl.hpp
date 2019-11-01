#pragma once
#include "../../Framework/Character/BaseBattleCtrl.hpp"
class BaseCharacter;
class BattleCtrl : public BaseBattleCtrl {
    public :
    BattleCtrl();
    ~BattleCtrl();

    virtual bool MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) ;

    protected:
    virtual int calculateDamage(int atk, int def) ;
};