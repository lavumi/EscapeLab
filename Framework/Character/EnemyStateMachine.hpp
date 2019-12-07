#pragma once
#include "../precompiled.hpp"


enum EnemyState {
    NONE,
    SLEEP,
    WANDERING,
    FIND_PLAYER,
};


class DataController;
class BaseCharacter;
class EnemyStateMachine{
    public : 
        EnemyStateMachine(BaseCharacter* owner);
        ~EnemyStateMachine();

        void Update();

    private:
        BaseCharacter* owner;
        EnemyState currentState;
        DataController* dataCtrl;


        void checkCondition();

        void wantering();
        void fallowCharacter();
        void rangeAttack();
};