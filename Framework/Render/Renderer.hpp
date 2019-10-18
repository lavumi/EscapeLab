#pragma once
#include "../precompiled.hpp"

class Renderer{
public :

    virtual bool Initialize() = 0;
    virtual bool ClearScreen() = 0;
    virtual bool inputMapData(void* mapData ) = 0;
    virtual bool RefreshLog(std::string* logContainer , int logStartPos) = 0;
    virtual bool SetLogContainer( std::string* logContainer, int* logStartPos) = 0;
    virtual bool Render( ) = 0;

};

