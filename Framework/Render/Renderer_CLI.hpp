#pragma once
#include "../precompiled.hpp"

class DataController;
class Renderer_CLI : public Renderer{

    public:
        Renderer_CLI();
        ~Renderer_CLI();


        bool Initialize();
        bool ClearScreen();
        bool inputMapData(void* pMapData );
        bool Render();

        bool SetLogContainer( std::string* logContainer , int* logStartPos);

        
};
