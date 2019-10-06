#pragma once

#include "../Variables.hpp"
#include "../Map/FloorMap.hpp"

class Character{
    public : 
        Character();
        ~Character();

        bool Move(int x, int y);

        bool goUpstair();
        bool goDownstair();
        
        Vector2 GetPos();
    private:
        Vector2 position;
        FloorMap* currentMap;
};