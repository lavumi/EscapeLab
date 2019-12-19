#include <ncurses.h>

#include "Renderer.hpp"
#include "../Map/FloorMap.hpp"
#include "../Character/Character.hpp"
#include "../Input/InputCtrl.hpp"
#include "../UserInterface/DataController.hpp"
#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "Renderer_ncrs.hpp"

// COLOR_BLACK
// COLOR_RED
// COLOR_GREEN
// COLOR_YELLOW
// COLOR_BLUE
// COLOR_MAGENTA
// COLOR_CYAN
// COLOR_WHITE


enum TileColorType{
    BASE_TILE = 1,
    OBSTACLE_TILE,
    FOG_TILE,
    WALL_TILE,
    OOS_TILE,
    NS_TILE,
    CHAR_TILE,
    UI_TILE,
    CURSOR_TILE,
    GUAGE_TILE = 98,
};

Renderer_ncrs::Renderer_ncrs(){
    centerPos = Vector2( MaxMapWindowWidth / 2,  MaxMapWindowHeight / 2);
    renderTexture = "";
    uiTexture = "";

    uiStartPos = MaxMapWindowWidth + 1;
    logPrintStartPos = Vector2( uiStartPos + 2, MaxMapWindowHeight / 2);

    dataCtrl = DataController::getInstance();
    inputCtrl = InputController::getInstance();

    icon[0] = 46;
    icon[1] = 35; //
    icon[2] = 43;
    icon[3] = 35;
    icon[4] = 64; // 플레이어   
    icon[5] = 32; //empty (outSide of map)
   
}

Renderer_ncrs::~Renderer_ncrs(){

}

bool Renderer_ncrs::Initialize(){

    initscr();
    curs_set(0);
    noecho();


    start_color();
    init_pair( BASE_TILE, COLOR_GREEN , COLOR_CYAN );
    init_pair( WALL_TILE, COLOR_BLACK , COLOR_WHITE );
    init_pair( OBSTACLE_TILE, COLOR_BLACK , COLOR_WHITE );
    init_pair( FOG_TILE, COLOR_WHITE , COLOR_MAGENTA );
    init_pair( OOS_TILE, COLOR_WHITE , COLOR_BLACK);
    init_pair( NS_TILE, COLOR_BLACK , COLOR_BLACK);
    init_pair( CHAR_TILE, COLOR_CYAN , COLOR_BLACK );
    init_pair( CURSOR_TILE, COLOR_MAGENTA , COLOR_BLACK );
    init_pair( 98, COLOR_RED , COLOR_BLACK );
    init_pair( 99, COLOR_BLUE , COLOR_BLACK );
    init_pair( UI_TILE ,COLOR_GREEN , COLOR_BLACK );
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
    uiWindow = newwin(MaxUIHeight,MaxUIWidth, 0 , MaxMapWindowWidth + 1);

    logWindow = newwin(MaxUIHeight,MaxUIWidth, MaxUIHeight + 1 , MaxMapWindowWidth + 1);


    wattron(logWindow, COLOR_PAIR(BASE_TILE));

    drawUI();

    return true;
}

bool Renderer_ncrs::SetLogContainer( std::string* logContainer , int* logStartPos){
    this->logContainer = logContainer;
    this->logStartPos = logStartPos;
    return true;
}

bool Renderer_ncrs::printStringAt(int x, int y, std::string pString){
    
    return true;
}

bool Renderer_ncrs::ClearScreen(){

    return true;
}

bool Renderer_ncrs::inputMapData(void* pMapData){
    mapData = (FloorMap*) pMapData;
    //mapTileData = (int*)(mapData->getData());
    return true;
}

bool Renderer_ncrs::drawMap(){

    TileData* mapTileData = (TileData*)(mapData->getData());
    Vector2 pPos = dataCtrl->GetPlayerPos();

    int drawStartPosX = pPos.x - MaxMapWindowWidth / 2;
    int drawStartPosY = pPos.y - MaxMapWindowHeight / 2;

    renderTexture  = "";
    
    int mapDrawStartX = 0;
    int mapDrawStartY = 0;

   // attron(COLOR_PAIR(WALL_TILE));

    //최적화 염두에 두자
    for( int i = drawStartPosY, screenY = 0 ; screenY < MaxMapWindowHeight; i++, screenY ++){
        renderTexture = "";
        for( int j = drawStartPosX, screenX = 0;screenX < MaxMapWindowWidth ; j++, screenX ++){
            if( i < 0
                || i >= MaxMapHeight
                || j < 0
                || j >= MaxMapWidth ){
                    drawTile(screenX, screenY, 5);
            }
            else{
                int index = i * MaxMapWidth + j;
                int tileId = mapTileData[index].getTileID();
                drawTile(screenX, screenY, tileId, mapData->isInSight(j,i), mapData->hasSeen(j,i),  mapData->getCharacter(j,i));
            }
        }

        //mvprintw(mapDrawStartY,mapDrawStartX,"%s",renderTexture.c_str()); 

        mapDrawStartY++;
    }
    
   // attroff(COLOR_PAIR(WALL_TILE));
    return true;
}

bool Renderer_ncrs::drawTile(int x, int y,int tileID, bool isVisible , bool hasSeen, BaseCharacter* character){
    if( isVisible && character != nullptr ){
        attron(COLOR_PAIR(CHAR_TILE));
        char headChar = character->GetNameHead();
        mvprintw(y,x, "%c", headChar); 
        attroff(COLOR_PAIR(CHAR_TILE));

    }
    else if ( isVisible ){
        attron(COLOR_PAIR(tileID + 1));
        mvprintw(y,x, "%c", convertToASCII(tileID)); 
        attroff(COLOR_PAIR(tileID + 1));
    }
    else if( hasSeen ){
        attron(COLOR_PAIR(OOS_TILE));
        mvprintw(y,x, "%c", convertToASCII(tileID)); 
        attroff(COLOR_PAIR(OOS_TILE));
    }
    else {
        attron(COLOR_PAIR(NS_TILE));
        mvprintw(y,x, "%c", convertToASCII(tileID)); 
        attroff(COLOR_PAIR(NS_TILE));
    }
    return true;;
}

bool Renderer_ncrs::drawInputModeCursor(){
    Vector2 curPos = inputCtrl->GetCursorPos();
    if( curPos == Vector2(0,0))
        return false;

    Vector2 pPos = dataCtrl->GetPlayerPos();
    drawBresenhamLine( pPos,curPos );

    // attron(COLOR_PAIR(CURSOR_TILE));
    // 
    // int posX = curPos.x - pPos.x + centerPos.x;
    // int posY = curPos.y - pPos.y + centerPos.y;
    // mvprintw(posY,posX,"*");   
    // attroff(COLOR_PAIR(CURSOR_TILE));
    return true;
}


bool Renderer_ncrs::drawPlayer(){
    attron(COLOR_PAIR(CHAR_TILE));
    mvprintw(centerPos.y,centerPos.x,"%c",convertToASCII(4));   
    attroff(COLOR_PAIR(CHAR_TILE));
    return true;
}

bool Renderer_ncrs::drawEnemy(){
    attron(COLOR_PAIR(CHAR_TILE));
    int enemySize = dataCtrl->GetEnemyCount();
    Vector2 pPos = dataCtrl->GetPlayerPos();

    for(int i = 0;i < enemySize;i++){
        Vector2 pos = dataCtrl->GetEnemyPos(i);
        int posX = pos.x - pPos.x + centerPos.x;
        int posY = pos.y - pPos.y + centerPos.y;
        mvprintw(posY,posX,"T");   
    }

    attroff(COLOR_PAIR(CHAR_TILE));
    return true;
}

bool Renderer_ncrs::drawUI(){
    wattron(uiWindow, COLOR_PAIR(UI_TILE));
    box(uiWindow,  ACS_VLINE, ACS_HLINE);
    int InitUICursorPosX =  2, InitUICursorPosY = 1;



    for( int i = 0; i < StatusData::stringDataLength ; i++ ){
        std::string value = dataCtrl->GetStringUIData((StatusData::stringData)i);
        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, value.c_str());
        InitUICursorPosY++;
    }

    for( int i = 0; i < StatusData::vectorDataLength ; i++ ){
        Vector2 value = dataCtrl->GetPercentUIData((StatusData::vectorData)i);
        int curValue = value.x;
        int maxValue = value.y;
        std::string parsedData = ToString((StatusData::vectorData)i);


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
       

        int interspace = MaxUIWidth - parsedData.length() - 1 - 20 - 2 - 2;
       // parsedData += std::to_string(interspace);
        for(int i = 0;i < interspace ;i ++){
            parsedData += " ";
        }
        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, parsedData.c_str());

        int percent = (int)((float)curValue / (float)maxValue * 10);
        wattroff(uiWindow, COLOR_PAIR(UI_TILE));
        wattron(uiWindow,COLOR_PAIR(GUAGE_TILE));
        for( int i = 0;i < 20 ; i++ ){
            if( i <= percent * 2){
                
                waddch(uiWindow, ACS_CKBOARD);
            }      
            else{
                waddch(uiWindow, ACS_HLINE);
            }
        }
        wattroff(uiWindow,COLOR_PAIR(GUAGE_TILE));
        wattron(uiWindow, COLOR_PAIR(UI_TILE));
        
        
        InitUICursorPosY++;
    }

    for( int i = 0;i < StatusData::intDataLength ; i++ ){
        int value = dataCtrl->GetValueUIData((StatusData::intData)i);
        std::string parsedData = ToString((StatusData::intData)i);

        parsedData += " : ";
        parsedData += std::to_string(value);

        mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX, parsedData.c_str());
        i++;

        if( i < StatusData::intDataLength){
            int value = dataCtrl->GetValueUIData((StatusData::intData)i);
            std::string parsedData = ToString((StatusData::intData)i);

            parsedData += " : ";
            parsedData += std::to_string(value);
            mvwprintw(uiWindow,InitUICursorPosY, InitUICursorPosX + MaxUIWidth / 2 - 2, parsedData.c_str());
        }
        else{
            break;
        }

        InitUICursorPosY++;
    }

    wattroff(uiWindow, COLOR_PAIR(UI_TILE));
    touchwin(uiWindow);
    wrefresh(uiWindow);

    return true;
}

bool Renderer_ncrs::drawLog(){
    wattron( logWindow, COLOR_PAIR(UI_TILE));
    box(logWindow,  ACS_VLINE, ACS_HLINE);
    int maxLogShowSize = MaxUIHeight - 2;
    for( int i = *logStartPos , j = 0; j < maxLogShowSize; i++, j++){
        int textIndex = (*logStartPos - j) % MaxLogContainerSize;
        if( textIndex < 0)
            textIndex = MaxLogContainerSize - 1;
        mvwprintw(logWindow, maxLogShowSize -j , 2, logContainer[textIndex].c_str());
    }
    wattroff( logWindow, COLOR_PAIR(UI_TILE));
    touchwin(logWindow);
    wrefresh(logWindow);
    return true;
}

char Renderer_ncrs::convertToASCII(int id){
    return (char)icon[id]; 
}

bool Renderer_ncrs::drawBresenhamLine(Vector2 start, Vector2 end ){
    attron(COLOR_PAIR(CURSOR_TILE));

    int deltaX, deltaY;
    int counter = 0;

    int width = end.x - start.x;
    int height = end.y - start.y;



    if ( width < 0 ){
        deltaX = -1;
        width = -width;
    }
    else {
        deltaX = 1;
    }

    if ( height < 0 ) {
        deltaY = -1;
        height = -height;
    }
    else{
        deltaY = 1;
    }

    int x = start.x;
    int y = start.y;

    Vector2 pPos = dataCtrl->GetPlayerPos();
    if ( width >= height ){
        for ( int i = 0; i < width ; i++){
            x += deltaX;
            counter += height;

            if( counter >= width ){
                y += deltaY;
                counter -= width;
            }

            int posX = x - pPos.x + centerPos.x;
            int posY = y - pPos.y + centerPos.y;
            mvprintw(posY,posX,"*");
        }
    }
    else {
        for ( int i = 0 ; i < height ; i++ ){
            y += deltaY;
            counter += width;

            if ( counter >= height ){
                x += deltaX;
                counter -= height;
            }
            int posX = x - pPos.x + centerPos.x;
            int posY = y - pPos.y + centerPos.y;
            mvprintw(posY,posX,"*");
        }
    }

    return true;
}

bool Renderer_ncrs::Render(){
    ClearScreen();
    //Game Main Draw
    {
        drawMap();
        drawPlayer();
        drawInputModeCursor();
        refresh();
    }

    //UI draw
    {
        drawUI();
        drawLog();
    }


    return true;
}

bool Renderer_ncrs::RefreshLog( std::string* logContainer ,int logStartPos ){
    return true;
}
