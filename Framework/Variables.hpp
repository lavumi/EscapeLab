#pragma once

const int MaxMapWidth = 70;
const int MaxMapHeight = 60;

const int MaxMapWindowWidth = 70;
const int MaxMapWindowHeight = 40;

const int MaxUIWidth = 40;
const int MaxUIHeight = 20;

struct Vector2 {
    int x;
    int y;

    Vector2( int x=0, int y=0 ){
        this->x = x;
        this->y = y;
    }
};


