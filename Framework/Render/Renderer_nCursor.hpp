#pragma once
#include "../precompiled.hpp"

class DataController;
class InputController;
class Renderer_ncrs : public Renderer{

    public:
        Renderer_ncrs();
        ~Renderer_ncrs();


        bool Initialize() override;
        bool ClearScreen() override;
        bool inputMapData(void* pMapData ) override;
        bool RefreshLog(std::string* logContainer ,int logStartPos ) override;
        bool Render() override;

        bool SetLogContainer( std::string* logContainer , int* logStartPos) override;

    private: 

        // bool moveCursor( Vector2 pos);
        // bool moveCursor( int x, int y);

        bool printStringAt( int x, int y, std::string pString );
        bool printStringAt( int x, int y, char singleChar);


        bool initUIFrame();

        bool drawMap();
        bool drawTile(int x, int y,int tileID, bool isVisible = false, bool hasSeen = false, BaseCharacter* character = nullptr);
        bool drawInputModeCursor();
        bool drawPlayer();
        bool drawEnemy();
        bool drawUI();
        bool drawLog();



        char convertToASCII( int id );
        bool drawBresenhamLine( Vector2 start, Vector2 end);

        int icon[12]{};

        WINDOW* uiWindow{};
        WINDOW* logWindow{};
        WINDOW* mapWindow{};
         
        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;
        Vector2 logPrintStartPos;
        Vector2 centerPos;

        DataController* dataCtrl;
        FloorMap* mapData{};

        std::string* logContainer{};
        int* logStartPos{};


        InputController* inputCtrl;
        
};
