#pragma once

class BaseCharacter;
class FloorMap;
class CharacterGenerator{
    public :
        CharacterGenerator();
        ~CharacterGenerator();

        void Initialize(BaseBattleCtrl* btlCtrl);
        BaseCharacter* makeCharacter( Status data , FloorMap* map, Vector2 Pos, bool isPlayer = false);
    
    private:

        BaseCharacter* characterPool;
        BaseBattleCtrl* btlCtrl;
};