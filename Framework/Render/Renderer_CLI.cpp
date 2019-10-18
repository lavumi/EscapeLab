#ifdef _WIN32
#else
    #include <ncurses.h>
#endif

#include "Renderer.hpp"
#include "../Map/FloorMap.hpp"

#include "../UserInterface/DataController.hpp"
#include "../UserInterface/LogController.hpp"
#include "../Variables.hpp"
#include "Renderer_CLI.hpp"


Renderer_CLI::Renderer_CLI(){
    centerPos = Vector2( MaxMapWidth / 2,  MaxMapHeight / 2);
    renderTexture = "";
    uiTexture = "";

    uiStartPos = MaxMapWidth + 1;
    logPrintStartPos = Vector2( uiStartPos + 2, MaxMapHeight / 2);

    ui = DataController::getInstance();
   
#ifdef _WIN32 
    icon[0] = 176;
    icon[1] = 219; //
    icon[2] = 178;  //
    icon[3] = 112; //
    
    icon[5] = 255; //empty (outSide of map)
    
    icon[6] = 205; // -
    icon[7] = 186; // |
    
    icon[8] = 201; // topleft
    icon[9] = 187; // topright
    icon[10] = 200; // btmleft
    icon[11] = 199; // btmright
    
#else
    icon[0] = 46;
    icon[1] = 35; //
    icon[2] = 43;
    icon[3] = 35;

    icon[5] = 32; //empty (outSide of map)
    
    icon[6] = 45; // |
    icon[7] = 124; // -
    
    icon[8] = 45; // toplef
    icon[9] = 45; // topright
    icon[10] = 45; // btmleft
    icon[11] = 45; // btmright
#endif
    icon[4] = 64; // 플레이어

}

Renderer_CLI::~Renderer_CLI(){
    delete[] mapTileData; 
#ifdef __NCURSES_H
   
#endif
}

bool Renderer_CLI::Initialize(){
    system( "mode con lines=42 cols=84" );


#ifdef _WIN32
    SetConsoleOutputCP(437);
    cliHandle = GetStdHandle( STD_OUTPUT_HANDLE );

    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = false;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(cliHandle, &cursor );
#endif

#ifdef __NCURSES_H
    initscr();
    curs_set(0);
    noecho();
#endif


   initUIFrame();//
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

/*
bool Renderer_CLI::initUIFrame(){
    for( int i = 0;i < MaxMapWidth ; i++){ 
        for( int j = 0;j < uiStartPos ; j++){
             uiTexture += convertToASCII(5);
        } 
        for( int j = 0;j < MaxMapHeight ; j++){
            if( i == 0 && j == 0){
               uiTexture += convertToASCII(8);
            }
            else if( i == 0 && j == MaxMapHeight - 1){
               uiTexture += convertToASCII(9);
            }
            else if( i == MaxMapWidth - 1 && j == 0 ){
               uiTexture += convertToASCII(10);
            }
            else if( i == MaxMapWidth - 1 && j == MaxMapHeight - 1 ){
               uiTexture += convertToASCII(11);
            }
            else if( i == 0 ||  i == MaxMapWidth - 1){
               uiTexture += convertToASCII(6);
            }
            else if( j == 0 ||  j == MaxMapHeight - 1){
               uiTexture += convertToASCII(7);
            }
            else{
               uiTexture += convertToASCII(5);
            }
        }
        uiTexture += (char)10;
    }

    printStringAt(0,0,uiTexture);  


    int InitUICursorPosX = uiStartPos + 2, InitUICursorPosY = 1;
    
    auto stringUIData = ui->GetUIstringOrder();
    for( auto iter = stringUIData.begin();iter != stringUIData.end();iter++){
        std::string value = ui->GetStringUIData(*iter);


        printStringAt(InitUICursorPosX,InitUICursorPosY,value);  
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

        printStringAt(InitUICursorPosX,InitUICursorPosY,parsedData);  
        InitUICursorPosY++;
    }

    auto valueUIData = ui->GetUIvalueOrder(); 
    for( auto iter = valueUIData.begin();iter != valueUIData.end();iter++){
        int value = ui->GetValueUIData(*iter);
        std::string parsedData = *iter;
        
        parsedData += " : ";
        parsedData += std::to_string(value);

        printStringAt(InitUICursorPosX,InitUICursorPosY,parsedData);  
        iter++;
        if( iter != valueUIData.end()){
            int value = ui->GetValueUIData(*iter);
            std::string parsedData =  *iter + " : " + std::to_string(value) ;
            printStringAt(InitUICursorPosX + MaxMapWidth / 2 - 2 ,InitUICursorPosY,parsedData);  
        }
        else{
            break;
        }

        InitUICursorPosY++;
    }

    return true;
}
*/

bool Renderer_CLI::initUIFrame(){
    uiWindow = newwin(MaxUIHeight,MaxUIWidth, 0 , MaxMapWidth + 1);
    box(uiWindow,  ACS_VLINE, ACS_HLINE);
    touchwin(uiWindow);
    wrefresh(uiWindow);

    logWindow = newwin(MaxUIHeight,MaxUIWidth, MaxUIHeight + 1 , MaxMapWidth + 1);
    box(logWindow,  ACS_VLINE, ACS_HLINE);


    refreshUI();

    return true;
}

bool Renderer_CLI::SetLogContainer( std::string* logContainer , int* logStartPos){
    this->logContainer = logContainer;
    this->logStartPos = logStartPos;
}

bool Renderer_CLI::printStringAt( int x, int y, char singleChar){
    mvprintw(y,x,"%c", singleChar );
    return true;
}

bool Renderer_CLI::printStringAt(int x, int y, std::string pString){
    #ifdef __NCURSES_H
            mvprintw(y,x,"%s",pString.c_str()); 
    #else
        COORD position;

        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(cliHandle, position);
        std::cout << pString;
    #endif

    return true;
}

bool Renderer_CLI::ClearScreen(){

    return true;
}

bool Renderer_CLI::inputMapData(void* pMapData){
    FloorMap* mapData = (FloorMap*) pMapData;
    mapTileData = (int*)(mapData->getData());
    return true;
}


//bool Renderer_CLI::drawTile(){
//    Vector2 pPos = ui->GetPlayerPos();
//
//    int drawStartPosX = pPos.x - MaxMapWidth / 2;
//    int drawStartPosY = pPos.y - MaxMapHeight / 2;
//
//    renderTexture  = "";
//
//    int mapDrawStartX = 0;
//    int mapDrawStartY = 0;
//
//    for( int i = drawStartPosY, screenX = 0 ; screenX < MaxScreenHeight; i++, screenX ++){
//
//        for( int j = drawStartPosX, screenY = 0;screenY < MaxScreenWidth ; j++, screenY ++){
//            if( i < 0
//                || i >= MaxMapHeight
//                || j < 0
//                || j >= MaxMapWidth ){
//                renderTexture += convertToASCII(5);
//            }
//            else{
//                int index = i * MaxScreenWidth + j;
//                int tileId = mapTileData[index];
//                renderTexture += convertToASCII(tileId);
//            }
//        }
//
//        renderTexture += (char)10;
//    }
//    renderTexture += (char)0;
//
//    printStringAt(0,0,renderTexture);
//
//    return true;
//}

bool Renderer_CLI::drawTile(){
    Vector2 pPos = ui->GetPlayerPos();

    int drawStartPosX = pPos.x - MaxMapWidth / 2;
    int drawStartPosY = pPos.y - MaxMapHeight / 2;

    renderTexture  = "";
    
    int mapDrawStartX = 0;
    int mapDrawStartY = 0;

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
                int index = i * MaxScreenWidth + j;
                int tileId = mapTileData[index];
                renderTexture += convertToASCII(tileId);
            }
        }
        printStringAt(mapDrawStartX, mapDrawStartY, renderTexture);
        mapDrawStartY++;
    }
    return true;
}

bool Renderer_CLI::drawPlayer(){
    printStringAt(centerPos.x,centerPos.y, convertToASCII(4));  
    return true;
}

bool Renderer_CLI::refreshUI(){
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
    touchwin(uiWindow);
    wrefresh(uiWindow);
    return true;
}

bool Renderer_CLI::refreshLog(){
    wclear(logWindow);
    box(logWindow,  ACS_VLINE, ACS_HLINE);
    int maxLogShowSize = 19;
    for( int i = *logStartPos , j = 0; j < maxLogShowSize; i++, j++){
        int textIndex = (*logStartPos - j) % MaxLogContainerSize;
        if( textIndex < 0)
            break;
        mvwprintw(logWindow,maxLogShowSize -j , 2, logContainer[textIndex].c_str());
    }
    touchwin(logWindow);
    wrefresh(logWindow);
}

char Renderer_CLI::convertToASCII(int id){

    return (char)icon[id]; 
}

bool Renderer_CLI::Render(){
    

    ClearScreen();
    drawTile();
    drawPlayer();

    #ifdef __NCURSES_H
    refresh();
    refreshUI();
    refreshLog();

    #endif
    return true;
}




bool Renderer_CLI::RefreshLog( std::string* logContainer ,int logStartPos ){

    return true;
    int maxLogShowSize = 18;
    for( int i = logStartPos , j = 0; j < maxLogShowSize; i++, j++){
        int textIndex = (logStartPos - j) % MaxLogContainerSize;
        if( textIndex < 0)
            break;
        mvwprintw(logWindow,maxLogShowSize -j, 0, logContainer[textIndex].c_str());
    }
    touchwin(logWindow);
    wrefresh(logWindow);
    return true;
}
