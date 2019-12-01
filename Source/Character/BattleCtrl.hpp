#pragma once
#include "../../Framework/Character/BaseBattleCtrl.hpp"
class BaseCharacter;
class BattleCtrl : public BaseBattleCtrl {
    public :
    BattleCtrl();
    ~BattleCtrl();

    virtual bool MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) ;
    virtual bool RangeAttack( BaseCharacter* attacker, Vector2 target) ;

    protected:
    virtual int calculateDamage(int atk, int def) ;
};