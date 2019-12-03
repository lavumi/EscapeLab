#pragma once
#include "../precompiled.hpp"

class DataController;
class InputController;
class Renderer_ncrs : public Renderer{

    public:
        Renderer_ncrs(); // ok
        ~Renderer_ncrs();


        bool Initialize(); // no
        bool ClearScreen(); //???
        bool inputMapData(void* pMapData ); // ok
        bool Render();

        bool SetLogContainer( std::string* logContainer , int* logStartPos);

    private: 

        // bool moveCursor( Vector2 pos);
        // bool moveCursor( int x, int y);

        bool initUIFrame(); // no

        bool drawMap(); // ok

        bool drawTile(int x, int y,int tileID, bool isVisible = false, BaseCharacter* character = nullptr); // no
        bool drawInputModeCursor(); //no
        bool drawPlayer(); // no
        bool drawUI(); // no
        bool drawLog(); // no


        WINDOW* uiWindow;
        WINDOW* logWindow;



        char convertToASCII( int id );
        bool drawBresenhamLine( Vector2 start, Vector2 end);

        int icon[12];
         
        std::string renderTexture;
        std::string uiTexture;

        int uiStartPos;
        Vector2 logPrintStartPos;
        Vector2 centerPos;

        DataController* dataCtrl;
        FloorMap* mapData;

        std::string* logContainer;
        int* logStartPos;


        InputController* inputCtrl;
        
};
