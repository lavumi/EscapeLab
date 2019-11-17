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


namespace StatusData{
    enum stringData: unsigned int{
        Name,
    };

    enum vectorData: unsigned int{
        HP,
        MP,
    };

    enum intData: unsigned int{
        STR,
        EV,
        DEX,
        DEF,
        INT,
        GLD
    };

    inline const char* ToString(stringData v){
        switch (v){
            case Name:   
                return "Name";
        }
    }

        inline const char* ToString(vectorData v){
        switch (v){
            case HP:   
                return "HP";
            case MP:   
                return "MP";
        }
    }

        inline const char* ToString(intData v){
        switch (v){
            case STR:   
                return "STR";
            case EV:   
                return "EV";
            case DEX:   
                return "DEX";
            case DEF:   
                return "DEF";
            case INT:   
                return "INT";
            case GLD:   
                return "GLD";
        }
    }

    const int stringDataLength = 1;
    const int vectorDataLength = 2;
    const int intDataLength = 6;
}

