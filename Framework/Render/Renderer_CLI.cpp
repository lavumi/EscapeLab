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
    
    icon[0] = 176;
    icon[1] = 219; //
    icon[2] = 178;  //
    icon[3] = 112; //
    icon[4] = 64; // 플:레이어`

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
#endif


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
bool Renderer_CLI::initUIFrame(){
    for( int i = 0;i < MaxMapWidth ; i++){ 
        for( int j = 0;j < uiStartPos ; j++){
             uiTexture += (char)255;
        } 
        for( int j = 0;j < MaxMapHeight ; j++){
            if( i == 0 && j == 0){
               uiTexture += (char)201;
            }
            else if( i == 0 && j == MaxMapHeight - 1){
               uiTexture += (char)187;
            }
            else if( i == MaxMapWidth - 1 && j == 0 ){
               uiTexture += (char)200;
            }
            else if( i == MaxMapWidth - 1 && j == MaxMapHeight - 1 ){
               uiTexture += (char)188;
            }
            else if( i == 0 ||  i == MaxMapWidth - 1){
               uiTexture += (char)205;
            }
            else if( j == 0 ||  j == MaxMapHeight - 1){
               uiTexture += (char)186;
            }
            else{
               uiTexture += (char)255;
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

}

// bool Renderer_CLI::moveCursor(Vector2 pos ){
//     // COORD position;

//     // position.X = pos.x;
//     // position.Y = pos.y;
//     // SetConsoleCursorPosition(cliHandle, position);

//     move(pos.x, pos.y);
//     return true;
// }

// bool Renderer_CLI::moveCursor( int x, int y ){
//     // COORD position;

//     // position.X = x;
//     // position.Y = y;
//     // SetConsoleCursorPosition(cliHandle, position);

//     move(x, y);
//     return true;
// }


bool Renderer_CLI::printStringAt(int x, int y, std::string pString){
#ifdef __NCURSES_H
        mvprintw(x,y,"%s",pString.c_str()); 
#else
    COORD position;

    position.X = pos.x;
    position.Y = pos.y;
    SetConsoleCursorPosition(cliHandle, position);
    std::cout << pString;
#endif

 
}

bool Renderer_CLI::ClearScreen(){

    return true;
}

bool Renderer_CLI::inputMapData(void* pMapData){
    FloorMap* mapData = (FloorMap*) pMapData;
    mapTileData = (int*)(mapData->getData());
    return true;
}

bool Renderer_CLI::RefreshLog( std::string* logContainer ,int logStartPos ){

    int maxLogShowSize = 18;
    for( int i = logStartPos , j = 0; j < maxLogShowSize; i++, j++){
        int textIndex = (logStartPos - j) % MaxLogContainerSize;
        if( textIndex < 0)
            break;

        printStringAt(logPrintStartPos.x,logPrintStartPos.y,"                               ");  
        printStringAt(logPrintStartPos.x,logPrintStartPos.y+ maxLogShowSize - j,logContainer[textIndex]);  
        
        
    }

}

bool Renderer_CLI::drawTile(){
    Vector2 pPos = ui->GetPlayerPos();

    int drawStartPosX = pPos.x - MaxMapWidth / 2;
    int drawStartPosY = pPos.y - MaxMapHeight / 2;

    renderTexture  = "";

    for( int i = drawStartPosY, screenX = 0 ; screenX < MaxScreenHeight; i++, screenX ++){  

        for( int j = drawStartPosX, screenY = 0;screenY < MaxScreenWidth ; j++, screenY ++){
            if( i < 0 
                || i >= MaxMapHeight 
                || j < 0 
                || j >= MaxMapWidth ){
                renderTexture += (char)255;
            }
            else{
                int index = i * MaxScreenWidth + j;
                int tileId = mapTileData[index];
                renderTexture += convertToASCII(tileId);
            }
        }               
        
        renderTexture += (char)10;    
    }
    renderTexture += (char)0;

    printStringAt(0,0,renderTexture);  
       
    return true;
}

bool Renderer_CLI::drawPlayer(){
    printStringAt(centerPos.x,centerPos.y,"@");  
    return true;
}

bool Renderer_CLI::refreshUI(){

    
}

char Renderer_CLI::convertToASCII(int id){
    return (char)icon[id]; 
}

int test = 0;
bool Renderer_CLI::Render(){
    

    ClearScreen();

    //drawTile();
    drawPlayer();

#ifdef __NCURSES_H
    refresh();
#endif
}
