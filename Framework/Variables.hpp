#pragma once

const int MaxMapWidth = 40;
const int MaxMapHeight = 40;

const int MaxScreenWidth = 40;
const int MaxScreenHeight = 40;

const int MaxUIWidth = 40;
const int MaxUIHeight = 40;

struct Vector2 {
    int x;
    int y;

    Vector2( int x=0, int y=0 ){
        this->x = x;
        this->y = y;
    }
};


