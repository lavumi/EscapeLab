#pragma once

#include <stdio.h>
#include <windows.h>

class Renderer{
    public :

        virtual bool Initialize() = 0;
        virtual bool ClearScreen() = 0;
        virtual bool inputMapData(void* mapData ) = 0;
        virtual bool Render( ) = 0;

};

