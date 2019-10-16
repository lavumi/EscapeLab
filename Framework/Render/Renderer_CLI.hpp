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
        bool RefreshLog(std::string* logContainer ,int logStartPos );
        bool Render();

    private: 

        // bool moveCursor( Vector2 pos);
        // bool moveCursor( int x, int y);

        bool printStringAt( int x, int y, std::string pString );

        bool initUIFrame();

        bool drawTile();
        bool drawPlayer();
        bool refreshUI();
        char convertToASCII( int id );

        int icon[5];

#ifndef __NCURSES_H
        HANDLE cliHandle;
#endif
     
        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;
        Vector2 logPrintStartPos;

        Vector2 centerPos;


        DataController* ui;
        int* mapTileData;

        
};
