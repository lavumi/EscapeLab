#include <iostream>
#include <windows.h>
#include <vector>

#include "../Renderer.hpp"
#include "../../Map/FloorMap.hpp"

#include "../../UserInterface/DataController.hpp"
#include "../../Variables.hpp"


class Renderer_CLI : public Renderer{

    public:
        Renderer_CLI();
        ~Renderer_CLI();


        bool Initialize();
        bool ClearScreen();
        bool inputMapData(void* pMapData );
        bool Render();

    private: 

        bool moveCursor( Vector2 pos);
        bool moveCursor( int x, int y);

        bool initUIFrame();

        bool drawTile();
        bool drawPlayer();
        bool refreshUI();
        char convertToASCII( int id );

        int icon[5] = {
            176,  // 
            178,  //
            219, //
            112, //
            64, // 플레이어
        };

        HANDLE cliHandle;

        DataController* ui;


        int* mapTileData;


        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;

        Vector2 centerPos;

};