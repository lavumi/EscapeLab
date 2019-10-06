#include "GameMain.hpp"


GameMain::GameMain(){

}

GameMain::~GameMain(){
    delete renderer;
    delete sampleMap;
    delete player;
    delete inputCtrl;
}

bool GameMain::Initialize(){
    renderer = new Renderer_CLI();
    sampleMap = new FloorMap();
    player = new Player("Lavumi");
    inputCtrl = new InputController();

    DataController::getInstance()->setCharacter(player);

    player->Initialize();
    renderer->Initialize();
    renderer->inputMapData(sampleMap);


}

bool GameMain::Update(){

    renderer->Render();


    int ch = inputCtrl->WairForInput();
    if(ch == 'a')
        player->Move(-1,0);
    if(ch == 'd')
        player->Move(1,0);
    if(ch == 'w')
        player->Move(0,-1);
    if(ch == 's')
        player->Move(0,1);
}