#include "GameMain.hpp"


GameMain::GameMain(){

}

GameMain::~GameMain(){
    delete renderer;
    delete sampleMap;
    delete player;

    InputController::Delete();
    DataController::Delete();
}

bool GameMain::Initialize(){
    renderer = new Renderer_CLI();
    sampleMap = new FloorMap();
    player = new Player("Lavumi");
    inputCtrl = InputController::getInstance();
    dataCtrl = DataController::getInstance();

    LogController::Initialize( renderer );


    inputCtrl->SetPlayer( player );
    dataCtrl->setCharacter(player);

    player->Initialize();
    renderer->Initialize();
    renderer->inputMapData(sampleMap);
    player->goDownstair( sampleMap );
}

bool GameMain::Update(){

    renderer->Render();
    inputCtrl->WairForInput();

}