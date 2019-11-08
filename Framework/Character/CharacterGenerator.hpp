#pragma once
#include "../precompiled.hpp"

enum StateType{
    StringState,
    VectorState,
    IntState
};

class BaseCharacter;
class CharacterGenerator{
    public:
        CharacterGenerator();
        ~CharacterGenerator();


        bool Initialize();
        bool AddCharacterParam(StateType Type, std::string paramName);

        BaseCharacter* generateCharacter(std::string name, bool isPlayer);
    private:
       
        std::vector<  BaseCharacter* > characterPool;  
};