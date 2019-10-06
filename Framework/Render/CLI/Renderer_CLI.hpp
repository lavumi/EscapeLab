#include <iostream>
#include <windows.h>
#include <vector>

#include "../Renderer.hpp"
#include "../../Map/FloorMap.hpp"
#include "../../Character/Character.hpp"
#include "../../UserInterface/BaseUI.hpp"
#include "../../Variables.hpp"


class Renderer_CLI : public Renderer{

    public:
        Renderer_CLI();
        ~Renderer_CLI();


        bool Initialize();
        bool ClearScreen();
        bool inputMapData(void* pMapData );
        bool setPlayerData(void* character);
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

        Character* player;
        BaseUI* ui;


        int* mapTileData;


        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;

        Vector2 centerPos;

};