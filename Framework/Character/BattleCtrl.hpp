#pragma once
#include "../precompiled.hpp"

class BaseCharacter;
class BattleCtrl  {
    public :
    BattleCtrl();
    ~BattleCtrl();

    virtual bool MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) ;
    virtual bool RangeAttack( BaseCharacter* attacker, Vector2 target) ;

    protected:
    virtual int calculateDamage(int atk, int def) ;
};