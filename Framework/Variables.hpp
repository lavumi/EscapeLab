#pragma once

static int MaxMapWidth = 40;
static int MaxMapHeight = 40;

static int MaxScreenWidth = 40;
static int MaxScreenHeight = 40;

static int MaxUIWidth = 40;
static int MaxUIHeight = 40;

struct Vector2 {
    int x;
    int y;

    Vector2( int x=0, int y=0 ){
        this->x = x;
        this->y = y;
    }
};


