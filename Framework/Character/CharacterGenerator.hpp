#pragma once

class BaseCharacter;
class CharacterGenerator{
    public :
        CharacterGenerator();
        ~CharacterGenerator();

        void Initialize();
        BaseCharacter* makeCharacter( Status data );
    
    private:

    
};