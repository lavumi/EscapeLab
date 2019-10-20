#pragma once
#include "../precompiled.hpp"

class DataController;
class Renderer_ncrs : public Renderer{

    public:
        Renderer_ncrs();
        ~Renderer_ncrs();


        bool Initialize();
        bool ClearScreen();
        bool inputMapData(void* pMapData );
        bool RefreshLog(std::string* logContainer ,int logStartPos );
        bool Render();

        bool SetLogContainer( std::string* logContainer , int* logStartPos);

    private: 

        // bool moveCursor( Vector2 pos);
        // bool moveCursor( int x, int y);

        bool printStringAt( int x, int y, std::string pString );
        bool printStringAt( int x, int y, char singleChar);


        bool initUIFrame();

        bool drawMap();
        bool drawTile(int x, int y,int tileID, bool isVisible = false);
        bool drawPlayer();
        bool drawEnemy();
        bool refreshUI();
        bool refreshLog();
        char convertToASCII( int id );

        int icon[12];

        WINDOW* uiWindow;
        WINDOW* logWindow;
        WINDOW* mapWindow;
         
        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;
        Vector2 logPrintStartPos;
        Vector2 centerPos;

        DataController* dataCtrl;
        FloorMap* mapData;

        std::string* logContainer;
        int* logStartPos;
        
};
