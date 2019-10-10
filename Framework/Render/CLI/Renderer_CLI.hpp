#pragma once
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#endif

#include <vector>

#include "../Renderer.hpp"
#include "../../Map/FloorMap.hpp"

#include "../../UserInterface/DataController.hpp"
#include "../../UserInterface/LogController.hpp"
#include "../../Variables.hpp"


class Renderer_CLI : public Renderer{

    public:
        Renderer_CLI();
        ~Renderer_CLI();


        bool Initialize();
        bool ClearScreen();
        bool inputMapData(void* pMapData );
        bool RefreshLog(std::string* logContainer ,int logStartPos );
        bool Render();

    private: 

        bool moveCursor( Vector2 pos);
        bool moveCursor( int x, int y);

        bool initUIFrame();

        bool drawTile();
        bool drawPlayer();
        bool refreshUI();
        char convertToASCII( int id );

        int icon[5];

        HANDLE cliHandle;




        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;
        Vector2 logPrintStartPos;

        Vector2 centerPos;


        DataController* ui;
        int* mapTileData;

        
};
