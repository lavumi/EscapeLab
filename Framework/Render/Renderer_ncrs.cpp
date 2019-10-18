#include <ncurses.h>

#include "Renderer.hpp"
#include "../Map/FloorMap.hpp"

#include "../UserInterface/DataController.hpp"
#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "Renderer_ncrs.hpp"


enum TileColorType{
    BASE_TILE = 1,
    WALL_TILE,
    OBSTACLE_TILE,
    FOG_TILE,
    PLAYER_TILE
};

Renderer_ncrs::Renderer_ncrs(){
    centerPos = Vector2( MaxScreenWidth / 2,  MaxScreenHeight / 2);
    renderTexture = "";
    uiTexture = "";

    uiStartPos = MaxScreenWidth + 1;
    logPrintStartPos = Vector2( uiStartPos + 2, MaxScreenHeight / 2);

    ui = DataController::getInstance();

    icon[0] = 46;
    icon[1] = 35; //
    icon[2] = 43;
    icon[3] = 35;
    icon[4] = 64; // 플레이어   
    icon[5] = 32; //empty (outSide of map)
   
}

Renderer_ncrs::~Renderer_ncrs(){
    delete[] mapTileData; 
#ifdef __NCURSES_H
   
#endif
}

bool Renderer_ncrs::Initialize(){

    initscr();
    curs_set(0);
    noecho();


    start_color();
    init_pair( BASE_TILE, COLOR_GREEN , COLOR_BLACK );
    init_pair( WALL_TILE, COLOR_BLACK , COLOR_GREEN );
    init_pair( OBSTACLE_TILE, COLOR_BLACK , COLOR_WHITE );
    init_pair( FOG_TILE, COLOR_WHITE , COLOR_MAGENTA );
    init_pair( PLAYER_TILE, COLOR_WHITE , COLOR_BLACK );

    initUIFrame();
    return true;
}


/*   UI 형태

    Lavumi - Magician
    HP : 100/100 ##########
    MP :  10/ 30 ####------
    STR : 10    | AC : 10
    DEX : 5     | EV : 15
    INT : 11    |    
    Gold : 100



    Rule
    1. Single StringData -> PercentData -> Single Data 순서대로 위에서부터 나열된다
    2. SingleData 는 2줄로 나뉘어서 표현해준다.


*/

bool Renderer_ncrs::initUIFrame(){
    uiWindow = newwin(MaxUIHeight,MaxUIWidth, 0 , MaxScreenWidth + 1);
    box(uiWindow,  ACS_VLINE, ACS_HLINE);
    touchwin(uiWindow);
    wrefresh(uiWindow);


    logWindow = newwin(MaxUIHeight,MaxUIWidth, MaxUIHeight + 1 , MaxScreenWidth + 1);
    box(logWindow,  ACS_VLINE, ACS_HLINE);


    wattron(logWindow, COLOR_PAIR(BASE_TILE));

    refreshUI();

    return true;
}

bool Renderer_ncrs::SetLogContainer( std::string* logContainer , int* logStartPos){
    this->logContainer = logContainer;
    this->logStartPos = logStartPos;
}

bool Renderer_ncrs::printStringAt(int x, int y, std::string pString){
    
    return true;
}

bool Renderer_ncrs::ClearScreen(){

    return true;
}

bool Renderer_ncrs::inputMapData(void* pMapData){
    FloorMap* mapData = (FloorMap*) pMapData;
    mapTileData = (int*)(mapData->getData());
    return true;
}

bool Renderer_ncrs::drawTile(){
    Vector2 pPos = ui->GetPlayerPos();

    int drawStartPosX = pPos.x - MaxScreenWidth / 2;
    int drawStartPosY = pPos.y - MaxScreenHeight / 2;

    renderTexture  = "";
    
    int mapDrawStartX = 0;
    int mapDrawStartY = 0;



    //최적화 염두에 두자
    for( int i = drawStartPosY, screenX = 0 ; screenX < MaxScreenHeight; i++, screenX ++){
        renderTexture = "";
        for( int j = drawStartPosX, screenY = 0;screenY < MaxScreenWidth ; j++, screenY ++){
            if( i < 0
                || i >= MaxMapHeight
                || j < 0
                || j >= MaxMapWidth ){
                renderTexture += convertToASCII(5);
            }
            else{
                int index = i * MaxMapWidth + j;
                int tileId = mapTileData[index];
                renderTexture += convertToASCII(tileId);
            }
        }

        mvprintw(mapDrawStartY,mapDrawStartX,"%s",renderTexture.c_str()); 

        mapDrawStartY++;
    }
    
    //attroff(COLOR_PAIR(WALL_TILE));
    return true;
}

bool Renderer_ncrs::drawPlayer(){
    attron(COLOR_PAIR(PLAYER_TILE));
    mvprintw(centerPos.y,centerPos.x,"%c",convertToASCII(4));   
    attroff(COLOR_PAIR(PLAYER_TILE));
    return true;
}

bool Renderer_ncrs::refreshUI(){
    wattron(uiWindow, COLOR_PAIR(BASE_TILE));
    int InitUICursorPosX =  2, InitUICursorPosY = 1;

    auto stringUIData = ui->GetUIstringOrder();
    for( auto iter = stringUIData.begin();iter != stringUIData.end();iter++){
        std::string value = ui->GetStringUIData(*iter);

        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, value.c_str());
        InitUICursorPosY++;
    }
    

    auto percentUIData = ui->GetUIpercentOrder(); 
    for( auto iter = percentUIData.begin();iter != percentUIData.end();iter++){

        Vector2 value = ui->GetPercentUIData(*iter);
        int curValue = value.x;
        int maxValue = value.y;


        std::string parsedData = *iter;
        parsedData += " : ";
        if( curValue < 100 )
            parsedData += " ";
        if( curValue < 10 )
            parsedData += " ";
        parsedData += std::to_string(curValue);
        parsedData += "/";
        if( maxValue < 100 )
            parsedData += " ";
        if( maxValue < 10 )
            parsedData += " ";
        parsedData += std::to_string(maxValue);;


        int interspace = MaxMapWidth - (*iter).length() - 3 - 3 - 1 - 3 - 10 - 2 - 2;
        for(int i = 0;i < interspace ;i ++){
            parsedData += " ";
        }

        int percent = (int)((float)curValue / (float)maxValue * 10);
        for( int i = 0;i < 10 ; i++ ){
            if( i <= percent){
                parsedData += '#';
            }      
            else{
                parsedData += "-";
            }
        }


        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, parsedData.c_str());
        
        InitUICursorPosY++;
    }

    auto valueUIData = ui->GetUIvalueOrder(); 
    for( auto iter = valueUIData.begin();iter != valueUIData.end();iter++){
        int value = ui->GetValueUIData(*iter);
        std::string parsedData = *iter;
        
        parsedData += " : ";
        parsedData += std::to_string(value);

        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, parsedData.c_str());
        iter++;
        if( iter != valueUIData.end()){
            int value = ui->GetValueUIData(*iter);
            std::string parsedData =  *iter + " : " + std::to_string(value) ;
            mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX + MaxUIWidth / 2 - 2, parsedData.c_str());
        }
        else{
            break;
        }

        InitUICursorPosY++;
    }
    //attroff(COLOR_PAIR(BASE_TILE));
    wattroff(uiWindow, COLOR_PAIR(BASE_TILE));
    touchwin(uiWindow);
    wrefresh(uiWindow);

    return true;
}

bool Renderer_ncrs::refreshLog(){
    wclear(logWindow);
    wattron( logWindow, COLOR_PAIR(BASE_TILE));
    box(logWindow,  ACS_VLINE, ACS_HLINE);
    int maxLogShowSize = MaxUIHeight - 2;
    for( int i = *logStartPos , j = 0; j < maxLogShowSize; i++, j++){
        int textIndex = (*logStartPos - j) % MaxLogContainerSize;
        if( textIndex < 0)
            textIndex = MaxLogContainerSize - 1;
        mvwprintw(logWindow, maxLogShowSize -j , 2, logContainer[textIndex].c_str());
    }
    wattroff( logWindow, COLOR_PAIR(BASE_TILE));
    touchwin(logWindow);
    wrefresh(logWindow);
}

char Renderer_ncrs::convertToASCII(int id){

    return (char)icon[id]; 
}

bool Renderer_ncrs::Render(){
    

    ClearScreen();
    drawTile();
    drawPlayer();
    refresh();
    refreshUI();
    refreshLog();
    return true;
}




bool Renderer_ncrs::RefreshLog( std::string* logContainer ,int logStartPos ){
    return true;
}
