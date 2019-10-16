#include "../Framework/Map/FloorMap.hpp"


#include "../Framework/Render/Renderer.hpp"
#include "../Framework/Render/Renderer_CLI.hpp"
#include "../Framework/Input/InputCtrl.hpp"
#include "../Framework/UserInterface/LogController.hpp"

#include "../Source/Character/Player.hpp"
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
    return false;

}