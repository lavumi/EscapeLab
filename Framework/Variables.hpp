#pragma once

const int MaxMapWidth = 70;
const int MaxMapHeight = 50;

const int MaxMapWindowWidth = 70;
const int MaxMapWindowHeight = 40;

const int MaxUIWidth = 40;
const int MaxUIHeight = 20;

const bool isRoundSight = false;

struct Vector2 {
    int x;
    int y;

    Vector2( int x=0, int y=0 ){
        this->x = x;
        this->y = y;
    }
};


