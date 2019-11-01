#pragma once
#include "../precompiled.hpp"


class BaseCharacter;
class BaseBattleCtrl {
    public: 
    virtual bool MeleeAttack( BaseCharacter* attacker, BaseCharacter* defender) = 0;

    protected:
    virtual int calculateDamage(int atk, int def) = 0;
};