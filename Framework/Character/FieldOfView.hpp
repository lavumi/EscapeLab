#pragma once
#include "../precompiled.hpp"


class BaseCharacter;
class FloorMap;
class FieldOfView{  

public :

    FieldOfView(BaseCharacter* player);
    ~FieldOfView();

    void Compute(Vector2 origin, int rangeLimit);


private :
    struct Slope // represents the slope Y/X as a rational number
    {
    public:
    Slope(int y, int x) { Y = y; X = x; }

    bool Greater(int y, int x) { return Y*x > X*y; } // this > y/x
    bool GreaterOrEqual(int y, int x) { return Y*x >= X*y; } // this >= y/x
    bool Less(int y, int x) { return Y*x < X*y; } // this < y/x
    //public bool LessOrEqual(uint y, uint x) { return Y*x <= X*y; } // this <= y/x

    int X, Y;
    };

    void _compute(int octant, Vector2 origin, int rangeLimit, int x, Slope top, Slope bottom);


    bool BlocksLight(int x, int y, int octant, Vector2 origin);
    void SetVisible(int x, int y, int octant, Vector2 origin);


    bool _blocksLight(int x,int y);
    int GetDistance(int x, int y);
    void _setVisible(int x, int y);


    BaseCharacter* player;
};